# 그래픽스 프로그래밍 #10 - 프레임 버퍼
## Depth Buffer
- OpenGL에서 사용하는 메모리 공간
- Depth Testing
    - Fragment의 깊이(카메라로 부터의 거리)에 따라 그릴지 결정
        - draw 함수 콜 순서가 아니라 깊이에 따라 정렬된 결과물
        - Depth testing을 안하면 그리는 순서에 따라 물체가 그려짐
        - depth testing을 적용하면 정상적으로 출력됨
- fragment의 깊이 값
    - Screen Coordinates에서 Z값
        - 범위 : 0.0~1.0 (카메라에 가까울수록 낮은 값)
        - Fragment Shader에서 OpenGL 내장 변수를 통해 확인 가능
            - ex. gl_FragCoord.z
- Depth Testing 동작 원리
    - Depth Buffer를 활용해 가장 가까운 Fragment만 렌더링
        - Color Buffer와 동일한 해상도의 추가 메모리를 활용해 깊이 값을 임시로 저장
        - 깊이 값만 저장하기 때문에 싱글 채널
            - 보통 24bit float 타입 활용
            - 싱글 채널이지만 깊이 값을 8비트로만 표현하면 해상도가 너무 안 좋기에 25bit 사용
    - 현재 그릴 Fragment의 z값을 Depth Buffer에서 동일한 위치에 저장된 Z값과 비교(Fragment의 X, Y값을 활용해 버퍼 위치 접근)
        - 현재 Fragment의 Z값이 더 크다면 건너뛰기
        - 현재 Fragment의 Z값이 더 작다면(가깝다면) ColorBuffer에 그리기, 현재 Z값으로 Depth Buffer업데이트
- OpenGL 구현
    - 다행히 자세한 알고리즘은 우리가 직접 구현할 필요 없다.
    ``` C++
    virtual void render(double currentTime){
        // 이전 프레임의 버퍼를 다 지우고 다시 Depth test
        const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR,0,black);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        ...
    }
    ```
## Stencil Buffer
- Stencil Testing
    - Depth Testing처럼 Fragment를 그릴지 결정하는 또다른 방법
        - '스텐실 공예'처럼 마스킹을 하는 개념
    - 마스킹 정보를 Stencil Buffer라는 OpenGL 메모리에 저장
        - Color Buffer, Depth Buffer와 동일한 해상도
        - 마스킹 값만 저장하기 때문에 싱글 채널(보통 8bit 타입 활용)
        - Stencil Buffer에 있는 값을 보고 그릴지 말지 결정
            - 로직은 우리가 어느 정도 정할 수 있음
- 활용 예시
    - 3D 객체 아웃라인 렌더링
        - 게임에서 캐릭터를 선택한 것을 알려주기 위해 많이 사용
        - 객체를 조금 더 크게 단색으로 그리는 방식
        - 이때, 이미 렌더링된 객체의 영역을 그리지 않기 위해 Stencil Testing을 활용
    - 박스를 동일 위치에 조금 더 크게 그리는데, stencil buffer를 설정하여 이미 렌더링된 객체의 영역을 빼고 그리도록 함
        - 기존 렌더링 할 때, 상자에 stencil buffer를 1로 채워라!

## Frame Buffer
- 정의
    - Rendering된 결과물이 적용되는 대상(Render Target)
        - Color Buffer, Depth Buffer, Stencil Buffer의 콜렉션
- 기본 프레임버퍼
    - 어플리케이션 윈도우로 연결되어 있음
        - 따라서 렌더링 윈도우 이미지가 업데이트 되는 것임
    - 이것을 Texture로 저장되게 하여 사용할수도 있음
        ![image](https://user-images.githubusercontent.com/11372675/149683334-9ee17b5c-3df0-4070-b3d6-d4c7333e402a.png)
- 구현
    1. 프레임버퍼 생성하기
        - VAO, VBO등과 
        - GLuint FBO는 사실 sb6.h에 이미 정의되어있음
        ``` C++
        virtual void startup(){
            ...
            GLuint FBO;
            glGenFramebuffers(1, &FBO);
        }
        ```
    2. Color/Depth/Stencil Buffer 생성 및 연결하기
        - Framebuffer Object 자체는 렌더링한 결과를 저장할 메모리가 없다.
            - Color/Depth/Stencil Buffer로 사용할 공간을 만들어서 연결해줘야 함
        - Color/Depth/Stencil Buffer로 사용할 수 있는 공간
            - Texture : Rendering한 결과물의 값을 읽어와서 사용할 경우 주로 사용
            - Render Buffer Object : 결과물의 값을 읽어올 필요가 없는 경우
                - 기본 프레임버퍼가 사용하는 공간, Texture에 렌더링 하는 것 보다 더 효율적인 연산 가능
        - Color Buffer 생성 및 연결
            ``` C++
            virtual void startup(){
                ...
                glBindFramebuffer(GL_FRAMEBUFFER, FBO);
                // color buffer 텍스처 생성 및 연결
                GLuint FBO_texture;
                glGenTextures(1, &FBO_texture);
                glBindTexture(GL_TEXTURE_2D, FBO_texture);
                // 윈도우 해상도 전달
                // NULL : 실제 우리가 전달하는 데이터는 없음. 나중에 framebuffer로 자동으로 채워질 것임
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,info.windowWidth,info.windowHeight,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                // 프레임 버퍼에 연결
                // 왜 굳이 인자로 GL_FRAMEBUFFER를 넘겨줄까? 사실 읽기전용, 쓰기전용 이렇게 넘겨줄 수 있는데, GL_FRAMEBUFFER를 인자로 넘겨주면 읽기, 쓰기 다 하겠다는 이야기
                glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBO_texure, 0);
                ...
                //depth & stencil buffer를 위한 Render Buffer Obect 생성 및 연결
                GLuint RBO;
                glGenRenderbuffers(1,&RBO);
                glBindRenderbuffer(GL_RENDERBUFFER,RBO);
                // GL_DEPTH24_STENCIL8 : Depth와 Stencil을 한번에 생성
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, info.widowWidth, info.windowHeight);
                // 프레임버퍼에 연결
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
            }
            ```
    3. 잘 만들어졌는지 체크
        - Depth/Stencil Buffer 생성 및 연결
        ``` C++
        virtual void startup(){
            ...
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                glfwTerminate();    // 프로그램을 종료시키는 함수
            glBindFrameBuffer(GL_FRAMEBUFFER,0);
        }
        ```
    4. (1<sup>st</sup> Pass) Rendering To FBO Texture
        - 생성한 FBO를 바인딩하고 렌더링 관련 함수 콜을 하면 된다.
        ``` C++
        virtual void render(double currentTime){
            // FBO 바인딩
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
            // FBO에 연결된 버퍼들의 값을 지우고, 뎁스 테스팅 활서오하
            glClearColor(0.0f,0.0f,0.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            // 지금부터 렌더링한 결과물은 우리가 만든 프레임 버퍼에 저장된다.
        }
        ```
    5. (2<sup>nd</sup> Pass) Rendering to App Window
        1. 프로그램 창에 연결된 기본 Framebuffer를 다시 바인딩
        2. 1<sup>st</sup>Pass의 FBO Texture를 이용해 렌더링
            ``` C++
            virtual void render(double currentTime){
                ...
                // 기본 Framebuffer로 되돌리기
                glBindFramebuffer(GL_FRAMEBUFFER,0);
                glDisable(GL_DEPTH_TEST);
                // 버퍼들의 값 지우기
                glClearColor(0.5f,0.5f,0.5f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                // FBO Texture를 쉐이더 프로그램에 연결
                glUniform1i(glGetUniformLocation(shader_programs[0],"texture1"),0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, FBO_texture);
                // 박스 그리기
            }
            ```
## Post Processing
- 렌더링된 이미지에 효과를 추가해보자.
- 이미지 프로세싱
    - 2차원 이미지 컬러 값들을 처리하는 다양한 방법
    - 블러 / 샤픈 / 엣지
- Convolution Filtering
    - 기존 텍스처가 FBO texture, 결과물 렌더링된 이미지 중간에 kernel이 존재
    - 주변 픽셀들을 커널(Kernel)에 대응되는 값(가중치)를 곱하고 모두 더하여 새로운 픽셀 값을 얻는 방법
        - 공간 영역 필터링
        - 커널의 값과 크기에 따라 다양한 효과 적용 가능
- OpenGL 렌더링에 어떻게 적용이 가능할까?
    - Framebuffer를 활용한 2Pass 렌더링을 통해 구현
        1. FBO 텍스처에 렌더링 이미지 저장
        2. 사각형 평면에 텍스처 맵핑하고, 프래그먼스 쉐이더에서 필터링 연산 
- 2<sup>nd</sup> Rendering 용 스크린 객체 설정
    - 윈도우를 다 채워야 하니까 간단하게 NDC 좌표로 설정
        ``` C++
        - startup - 
        // Post-Processing용 스크린 정의
        GLfloat screenVertices[] ={
            // NDC xy좌표 // 텍스처 UV
            -1.0f,1.0f,   0.0f,1.0f,
            -1.0f,-1.0f,  0.0f,0.0f,
            1.0f,-1.0f,   1.0f,0.0f,

            -1.0f,1.0f,   0.0f,1.0f,
            1.0f,-1.0f,   1.0f,0.0f,
            1.0f,1.0f,    1.0f,1.0f,
        };
        // VAO, VBO 설정은 동일
        // glVertexAttribPointer 설정시 stride, offset 설정 주의!
        ```
    - 아주 단순한 텍스처링 쉐이더
        ``` C++
        - vertex shader - 
        #version 430 core
        layout(location=0) in vec2 pos;
        layout(location=1) in vec2 texCoord;
        out vec2 vsTexCoord;
        void main(){
            gl_Position=vec4(pos.x,pos.y,0.0,1.0);
            vsTexCoord = texCoord;
        }
        ```
        ``` C++
        - fragment shader -
        #version 430 core
        out vec4 fragColor;
        in vec2 vsTexCoord;
        uniform sampler2D screenTexture;
        void main(){
            fragColor = texture(screenTexture, vsTexCoord);
        }
        ```
        ``` C++
        - render -
        // 1st rendering
        // 2nd rendering
        // 기본 Framebuffer로 되돌리기
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glDisable(GL_DEPTH_TEST);
        // 버퍼들의 값 지우기
        glClearColor(0.5f,0.5f,0.5f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // FBO Texture를 스크린 쉐이더 프로그램에 연결
        glUseProgram(shader_program_screen);
        glUniform1i(glGetUniformLocation(shader_program_screen, "screenTexture"),0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, FBO_texture);
        glBindVertexArray(VAO_screen);
        glDrawArrays(GL_TRIANGLES,0,6);
        ```
- 엣지 검출 필터링
    - 프래그먼트 쉐이더에 컨볼루션 연산을 구현
    
    | 1 | 1 | 1 |
    |:--:|:--:|:--:|
    | 1 | -8 | 1|
    | 1 | 1 | 1 |
    ``` C++
    - fragment shader -
    ...
    float offsetX = 1.0f / float(textureSize(screenTexture,0).x);
    float offsetY = 1.0f / float(textureSize(screenTexture,0).y);
    void main(){
        vec2 offsets[9] = vec2[](
            vec2(-offsetX,offsetY), // top-left
            vec2(0.0f,offsetY),     // top-center
            vec2(offsetX,offsetY),  // top-right
            vec2(-offsetX,0.0f),    // center-left
            vec2(0.0f,0.0f),        // center-center
            vec2(offsetX,0.0f),     // center-right
            vec2(-offsetX,-offsetY),// bottom-left
            vec2(0.0f,-offsetY),    // bottom-center
            vec2(offsetX,-offsetY), // bottom-right
        );
        float kernel[9] = float[](
            1,1,1
            1,-9,1,
            1,1,1
        );
        
        vec3 sampleTex[9];
        for(int i=0;i<9;i++){
            sampleTex[i] = vec3(texture(screenTexture,vsTexCoord.st + offsets[i]));
        }
        vec3 color = vec3(0.0);
        for(int i = 0;i<9;i++){
            color += sampleTex[i] * kernel[i];
        }
        fragColor = vec4(color, 1.0);
    }
    ```
- 블러 필터링 구현
    - 이미지를 흐릿하게 만드는 필터
        
    | 1/16 | 2/16 | 1/16 |
    |:--:|:--:|:--:|
    | 2/16 | 4/16 | 2/16|
    | 1/16 | 2/16 | 1/16 |
- 샤픈 필터링 구현
    - 이미지를 선명하게 만드는 필터
        
    | -1 | -1 | -1 |
    |:--:|:--:|:--:|
    | -1 | 9 | -1 |
    | -1 | -1 | -1 |
- 보통 커널의 합이 1이 되도록 함