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
        - GL_REPEAT
        - GL_MIRROED_REPEAT
        - GL_CLAMP_TO_EDGE
        - GL_CLAMP_TO_BOARDER
    - glTexParameteri() 함수로 축 별로 설정
        ``` C++
        // 0: 타겟 텍스쳐, 1: 설정할 축 명시(S-가로,T-세로), 2: WRapping 모드 명시
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        ```