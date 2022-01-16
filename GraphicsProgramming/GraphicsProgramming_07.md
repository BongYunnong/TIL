# 그래픽스 프로그래밍 #7 - 라이팅
## Colors
- 가시광선
    - 빛의 파장에 따라 색깔로 표현됨
    - 모든 가시광을 합치면 흰색
    - 파장 길이 : 자외선 > 가시광선 > 적외선
    - 발광하지 않아도 색을 가지고 있음 -> 반사하는 빛의 양이 "물체의 컬러"
- 디지털 컬러
    - 빛의 3원색(R,G,B)의 조합으로 표현
    - 각 원색을 채널이라고 보통 표현
    - 각 채널을 보통 8비트로 양자화(256가지의 단계로 세기를 표현)
        - 16,777,216가지의 색상 표현 가능
    - OpenGL에서는 0~1로 표현
- 디지털 물체의 컬러
    - 광원의 각 채널을 얼마나 반사하는지 정의
        ``` C++
        vec3 lightColor(1.0f, 1.0f, 1.0f);
        vec3 objectColor(1.0f, 0.5f, 0.31f);
        // 요소 단위 곱으로 최종 컬러를 계산(내적이 아니라 그냥 곱)
        vec3 result = lightColor*objectColor;
        ```
    - 광원의 각 채널을 얼마나 반사하는지 정의
        - 빛의 위치와 객체의 각도들은 무시한 아주 단순한 정의
        ![image](https://user-images.githubusercontent.com/11372675/149627787-0bab7efc-e934-4d3a-8134-089388b17d15.png)
## Basic Lighting Model
- 무엇이 사실적으로 만드는가?
    - 명암 표현
        - 광원의 위치, 빛의 입사 각도, 보는 위치 등등 ...
        ![image](https://user-images.githubusercontent.com/11372675/149627817-c8637cdc-00e3-44ab-8e0c-473cb2047c9d.png)
- Phong Lighting Model
    - 물리적인 라이팅 효과를 단순한 모델을 활용해 근사
        - 가장 기본적인 반사 모델 중 하나
        - 3개의 요소로 구성됨 : Ambient Lighting, Diffuse Lighting, Specular Lighting
    - Ambient Lighting
        - 특정 광원에 영향을 안 받더라도 일반적으로 공간에는 은은한 빛이 존재
            - 빛이 안 닿는다고 완전 다크는 일반적으로 아니다!
        - ex. 달빛, 아주 멀리 있는 광원, 다른 객체들로 부터 반사된 간접 빛
    - Ambient Lighting Color 계산하기
        - 라이트 컬러에 작은 양의 factor를 곱해서 계산
        ``` C++
        - fragment shader -
        uniform vec3 lightColor;
        uniform vec3 objectColor;
        ...
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
        vec3 result = ambient * objectColor;
        fragColor = vec4(result, 1.0);
        ```
        ``` C++
        - render 함수 - 
        vmath::vec3 lightColor(1.0f,1.0f,1.0f);
        vmath::vec3 boxColor(1.0f,0.5f,0.31f);
        glUniform3fv(glGetUniformLocation(shader_programs[1], "lightColor"),1,lightColor);
        glUniform3fv(glGetUniformLocation(shader_programs[1], "objectColor"),1,boxColor);
        ```
    - Diffuse Lighting
        - 광원의 빛을 입사각에 따라 산란시키는 빛
        - 명암에 가장 큰 영향을 주는 요소
        - 광원을 정면으로 바라보는 서피스가 더 밝아짐
        - 광원을 향하는 벡터와 노멀 벡터의 내적으로 밝기 정도를 계산 가능!(둘 다 단위 벡터일 때)
    - 노멀 벡터 계산하기
        - 삼각형을 이루는 세 점을 이용한 두 벡터를 외적해서 계산 가능(감는 순서 중요!)
        - 계산 후 버텍스 속성으로 전달하고 프래그먼트별로 보간 되게끔 프래그먼트 쉐이더로 값을 연결
        ``` C++
        - vertex shader -
        #version 430 core
        layout(location = 0) in vec3 pos;
        layout(location = 1) in vec3 normal;

        out vec3 vsNormal;
        ...
        ```
    - 광원을 향하는 벡터를 어떻게 계산할까?
        - 3차원 광원 위치(우리가 정하는 것)에서 3차원 프래그먼트 위치(쉐이더 연결하면 보간 해서 구할 수 있음)를 빼서 벡터를 계산
        ``` C++
        - vertex shader -
        ...
        out vec3 vsNormal;
        out vec3 vsPos;
        void main(){
            gl_Position = projection * view * model * vec4(pos,1.0);
            // 월드 공간에서 라이팅 계산을 하기 위해 뷰, 투영 변환 적용 안함
            vsPos = vec3(model * vec4(pos, 1.0));
            vsNormal = normal;
        }
        ```
    - Diffuse Lighting컬러 계산하기
        ``` C++
        - fragment shader - 
        ...
        uniform vec3 lightPos;
        in vec3 vsNormal;
        in vec3 vsPos;
        void main(){
            ...
            vec3 norm = normalize(vsNormal);
            // 내적값이 음수가 안나오도록 max()함수 사용
            vec3 lightDir = normalize(lightPos - vsPos);
            float diff = max(dot(norm,lightDir),0.0);
            vec3 diffuse = diff * lightColor;
            vec3 result = (ambient + diffuse) * objectColor;
            fragColor = vec4(result, 1.0);
        }
        ```
    - 노멀 벡터 변환
        - 노멀 벡터도 월드 변환을 적용해야한다.(단순 행렬 곱셈은 안 됨)
        - 방향 벡터이기 때문에 이동 변환을 적용하면 안됨(논리적으로 의미가 없음)
        - 축 별로 다른 스케일링을 적용할 경우 노멀 벡터가 수직이 아니게 될 수 있다.
        - 노멀 벡터 변환을 위한 특수한 변환 행렬이 필요!
        - 이를 Normal Matrix라고 함(변환 행렬의 역행렬의 전치행렬을 구하면 됨)
        ``` C++
        - vertex shader -
        ...
        out vec3 vsNormal;
        out vec3 vsPos;
        void main(){
            gl_Position = projection * view * model * vec4(pos, 1.0);
            vsPos = vec3(model * vec4(pos, 1.0));
            vsNormal = mat3(transpose(inverse(model)))*normal;
        }
        ```
    - Specular Lighting
        - 광원의 빛이 정반사 되어 눈에 바로 들어오는 강한 빛
        - 광원을 향하는 벡터, 노멀 벡터, 그리고 카메라를 향하는 벡터를 이용해 계산
        - 표면에 반사된 광원 벡터와 카메라를 향하는 벡터를 내적하여 세기를 계산
    - 표면에 반사된 광원 벡터를 구하는 방법
        - 노멀 벡터와 내적을 이용한 연산을 하면 구할 수 있음
        - 고맙게도 GLSL에 reflect라는 함수가 있음
        ``` C++
        vec3 reflectDir = reflet(-lightDir, norm);
        ```
        - 노멀 벡터와 내적을 이용한 연산을 하면 구할 수 있음
        - 우리가 직접 할 수도 있다.
            ![image](https://user-images.githubusercontent.com/11372675/149628557-9713f69c-5c6f-48c5-bf95-3eac637c5cec.png)
    - Specular Lighting 컬러 계산하기
        1. 카메라 위치(=눈 위치)를 fragment shader uniform으로 넘기기
            ``` C++
            - fragment Shader - 
            uniform vec3 viewPos;
            ```
            ``` C++
            - render 함수 -
            vmath::vec3 viewPos = eye;
            glUniform3fv(glGetUniformLocation(shader_programs[1],"viewPos"),1,viewPos);
            ```
        2. 반사 벡터, 카메라를 향하는 뷰 벡터 구하기
            ``` C++
            - fragment shader -
            vec3 viewDir = normalize(viewPos - vsPos);
            vec3 reflectDir = reflect(-lightDir,norm);
            ```
        3. 스펙큘러 빛 컬러 계산
            ``` C++
            - fragment shader -
            float specularStrength = 0.5;
            int shininess =32;
            float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess);
            vec3 specular = specularStrength * spec * lightColor;

            vec3 result = (ambient + diffuse + specular) * objectColor;
            fragColor = vec4(result,1.0);
            ```