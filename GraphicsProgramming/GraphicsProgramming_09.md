# 그래픽스 프로그래밍 #9 - 다양한 광원 스타일
## 다양한 광원 스타일
- Point Light(점 광원)
    - 광원을 향한 각도를 계산하여 밝기를 결정
    - 광원이 멀어져도 밝기는 안 변함(광원까지의 거리가 밝기에 영향을 안 줌.)
## Directional Light
- 정의
    - 빛의 방향으로만 정의되는 광원
        - 빛이 크고 강한 광원이 아주 멀리 있는 것을 묘사(ex. 태양 빛)
        - 광원이 아주 멀리 있는 경우 모든 표면에 닿는 빛의 양과 각도는 동일해짐
- OpenGL 구현
    - 광원 위치 벡터 대신에 방향 벡터만 사용
        - 광원을 향하는 벡터로 정의하든, 광원으로부터 들어오는 방향(일반적)으로 벡터를 정의하든 상관 없음
        ``` C++
        - fragment shader -
        struct Light{
            vec3 direction;
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };
        uniform Light light;
        ...
        void main(){
            ...
            // vec3 lightDir = normalize(lightPos-vsPos);
            // 나머지 계산은 동일!
            vec3 lightDir = normalize(-light.direction);
            ...
        }
        ```
        ``` C++
        - render
        glUniform3f(glGetUniformLocation(shader_programs[1], "light.direction"),-0.2f,-1.0f,-0.3f);
        glUniform3f(glGetUniformLocation(shader_programs[1], "light.ambient"),0.05f,0.05f,0.05f);
        glUniform3f(glGetUniformLocation(shader_programs[1], "light.diffuse"),0.4f,0.4f,0.4f);
        glUniform3f(glGetUniformLocation(shader_programs[1], "light.specular"),0.5f,0.5f,0.5f);
        ```
## Point Light
- 정의
    - 한 점에서 빛의 사방으로 퍼지는 광원(ex. 전구)
        - 광원의 위치가 중요
        - 거리에 따라 빛의 밝기는 점점 줄어듦(Attenuation) - 수학적 정의가 필요!
- Attenuation 공식
    - 밝기에 대한 퍼센트를 계산(0.0~1.0)
        - 거리에 대해 반 비례하도록 작성 필요
        - ex. 1/(length(lightPos-vsPos)) or1/(length(lightPos-vsPos))<sup>2</sup>
    - OpenGL에서 많이 쓰이는 공식
        - 빛이 감소되는 정도를 프로그래머가 조정할 수 있음
        - 1/(1+c<sub>1</sub> * d + c<sub>2</sub> * d<sup>2</sup>)
            - c<sub>1</sub> : 거리에 따라 선형적으로 감소하는 정도
            - c<sub>2</sub> : 거리의 제곱에 따라 비선형적으로 감소하는 정도
            - 1을 더해주는 이유 : 거리가 0일 경우, 1.0이 되도록 하기 위함(나눗셈 오류 방지)
        - 광원이 커버하는 거리에따른 c<sub>1</sub>, c<sub>2</sub>는 정해져있음
    - 광원의 3차원 위치와 Attenuation 파라미터 포함
        ``` C++
        - fragment shader -
        struct Light{
            vec3 position;
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
            float c1, c2;
        };
        uniform Light light;
        ...
        void main(){
            ...
            float dist = length(light.position-vsPos);
            float attenuation = 1.0/(1.0 + light.c1 *dist + light.c2*dist*dist);
            ...
            vec3 result = (ambient + diffuse + specular) * attenuation;
            fragColor = vec4(result, 1.0);
        }
        ```
        ``` C++
        - render -
        glUniform3fv(glGetUniformLocation(shader_programs[1], "light.position"),1,lightPos);
        glUniform3f(glGetUniformLocation(shader_programs[1],"light.ambient"),0.1f,0.1f,0.1f);
        glUniform3f(glGetUniformLocation(shader_programs[1],"light.diffuse"),0.8f,0.8f,0.8f);
        glUniform3f(glGetUniformLocation(shader_programs[1],"light.specular"),1.0f,1.0f,1.0f);
        glUniform1f(glGetUniformLocation(shader_programs[1],"light.c1"),0.09f);
        glUniform1f(glGetUniformLocation(shader_programs[1],"light.c2"),0.032f);
        ```
## Spotlight
- 정의
    - 빛을 특정 방향으로만 내보내는 광원
        - 특정 방향으로 정해진 원형 범위 안에 들어와 있는 물체만 빛을 받음
    - 광원의 3차원 위치
    - Spot 방향
    - Cutoff 각도
        - 빛을 받는 원형 영역을 결정
- 계산 방법
    - 각 프래그먼트에 대해서
        1. 프래그먼트에서 광원 위치를 빼서 lightDir 벡터 구하기
        2. lightDir과 spotDir 사이의 각도 $\theta$ 구하기
        3. $\theta$ 가 Cutoff 각도보다 작으면 밝기 계산하기
- OpenGL 구현
    ``` C++
    - fragment shader -
    struct Light{
        vec3 position;
        vec3 direction;
        float cutOff;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
    uniform Light light;
    ...
    void main(){
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, vsTexCoords));
        vec3 lightDir = normalize(light.position-vsPos);
        float theta = dot(lightDir,normalize(-light.direction));
        if(theta > light.cutOff){   // 코사인 값이기 때문에 부등호가 반대
            // Diffuse, Specular 라이팅 연산 수행
        }else{
            fragColor = vec4(ambient,1.0);
        }
    }
    ```
    ``` C++
    - render -
    glUniform3fv(glGetUniformLocation(shader_programs[1],"light.position"),1,eye);
    glUniform3fv(glGetUniformLocation(shader_programs[1],"light.direction"),1,center-eye);
    glUniform1f(glGetUniformLocation(shader_programs[1],"light.cutOff"),(float)cos(vamth::radians(12.5)));
    glUniform3f(glGetUniformLocation(shader_programs[1],"light.ambient"),0.2f,0.2f,0.2f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"light.diffuse"),1.0f,1.0f,1.0f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"light.specular"),1.0f,1.0f,1.0f);
    ```
- 소프트 엣지
    - 소프트 엣지 영역을 outerCutoff로 하나 더 정의
        - cutoff와 outer cutoff 사이에 밝기가 점점 어두워지도록 계산(1.0->0.0)
    - 구현
        - clamp() 함수를 이용해 0.0~1.0을 벗어나지 않도록 제한
        ``` C++
        - fragment shader -
        struct Light{
            vec3 position;
            vec3 direction;
            float cutOff;
            float outerCutOff;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };
        uniform Light light;

        void main(){
            ...
            float theta = dot(lightDir, normalize(-light.direction));
            float epsilon = light.cutOff - light.outerCutOff;
            float intensity = clamp((theta-light.outerCutOff)/epsilon,0.0,1.0);
            ...
            // ambient 값은 건드리지 않는다. 최소한의 빛은 유지하기 위해서
            diffuse *= intensity;
            specular *= intensity;
        }
        ```
        ``` C++
        - render -
        glUniform1f(glGetUniformLocation(shader_programs[1],"light.cutOff"),(float)cos(vmath::radians(12.5)));
        glUniform1f(glGetUniformLocation(shader_programs[1],"light.outerCutOff"),(float)cos(vmath::radians(15.5)));
        ```
## Multiple Lights
- 현실은 다양한 광원이 복합적으로 작용
    - Directional Light, Point Light, SpotLight가 동시에 적용
- 모든 광원을 쉐이더로 전달해서 합치기
    - 각 프래그먼트 마다 모든 광원들에 대한 밝기를 계산해서 더하면 됨
    ``` C++
    struct Material{
        sampler2D diffuse;
        sampler2D specular;
        float shininess;
    };
    struct DirLight{
        vec3 direction;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
    struct PointLight{
        vec3 position;
        float c1;
        float c2;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
    struct SpotLight{
        vec3 position;
        vec3 direction;
        float cutOff;
        float outerCutOff;
        float c1;
        float c2;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
    #define NUM_POINT_LIGHTS 2
    uniform Material material;
    uniform vec3 viewPos;
    uniform DirLight dirLight;
    uniform PointLight pointLights[Num_Point_LIGHTS];
    uniform SpotLight spotLight;

    glUniform3f(glGetUniformLocation(shader_programs[1],"dirLight.direction"),-1.0f,0.0f,0.0f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"dirLight.ambient"),0.05f,0.05f,0.05f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"dirLight.diffuse"),0.4f,0.4f,0.4f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"dirLight.specular"),0.5f,0.5f,0.5f);

    glUniform3fv(glGetUniformLocation(shader_programs[1],"pointLight[0].position"),1,pointLightPos[0]);
    glUniform3f(glGetUniformLocation(shader_programs[1],"pointLight[0].ambient"),0.05f,0.05f,0.05f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"pointLight[0].diffuse"),0.8f,0.8f,0.8f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"pointLight[0].specular"),1.0f,1.0f,1.0f);
    glUniform1f(glGetUniformLocation(shader_programs[1],"pointLight[0].c1"),0.09f);
    glUniform1f(glGetUniformLocation(shader_programs[1],"pointLight[0].c2"),0.032f);
    glUniform3fv(glGetUniformLocation(shader_programs[1],"pointLight[1].position"),1,pointLightPos[1]);
    glUniform3f(glGetUniformLocation(shader_programs[1],"pointLight[1].ambient"),0.05f,0.05f,0.05f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"pointLight[1].diffuse"),0.8f,0.8f,0.8f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"pointLight[1].specular"),1.0f,1.0f,1.0f);
    glUniform1f(glGetUniformLocation(shader_programs[1],"pointLight[1].c1"),0.09f);
    glUniform1f(glGetUniformLocation(shader_programs[1],"pointLight[1].c2"),0.032f);
    
    glUniform3fv(glGetUniformLocation(shader_programs[1],"spotLight.position"),1,eye);
    glUniform3fv(glGetUniformLocation(shader_programs[1],"spotLight.direction"),1,center-eye);
    glUniform1f(glGetUniformLocation(shader_programs[1],"spotLight.cutOff"),(float)cos(vmath::radians(12.5)));
    glUniform1f(glGetUniformLocation(shader_programs[1],"spotLight.outerCutOff"),(float)cos(vmath::radians(15.5)));
    glUniform1f(glGetUniformLocation(shader_programs[1],"spotLight.c1"),0.09f);
    glUniform1f(glGetUniformLocation(shader_programs[1],"spotLight.c2"),0.032f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"spotLight.ambient"),0.0f,0.0f,0.0f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"spotLight.diffuse"),1.0f,1.0f,1.0f);
    glUniform3f(glGetUniformLocation(shader_programs[1],"spotLight.specular"),1.0f,1.0f,1.0f);

    // 광원별 컬러 계산 함수 정의
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
    vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

    void main(){
        vec3 norm = normalize(vsNormal);
        vec3 viewDir = normalize(viewPos-vsPos);

        // directional lighting
        vec3 result = CalcDirLight(dirLight, norm, viewDir);

        // point lights
        for(int i=0;i<NUM_POINT_LIGHTS;i++){
            result += CalcPointLight(pointLights[i],norm,vsPos,viewDir);
        }

        // spot light
        result += CalcSpotLight(spotLight, norm, vsPos, viewDir);

        fragColor = vec4(result, 1.0);
    }

    // directional light 계산 함수
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
        vec3 lightDir = normalize(-light.direction);
        // diffuse shading
        float diff = max(dot(normal, lightDir),0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
        // combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, vsTexCoord));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,vsTexCoord));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, vsTexCoord));

        return (ambient + diffuse + specular);
    }
    // point light 계산 함수
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fraPos, vec3 viewDir){
        vec3 lightDir = normalize(light.position -fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir),0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec =pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
        // attenuation
        float distance = length(light.position -fragPos);
        float attenuation = 1.0/(1.0+light.c1 * distance + light.c2 * (distance*distance));
        // combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, vsTexCoord));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,vsTexCoord));
        vec3 specular = light.specular * spec * vec3(texture(material.specular,vsTexCoord));

        return (ambient + diffuse + specular)*attenuation;
    }
    // spot light 계산 함수
    vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
        vec3 lightDir =normalize(light.position-fragPos);
        //diffuse shading
        float diff = max(dot(normal, lightDir),0.0);
        //speuclar shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
        // soft edge spotLIght intensity
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta-light.outerCutOff)/epsilon, 0.0, 1.0);
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0/(1.0+light.c1 * distance + light.c2*(distance*distance));
        // combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, vsTexCoord));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, vsTexCoord));
        vec3 specular = light.specular * spec * vec3(texture(material.specular,vsTexCoord));
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;

        return (ambient + diffuse + specular);
    }
    ```