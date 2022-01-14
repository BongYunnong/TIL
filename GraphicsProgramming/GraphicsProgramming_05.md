# 그래픽스 프로그래밍 #5 - 데이터
## 쉐이더 프로그램에게 데이터를 전달하는 방법
- OpenGL이 GPU에서 그리기 위한 데이터(점 위치, 컬러, 이동 벡터)를 어떻게 입력하였는가?
    1. 쉐이더 소스에 하드코딩
        ``` C++
        - vertex shader -
        #version 430 core
        layout (location=0) in vec4 offset;
        out VS_OUT{
            vec4 color;
        } vs_out;
        void main(void){
            const vec4 vertices[3] = vec4[3](vec4(0.25,-0.25,0.5,1.0),
                                            vec4(-0.25,0.25,0.5,1.0),
                                            vec4(0.25,0.25,0.5,1.0));
            gl_Position = vertices[gl_VertexID] + offset;
            const vec4 colors[3] = vec4[3](vec4(1.0,0.0,0.0,1.0),
                                            vec4(0.0,1.0,0.0,1.0),
                                            vec4(0.0,0.0,1.0,1.0));
            vs_out.color = colors[gl_VertexID];
        }
        ```
        - 쉐이더 소스를 수정해야 하기 때문에 데이터 생성 및 수정이 어렵다
        - 불필요한 GPU 메모리 할당이 발생하여 비효율적이다
            - 점 하나하나마다 gl_VertexID, vertices, colors를 생성해서 비효율적
    2. vertex attributes 활용
        ```C++
        - vertex shader(GPU) - 
        #version 430 core
        layout(location=0) in vec4 offset;
        out VS_OUT{
            vec4 color;
        }vs_out;
        void main(void){...}
        ```
        ```C++
        - applicaiton(CPU) -
        virtual void render(double currentTime){
            ...
            GLfloat attrib[] = {(float)sin(currentTime)*0.5f, (float)cos(currentTime)*0.5f, 0.0f,0.0f};
            glVertexAttrib4fv(0,attrib); // 입력 속성 0의 값을 갱신한다.
        }
        ```
        - CPU 데이터를 GPU메모리상에 저장하고 쉐이더에서 사용 가능
        - 데이터 작성이 쉽고, GPU 메모리 효율성 증대
        - CPU에서 GLfloat attrib[] 를 생성하고, GPU에서 그것을 참조 -> 효율성 UP
- 우리가 원하는 것
    - Vertex Position 입력
        - vertex position 입력을 위해 먼저 cpu에서 float 배열 생성
            ``` C++
            GLfloat vertices={
                0.25f,-0.25f,0.5f,  // 1번 버텍스
                -0.25f,0.25f,0.5f,  // 2번 버텍스
                0.25f,0.25f,0.5f    // 3번 버텍스
            };
            ```
            - 이렇게 임의의 개수인 데이터를 한꺼번에 GPU 메모리로 저장하기 위해서는 'glVertexAttrib4fv()'와 같이 데이터 사이즈가 정해진 함수는 못 쓴다.
            - 해결방법?
                1. 데이터 복사를 위해 필요한 GPU 메모리를 생성
                2. 어떻게 데이터를 버텍스 쉐이더로 나눠서 전달하는지 알려줘야함
        - Vertex Buffer Objects(VBO)
            - VBO를 통해 GPU 메모리를 관리(우리는 쉐이더나 프로그램처럼 GLuint로 객체 고유 ID를 받음)
            - 생성 > 바인드 > 데이터 복사 순서로 이루어짐
            ``` C++
            // VBO를 생성하여 vertices값을 복사
            GLuint VBO;
            glGenBuffers(1, &VBO);
            glBindBUffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            ```
            - glGenBuffers에서 1은 버퍼의 개수(vertices 배열 하나만 만들기에 1임)
            - GL_ARRAY_BUFFER : 타겟하는 Buffer Object타입 설정
            - sizeof(vertices) : 데이터 사이즈(byte단위)
            - vertices : 넘길 데이터 배열
            - GL_STATIC_DRAW : 버퍼 사용 목적
                - GPU가 효율적으로 버퍼 메모리 관리를 할 수 있도록 명시해주는 것

                | 버퍼 사용 목적 | 설명  |
                |:---:|:---:|
                | GL_STREAM_DRAW | 버퍼의 데이터가 한 번 설정되며, 드로잉을 위해 가끔 사용될 것이다. |
                | GL_STATIC_DRAW | 버퍼의 데이터가 한 번 설정되며, 드로잉을 위해 자주 사용될 것이다. |
                | GL_DYNAMIC_DRAW | 버퍼의 데이터가 자주 변경되며, 드로잉을 위해 자주 사용될 것이다. | 
            - 연결해주는 방법은 Vertex Attribute 처럼 layout으로 받아올 수 있음
                ``` C++
                #version 430 core
                layout (location =0) in vec3 pos; // x,y,z 접근을 위해 vec3
                void main(void){
                    // w를 넣어서 동차 좌표계 변환
                    gl_Position = vec4(pos.x,pos.y,pos.z,1.0);
                }
                ```
            - 하지만 우리는 크기가 9인 vertices 배열을 만들었는데, 어떻게 버텍스 별로 자기 위치 데이터만 어떻게 가져올까?
                - VBO에 Vertex Attributes 연결하기
                - VBO를 어떻게 나누어서 각 Vertex Attribute로 전달하는지 설정해줘야함
                ``` C++
                // layout location index, 속성사이즈(vec3), 데이터 타입, 값 정규화 수행 여부(정수형일 때 주로 사용), 속성 간 몇 byte(stride) 이동할지, 데이터 시작 위치 오프셋
                glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
                glEnableVertexAttribArray(0);
                ```
                ``` C++
                // 삼각형 세 점의 위치 정의
                GLfloat vertices[] = {0.25f,-0.25f,0.5f,
                                    -0.25f,0.25f,0.5f,
                                    0.25f,0.25f,0.5f};
                // VBO를 생성하여 vertices 값들을 복사
                GLuint VBO;
                glGenBuffers(1, &VBO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                // VBO를 나누어서 각 버텍스 속성으로 연결
                glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float),(void*)0);
                glEnableVertexAttribArray(0);
                // 렌더링을 위해 생성한 프로그램 객체를 사용하도록 한다.
                glUseProgram(rendering_program);
                // 삼각형을 하나 그린다.
                glDrawArrays(GL_TRIANGLES, 0, 3);
                ```
                - 그려야 할 3D 오브젝트가 많아진다면 매번 렌더 함수에서 이렇게 설정하는 것은 번거로움...
                    - 위의 설정을 저장하는 것이 Vertex Array Object(VAO)
- Vertex Array Object(VAO)
    - VAO가 바인드 되어 있다면 지금까지 했던 VBO, Attributes 세팅이 다 저장된다.
    ``` C++
    // 어플리케이션 초기화
    virtual void startup(){
        rendering_program = compile_shaders();
        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);

        // 삼각형 세 점의 위치 정의
        GLfloat vertices[] = {0.25f,-0.25f,0.5f,
                            -0.25f,0.25f,0.5f,
                            0.25f,0.25f,0.5f};
        // VBO를 생성하여 vertices 값들을 복사
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // VBO를 나누어서 각 버텍스 속성으로 연결
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);

        // VBO 및 베텍스 속성 다 한 후에 VBO와 VAO unbind
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    }
    ...
    // 렌더링 virtual 함수 작성해서 오버라이딩
    virtual void render(double currentTime){
        const GLfloat black[] = {0.0f,0.0f,0.0f,1.0f};
        glClearBufferfv(GL_COLOR,0,black);
        // 렌더링위해 생성한 프로그램 객체를 사용하도록 한다.
        glUseProgram(rendering_program);
        // 미리 설정한 VAO를 그리기 위해 bind한다.
        glBindVertexArray(VAO);
        // 삼각형을 하나 그린다.
        glDrawArrays(GL_TRIANGLES,0,3);
    }
    ```
    - 오브젝트가 여러개라면 VAO와 VBO의 개수를 늘리자.
        ``` C++
        GLuint VAOs[2], VBOs[2];
        glGenVetexArrays(2, VAOs);
        glGenBuffers(2,VBOs);
        ```
- 컬러도 추가해보자.
    - 하나의 VBO로 vertex attribute 두 개(위치 + 컬러) 연결시키기
        ``` C++
        // 삼각형 세점 위치와 컬러를 정의한다.
        GLfloat vertices[] ={
            0.25f,-0.25f,0.5f,1.0f,0.0f,0.0f,   // 버텍스 1
            -0.25f,0.25f,0.5f,0.0f,1.0f,0.0f,   // 버텍스 2
            0.25f,0.25f,0.5f,0.0f,0.0f,1.0f,   // 버텍스 3
        };
        ...
        // VBO를 나누어서 각 버텍스 속성으로 연결
        // 위치 속성(location = 0)
        glVertexAttribPoitner(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        // 컬러 속성(location = 1)
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        ```
        - color의 경우는 3개를 사용하고, 건너뛰어야 하는 것이 6*(sizeof(float)), offset이 (void*)(3*sizeof(float))로 설정 필요
        ``` C++
        - vertex shader -
        #version 430 core
        layout(location = 0) in vec3 pos;
        layout(location = 1) in vec3 color;
        out vec3 vsColor;
        void main(void){
            gl_Position = vec4(pos.x,pos.y,pos.z,1.0);
            vsColor= color;
        }
        ```
        ``` C++
        - fragment shader -
        #version 430 core
        in vec3 vsColor;
        out vec4 fragColor;
        void main(void){
            // vec4(vsColor.r, vsColor.g, vsColor.b, 1.0);
            fragColor = vec4(vsColor, 1.0);
        }
        ```
        - vsColor로 vertex에서 fragment로 전달
        - fragColor로 그리는 색상 내보내기
![image](https://user-images.githubusercontent.com/11372675/149449729-c703bd90-1fb5-4efb-a29e-11ae1bd65dbc.png)
- 회전도 시켜보자
    - 모든 버텍스에 동일한 회전 행렬의 곱을 한다. -> Uniform 변수 활용
    - Uniform
        - GPU 쉐이더들에게 데이터를 전달하는 또 다른 방법
        - Uniform 변수는 전역 변수다!
            - 프로그램 내 모든 쉐이더 스테이지에서 접근이 가능!
            - GLSL의 다양한 타입을 지원(float,int,vec3,vec4,mat4,...)
        ``` C++
        - vertex shader-
        #version 430 core
        layout(location=0) in vec3 pos;
        layout(location=1) in vec3 color;

        uniform mat4 rotMat;
        out vec3 vsColor;
        void main(void){
            gl_Position = rotMat* vec4(pos.x,pos.y,pos.z,1.0);
            vsColor = color;
        }
        ```
        ``` C++
        - application -
        // rotMatLocation : uniform 로케이션을 저장
        // rendering_program : uniform을 정의한 쉐이더 프로그램 객체 ID
        // "rotMat" : uniform 변수 명
        GLint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
        ```
        ``` C++
        - render()함수 -
        // 렌더링위해 생성한 프로그램 객체 사용
        glUseProgram(rendering_program);
        // z축에 대한 회전 행렬
        float angle = currentTime*50;
        vmath::mat4 rm = vmath::rotate(angle,0.0f,0.0f,1.0f);
        // "rotMat" uniform에 대한 위치를 가져옴
        GLint rotMatLcation = glGetUniformLocation(rendering_program, "rotMat");

        // "rotMat" uniform으로 전달한다.
        // rotMatLocation : 데이터를 넘길 uniform 로케이션 지정
        // 1 : 넘기는 매트릭스 개수
        // GL_FALSE : Transpose 수행 여부
        // rm : vmath를 통해 만든 mat4 변수를 지정
        glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE,rm);
        // 미리 설정한 VAO를 그리기 위해 bind
        glBindVertexArray(VAO)'
        ```