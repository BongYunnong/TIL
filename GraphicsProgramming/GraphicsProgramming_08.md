# 그래픽스 프로그래밍 #8 - 머터리얼과 라이팅맵
## Materials
- 재질
    - 현실 물체는 표면의 재질에 따라 빛을 반사하는 양과 방식이 다르다.
    - Phong Lighting model 각 요소의 값을 조절하여 재현해보자
        - object Color : 빛 반사 컬러
        - ambient lighting, Diffuse lighting, Specular lighting : 빛의 양
        - shininess : 하이라이트 크기
    ``` C++
    #version 430 core
    in vec3 vsNormal;
    in vec3 vsPos;

    uniform vec3 lightPos;
    uniform vec3 viewPos;
    uniform vec3 lightColor;
    uniform vec3 objectColor;
    out vec4 fragColor;

    void main(){
        //ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        //diffuse
        vec3 norm = normalize(vsNormal);
        vec3 lightDir = normalize(lightPos-vsPos);
        float diff = max(dot(norm, lightDir),0.0);
        int shininess =32;
        float spec = pow(max(dot(viewDir, reflectDir),0.0), shininess);
        vec3 specular = specularStrength * spec * lightColor;

        vec3 result = (ambient + diffuse + specular) * objectColor;
        fragColor = vec4(result, 1.0);
    }        
    ```
    - phong lighting model 계산 방법
        - Ambient, Diffuse, Specular 별로 빛의 양만 계산하고, 반사하는 정도는 Object Color로 동일하게 적용
        - Shininess와 같은 factor값이 하드코딩 되어 있음
- Material 구조체 정의
    - 라이팅 계산에 필요한 값들을 구조화해서 재질을 정의
    - Ambient, Diffuse, Specular 별로 반사 컬러를 정의해서 세부 조절이 가능하게 함
    - Shininess를 포함
    ``` C++
    - fragment shader -
    struct Material{
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float shininess;
    };
    uniform Material material;
    void main(){
        // ambient
        vec3 ambient lightColor * material.ambient;
        // diffuse
        vec3 norm = normalize(vsNormal);
        vec3 lightDir = normalize(lightPos - vsPos);
        float diff = max(dot(norm,lightDir),0.0);
        vec3 diffuse = lightColor * (diff * material.diffuse);
        // specular
        vec3 viewDir = normalize(viewPos - vsPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
        vec3 specular = lightColor * (spec * material.specular);

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result ,1.0);
    }
    ```
- Uniform 구조체 값 설정하기
    - 일반적인 uniform 값 설정과 동일
    ``` C++
    - render 함수 -
    vmath::vec3 ambient(1.0f, 0.5f, 0.31f);
    vmath::vec3 diffuse(1.0f, 0.5f, 0.31f);
    vmath::vec3 specular(0.5f, 0.5f, 0.5f);
    float shininess = 32.f;
    glUniform3fv(glGetUniformLocation(shader_programs[1], "material.ambient"), 1, ambient);
    glUniform3fv(glGetUniformLocation(shader_programs[1], "material.diffuse"), 1, ambient);
    glUniform3fv(glGetUniformLocation(shader_programs[1], "material.specular"), 1, ambient);
    glUniform1f(glGetUniformLocation(shader_programs[1], "material.shininess"), ambient);
    ```
    - 구조체 안의 값 하나하나마다 값을 불러와야한다.
    - 한 번에 Material을 보내는 것이 아님
- Light 구조체 정의
    - ambientStrength나 specularStrength와 같은 변수를 쓰지 말고 요소 별 빛의 세기를 쉐이더 프로그램 밖(어플리케이션)에서 조절이 가능하도록 만들자
    - Light 위치도 포함해서 구조체를 정의해보자
    ``` C++
    - fragment shader - 
    struct Light{
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
    uniform Light light;
    ```
- 변경된 프래그먼트 쉐이더
``` C++
- fragment shader - 
void main(){
    //ambient
    vec3 ambient = light.ambient * material.ambient;
    //diffuse
    vec3 norm = normalize(vsNormal);
    vec3 lightDir = normalize(light.position - vsPos);
    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    //specular
    vec3 viewDir = normalize(viewPos - vsPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
```
## Lighting Maps
- 재질을 넣었지만 사실적이지 않음
    - 일반적으로 물체는 다양한 재질이 섞여 있기 때문
    - 완벽히 깨끗한 단색 표면은 드물다.
    - -> 디테일 필요 -> 조명 계산에 텍스처 맵을 활용
- Diffuse Map
    - 객체의 diffuse 컬러 계산에 사용할 텍스처 맵을 뜻함
        - 사실 우리가 이미 배운 텍스처 맵핑과 적용 방법은 완전히 동일함
    - Material 구조체 업데이트
        - vec3 타입의 diffuse를 sampler2D 타입으로 변경(2D 텍스처)
        - ambient 컬러도 diffuse map과 동일하다는 가정으로 ambient 변수 삭제
        ``` C++
        - fragment shader - 
        struct Material{
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
            float shininess;
        };
        uniform Material material;
        ```
        - 위의 것을 아래 것으로 업데이트
        ``` C++
        - fragment shader -
        struct Material{
            sampler2D diffuse;
            vec3 specular;
            float shininess;
        };
        uniform Material material;
        in vec2 vsTexCoord;

        void main(){
            // ambient
            vec3 ambient = light.ambient * vec3(texture(material.diffuse, vsTexCoord));
            // diffuse
            vec3 norm = normalize(vsNormal);
            vec3 lightDir = normalize(light.position - vsPos);
            float diff = max(dot(norm, lightDir),0.0);
            vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,vsTexCoord));
            //specular
            ...
        }
        ```
        ``` C++
        - render - 
        vmath::vec3 specular(0.5f, 0.5f, 0.5f);
        float shininess = 32.f;
        glUniform3fv(glGetUniformLocation(shader_programs[1], "material.specular"), 1, specular);
        glUniform1f(glGetUniformLocation(shader_programs[1], "material.shininess"), shininess);
        glUniform1i(glGetUniformLocation(shader_programs[1], "material.diffuse"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        ```
    - Diffuse Map 사용 결과
        - 텍스처 맵과 함께 조명 효과가 동시에 표현됨
- Specular Map
    - 객체 표면 부분들의 Specular(하이라이트) 강도를 정읳는 텍스처 맵
        - Diffuse Map 텍스처와 대응
    - Material 구조체 업데이트
        - vec3 타입의 sepcular를 sampler2D 타입으로 변경(2D텍스처)
    ``` C++
    - fragment shader -
    struct Material{
        sampler2D diffuse;
        vec3 specular;
        float shininess;
    };
    uniform Materail material;
    in vec2 vsTexCoord;
    ```
    - 위의 것을 아래로 변경
    ``` C++
    - fragment shader - 
    struct Material{
        sampler2D diffuse;
        sampler2D specular;
        float shininess;
    };
    uniform Material material;
    inv vec2 vsTexCoord;

    void main(){
        ...
        //specular
        vec3 viewDir = normalize(viewPos - vsPos);
        vec3 reflelctDir = reflect(-lightDir,norm);
        float spec = pow(max(dot(viewDir, reflectDir),0.0), material.Shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.specular, vsTexCoord));
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result 1.0);
    }
    ```
    ``` C++
    - render - 
    float shininess = 32.f;
    glUniform1f(glGetUniformLocation(shader_programs[1],"material.shininess");shininess)
    glUniform1f(glGetUniformLocation(shader_programs[1],"material.diffuse"),0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE2D, textures[1]);
    glUniform1i(glGetUniformLocation(shader_programs[1],"material.specular",1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE[2]);
- 이렇게 하면 필요한 부분만 specular를 줄 수 있음