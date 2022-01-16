# 그래픽스 프로그래밍 #6 - 데이터 2
## Element Buffer Objects (EBO)
- 사각형을 그리려면 삼각형 2개로 나누어 렌더링 한다.
    ``` C++
    GLfloat vertices[] ={
        // 첫 번째 삼각형
        0.25f, 0.25f, 0.5f,
        -0.25f, 0.25f, 0.5f,
        -0.25f, -0.25f, 0.5f,
        // 두 번째 삼각형
        0.25f, 0.25f, 0.5f,
        -0.25f, -0.25f, 0.5f,
        0.25f, -0.25f, 0.5f
    }
    ```
    - 총 6개의 점을 입력해야한다.
        - 만약 사각형보다 더 복잡한 모델이라면? 비효율적임!
        - v0와 v3의 좌표, v2와 v4의 좌표가 같음
    - 겹치는 부분을 없앨 수는 없을까?
        - 첫 번째 삼각형은 v0-v1-v2
        - 두 번째 삼각형은 v0-v2-v3으로..
- Element Buffer Objects
    - OpenGL이 그려야 할 버텍스의 인덱스들을 저장
        - Indexed Drawing이라고도 함
        ``` C++
        // 사각형 네점의 위치와 컬러를 정의한다.
        GLfloat vertices[] ={
            0.25f, 0.25f, 0.5f, 1.0f, 0.0f, 0.0f,   //우측 상단
            -0.25f,0.25f,0.5f,0.0f,1.0f,0.0f,       //좌측 상단
            -0.25f,-0.25f,0.5f,0.0f,0.0f,1.0f,      //좌측 하단
            0.25f,-0.25f,0.5f,1.0f,1.0f,0.0f        //우측 하단
        };
        // 삼각형으로 그릴 인덱스를 정의한다.
        GLuint indices[]={
            0, 1, 2,    //첫 번째 삼각형
            0, 2, 3     //두 번째 삼각형
        }
        ```
        - VBO와 유사함
            - 타겟 버퍼만 GL_ELEMENT_ARRAY_BUFFER로 설정하면 된다.
        ``` C++
        // EBO를 생성하여 indices 값들을 복사
        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        ```
    - glDrawElements()
        - EBO에서 제공하는 인덱스를 사용해 그리라고 명령
        ``` C++
        // EBO를 활용해 사각형을 그린다(삼각형 두개)
        // 0 : 프리미티브 모드 설정(glDrawArrays와 유사), 1: 총 그릴 버텍스(인덱스) 개수, 2: 인덱스 데이터 타임, 3: 버퍼 오프셋
        glDrawElement(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        ```
    - 결과물
        - VBO를 VAO가 저장하고, EBO도 VAO에 저장된다.
        ![image](https://user-images.githubusercontent.com/11372675/149615627-ca3542c4-9f98-4b72-ba89-cd5cb83ee842.png)
## 텍스처
- 텍스처를 사용하는 이유
    - 더 사실적인 렌더링 이미지를 위해
        - 점 개수를 늘리고, 점 색상을 다 지정하는 것은 어렵다.
    - 각 버텍스가 텍스처 이미지의 어디에 위치하는지 설정
        - 나머지 fragment들은 보간(interpolation)하여 결정된다.
- Texture Coordinates
    - 2차원으로 표현(각 축을 보통 u,v나 s,t로 표현)
        - 좌측 하단이 원점
        - 가로 세로 해상도 모두 1로 정규화
        ``` C++
        GLfloat texCoords[] ={
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.5f, 1.0f
        };
        ```
- Texture Wrapping
    - 텍스처 좌표가(0,0) 부터 (1,1) 사이가 아닐 경우 처리 방법
        - GL_REPEAT             // repeat
        - GL_MIRROED_REPEAT     // repeat하는데, 반전되도록
        - GL_CLAMP_TO_EDGE      // 마지막 픽셀값으로 늘리기
        - GL_CLAMP_TO_BOARDER   // 우리가 정한 색깔로 지정
    - glTexParameteri() 함수로 축 별로 설정
        ``` C++
        // 0: 타겟 텍스쳐, 1: 설정할 축 명시(S-가로,T-세로), 2: WRapping 모드 명시
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        ```
        - GL_CLAMP_TO_BOARDER옵션을 선택한 경우, glTexParameterfv() 함수로 보더 색상을 명시해야 함
        ``` C++
        // 4개 요소를 가진 float 배열을 넘긴다. -> RGBA
        float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BOARDER_COLOR, borderColor);
        ```
- Texture Filtering
    - 텍스처로부터 픽셀 값(컬러)을 읽어오는 방법을 정의!
        - 왜? 실제 렌더링 픽셀과 텍스쳐 픽셀(a.k.a. texel)이 정확히 일치하지 않기 때문
    - GL_NEAREST
        - nearest neighbor or point filtering
        - 가장 가까운 픽셀 값을 그대로 가져옴
        - -> 각이 져 보임(blocked patterns)
    - GL_LINEAR
        - (bi)linear filtering
        - 주변 4개 픽셀을 이용해서 최종 픽셀 값을 계산
        - -> 더 부드럽지만 흐린 듯한 이미지
    - glTexParameteri() 함수로 확대/ 축소 별로 설정
        ``` C++
        // 1 : 확대 or 축소 동작 설정(MIN-축소,MAG-확대)
        // 2 : Filtering 옵션 지정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        ```
- Miamaps
    - 동일한 텍스처를 가진 오브젝트가 여기 저기 있다고 생각해보자.
        - 어떤 오브젝트는 멀리 있고, 어떤 오브젝트는 가까이 있고...
            - 거리에 따라 최종 프래그먼트 수가 다 다르다.
            - 멀리 있는 오브젝트는 몇 개 안 됨
            - 눈에 띄는 앨리어싱이 발생할 수 있다.
    - 다양한 크기의 텍스처 이미지를 거리에 따라 사용하여 해결 가능
        - 거리가 멀어지면 더 작은 크기의 텍스처 이미지를 사용
        - 밉맵 레벨이 증가할수록 면적이 1/4씩 줄어듦

        ![image](https://user-images.githubusercontent.com/11372675/149622260-c9cdff62-a8be-42be-9f75-acef7e985dbb.png)
        - glGenerateMipmaps() 함수로 간편하게 생성 가능!
    - 밉맵 레벨이 바뀔 때 눈에 띌 수 있음(갑자기 텍스처 해상도가 바뀌니까...)
        - 텍스처 필터링 방식을 밉맵 스위칭에도 활용이 가능
            - level 1 mipmap에서 level 2 mipmap으로 넘어갈 때 두 mipmap을 활용할 수 있음
        - 옵션 설정도 함께 함
            | 1번 parameter  | 2번 parameter  |
            |:---:|:---:|
            | GL_NEAREST_MIAMAP_NEARET | 밉맵 스위칭 Nearest, 텍스처 필터링 Nearest|
            | GL_LINEAR_MIAMAP_NEARET | 밉맵 스위칭 Nearest, 텍스처 필터링 Linear|
            | GL_NEAREST_MIAMAP_LINEAR | 밉맵 스위칭 Linear, 텍스처 필터링 Nearest|
            | GL_LINEAR_MIAMAP_LINEAR | 밉맵 스위칭 Linear, 텍스처 필터링 Linear|
        
        ``` C++
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        ```
- 텍스처 이미지 불러오기
    - stb_image.h
        - 이미지 파일을 읽어 오기 위한 외부 라이브러리
        - 싱글 헤더 라이브러라(by Sean Barrett)
    - 설치법
        - 헤더파일 다운로드
        - src\_myApp_ 폴더에 복사
        - 비쥬얼스튜디오 "add -> Existing item" 선택하여 헤더 파일 추가
    - 사용법
        - _myApp_.cpp에 아래 코드 추가
            ``` C++
            #define STB_IMAGE_IMPLEMENTATION
            #include "stb_image.h"
            ```
        - 아래 코드를 통해 이미지의 픽셀 데이터를 unsigned char 배열로 저장
            ``` C++
            // 텍스처 이미지 로드하기
            int width, height, nrChannels;
            unsigned char *data = stbi_load("../../src/_myApp_/wall.jpg", & width, &height, &nrChannels, 0);
            ```
- 텍스처 만들기
    - 시작은 지금까지 했던 OpenGL 객체와 유사
        ``` C++
        GLuint texture;
        // 0: 생성할 텍스쳐 객체 개수, 1: 텍스쳐 객체 ID 저장 변수
        glGenTextures(1, &texture);
        // 0: 타겟하는 텍스처 Object 타입 설정. 우리는 2D이미지이니 GL_TEXTURE_2D
        glBindTexture(GL_TEXTURE_2D, texture);
        ```
    - 이미지 데이터 복사하여 텍스쳐 만들기
        ``` C++
        // 0: 타겟 텍스쳐, 1: 밉맵 생성(0이면 자동 생성), 2: 텍스쳐 저장할 픽셀 포맷, 3: 가로 해상도, 4: 세로 해상도, 5: ..? 6, 7: 로드한 이미지 데이터 포맷 명시, 8: 실제 이미지 데이터
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        ```
    - 코드
        ``` C++
        // 텍스쳐 객체 만들고 바인딩
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // 텍스쳐 이미지 로드하기
        int width, height, nrChannels;
        unsigned char *data = stbi_load("../../src/_myApp_/wall.jpg", &width, &height, &nrChannels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // 밉맵 생성
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        // 텍스쳐 다 만들고 난 뒤엔 반드시 메모리 해제
        stbi_image_free(data);
        // 텍스처 샘플링/ 필터링 설정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        ```
    - 쉐이더에서 텍스쳐 사용하기
        - 사각형 그리기 예제에 이이서...
            - 버텍스 버퍼 오브젝트에 텍스처 좌표도 추가
            - 나머지 VBO 생성 관련은 동일
            ``` C++
            // 사각형 네점 위치와 컬러, 텍스처 좌표를 정의한다.
            GLfloat vertices[] ={
                // 3차원 위치         //컬러              //텍스처 좌표
                0.25f,0.25f,0.5f,    1.0f,0.0f,0.0f,    1.0f,1.0f,  //우측상단
                -0.25f,0.25f,0.5f,   0.0f,1.0f,0.0f,    0.0f,1.0f,  //좌측상단
                -0.25f,-0.25f,0.5f,  0.0f,0.0f,1.0f,    0.0f,0.0f,  //좌측하단
                0.25f,-0.25f,0.5f,   1.0f,1.0f,0.0f,    1.0f,0.0f  //우측하단
            };
            ```
    - Vertex Attributes 연결하기
        - 텍스처 좌표를 버텍스 속성으로 연결(location = 2)
        - 텍스쳐 좌표 데이터가 추가됨에 따라 stride와 offset 조정
        ![image](https://user-images.githubusercontent.com/11372675/149621999-659e08fe-5506-46fb-a6c2-330d638e9fc6.png)
        ``` C++
        // VBO를 나누어서 각 버텍스 속성으로 연결
        // 위치 속성 (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // 컬러 속성 (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        // 텍스처 좌표 속성 (location = 2)
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);
        ```
    - 버텍스 쉐이더 작성
        - (locaiton =2) 텍스처 좌표를 버텍스 아웃 변수로 연결
        ``` C++
        #version 430 core
        layout(location=0) in vec3 pos;
        layout(location=1) in vec3 color;
        layout(location=2) in vec2 texCoord;

        uniform mat4 rotMat;

        out vec3 vsColor;
        out vec2 vsTexCoord;

        void main(void){
            gl_Position = rotMat*vec4(pos.x,pos.y,pos.z,1.0);
            vsColor = color;
            vsTexCoord = texCoord;
        }
        ```
    - 프래그먼트 쉐이더 작성
        - 인터플레이션된 텍스쳐 좌표(2차원)로 실제 픽셀 값을 가져옴
        ``` C++
        #version 430 core
        in vec3 vsColor;
        // 인터폴레이션 된 텍스처 좌표
        in vec2 vsTexCoord;
        // 만들어서 바인딩한 텍스쳐 이미지(uniform 데이터)
        uniform sampler2D texture1;
        out vec4 fragColor;

        void main(void){
            // 실제 픽셀 값 vec4(RGBA)을 가져오는 함수
            fragCOlor = texture(texture1, vsTexCoord);
        }
        ```
    - 그리기 전에 사용하고자 하는 텍스처 바인딩하기
        ``` C++
        virtual void render(double currentTime){
            ...
            // 텍스쳐를 bind한다.
            glUniform1i(glGetUniformLocation(rendering_program, "texture1"),0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);

            // 미리 설정한 VAO를 그리기 위해 binding
            // glActiveTexture()함수가 glBindTexture()함수보다 먼저 와야 함
            glBindVertexArray(VAO);
            // EBO를 활용해 사각형을 그린다.(삼각형 두개)
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            ...
        }
        ```
    - 결과물

        ![image](https://user-images.githubusercontent.com/11372675/149622225-296434c8-c99b-4b3b-ad2b-04a922921af4.png)
    - 색깔을 넣어보자
        - fragColor= texture(texture1, vsTexCoord)*vec4(vsColor,1.0);

        ![image](https://user-images.githubusercontent.com/11372675/149622242-3d036095-0e7c-4c24-9b6f-ce65e0596cca.png)