# 그래픽스 프로그래밍 #2 - 첫 번째 OpenGL 프로그램
## 간단한 어플리케이션 작성
### 환경설정
- vc++
    1. build solution
    2. 볼드체로 되어있는 프로젝트 julia
    3. ctrl+f5 로 실행
    4. 프로젝트 우클릭하고 셋업 스타트 프로젝트 하면 볼드체 됨
    5. 원하는거 해보기
    - glsl 파일이 쉐이더

### sb6.h
- superbible6.h
    - 앞으로 사용할 OpenGL 애플리케이션 프레임워크 제공
    - 윈도우 생성, OpenGL 컨텍스트, 키보드/마우스 입력 등 처리하기 위한 다양한 유틸리티 함수 포함
        - 플랫폼, 기기마다 다를텐데, 이것을 통합하는 유틸리티 함수를 포함한다는 장점
    - 간단한 수학 라이브러리 'vmath'포함(벡터,회전,투영 행렬 등등)
- sb6.h를 include하고, sb6::application(뼈대) 상속받아서 애플리케이션을 구현한다.

### \_myApp\_ 기본 프로젝트
- visual studio 2013 버전
``` C++
#include <sb6.h>
// sb6::application 상속받기
class my_application : public sb6::application{
public:
    // 렌더링 virtual 함수를 작성해서 오버라이딩 한다.
    virtual void render(double currentTime){
        static const GLfloat red[] = {1.0f,0.0f,0.0f,1.0f};
        glClearBufferfv(GL_COLOR, 0, red);
    }
};
// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application)
```
- DECLARE_MAIN(my_application)
    - 메인 엔트리 포인트 지정 : 애플리케이션 인스턴스에 해당할 클래스를 인자로 전달
    - sb6::application에서 클래스로 객체를 만들고 어플리케이션을 실행하게 됨
	- -> void main 대체

### sb6::application
- 구조
    1. run() 호출 : 메인 루프 정의
    2. startup() 호출 : 애플리케이션의 초기화 관련 정의
    3. 메인 루프 시작 : 메인 루프 시작
    4. render() 호출 : 이 함수를 오버라이드해서 렌더링 코드 작성
        - 메인 루프 안에서 반복적으로 호출

    - startup, render 함수는 virtual임 -> override해서 사용

### glClearBufferfv()
- 화면에 뿌려질 Framebuffer를 특정 값으로 지우기
``` C++
glClearBufferfv(GL_COLOR,0,red);
```
- 모든 OpenGL 함수는 gl로 시작한다.
- 첫 번째 인자인 FrameBuffer(GLenum buffer)를 세 번째 인자 값(GLfloat* value)으로 지운다.
    ``` C++
    // R, G, B, A
    const GLfloat red[] ={1.0f, 0.0f, 0.0f, 1.0f};
    ```
- fv 접미사는 인자 타입을 줄여서 쓴 것이다.
    - f : 부동소수점
    - v : 벡터(배열)
- GLint drawbuffer : 출력 버퍼가 여러 개일 때 지정하기 위힘(0 기반의 인덱스)

### render(double currentTime)
- vmath.h를 include해야 한다.
- currentTime : 애플리케이션이 시작한 이후의 경과 시간(초)
    - 애니메이션을 위한 값으로 활용 가능
    ``` C++
    const GLfloat red[] ={(float)sin(currentTime) * 0.5f + 0.5f,
                        (float)cos(currentTime) * 0.5f + 0.5f,
                        0.0f,1.0f};
    ```

## 쉐이더 사용하기
- 쉐이더 프로그램 : vertex Fetch -> vertex Shader -> Tessellation Control Shader -> Tessellation -> Tessellatoin Evaluation Shader -> Geometry Shader -> Rasterization -> Fragment Shader -> Framebuffer Operations

### OpenGL Shading Language(GLSL)
- C언어를 기반으로 GPU에서 동작
    - 컴파일러는 OpenGL에 내장
    - 쉐이더 소스 코드는 쉐이더 객체에 위치되어 컴파일
    - 여러 쉐이더 객체들이 하나의 '프로그램 객체'로 링크
    - 하나의 '프로그램 객체'는 여러 쉐이더 스테이지의 쉐이더들을 포함
        - vertex 쉐이더, tessellation 컨트롤 및 evaluation 쉐이더, geometry 쉐이더, fragment 쉐이더 ,compute 쉐이더

- vertex Shader
    - 목적 : vertex를 처리해서 다음 스테이지에서 사용할 위치를 지정
    ``` C++
    // GLSL 버전 및 (core인지, compatable인지) 프로파일 지정
    #version 430
    // 쉐이더 프로그램 main 함수 정의
    void main(void){
        // 버텍스의 출력 위치를 클립공간(clip space-버텍스 쉐이더의 공간)의 중앙에 지정
        gl_Position = vec4(0.0, 0.0, 0.5, 1.0); // x,y,z,w
    }
    ```
    - gl_Position처럼 gl_로 시작하는 변수는 OpenGL이 사용하는 내장 변수로, 다른 스테이지 쉐이더들과 연결된다.

- fragment Shader
    - 목적 : 그려질 이미지의 픽셀 값을 지정
    ``` C++
    #version 430 core
    // out 키워드를 사용하여 color를 출력 변수로 선언해서 다음 스테이지에서도 사용 가능
    out vec3 color;
    void main(void){
        // R, G, B, A 색상 지정
        color = vec4(0.0, 0.8, 1.0, 1.0);
    }
    ```

### 쉐이더 코드를 프로그램 객체로 링크하기
- 기본 순서
    1. 빈 쉐이더 객체를 생성한다.
    2. 쉐이더 소스 코드를 쉐이더 객체로 전달한다.
    3. 쉐이더 객체의 소스 코드를 컴파일한다.
    4. 프로그램 객체를 생성한다.
    5. 쉐이터 객체를 프로그램 객체에 Attach시킨다.
    6. 프로그램 객체에 Attach된 모든 쉐이더 객체를 링크한다.
    7. 쉐이더 객체를 삭제한다.
        - 프로그램 안에 쉐이더 정보를 다 가지고있기 때문에 삭제해도 무방
1. 쉐이더 객체 생성
    - GLuint glCreateShader(GLenum ShaderType)
        ```C++
        GLuint vertex_shader;
        vertex_shader = GLuint glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment_shader;
        fragment_shader = GLuint glCreateShader(GL_FRAGMENT_SHADER);
        ```
        - shader type : GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
2. 쉐이더 소스 코드를 쉐이더 객체로 전달
    - 쉐이더 소스 코드 저장 변수 : const GLchar* variableName[]
        ``` C++
        const GLchar* vertex_shader_source[]={
            "#version 430 core                          \n"
            "void main(void)                            \n"
            "   gl_Position = vec4(0.0,0.0,0.5,1.0);    \n"
            "}                                          \n"
        };
        or
        const GLchar* vertex_shader_source[]={
            "#version 430 core                          \n"
            "out vec4 color;                            \n"
            "void main(void)                            \n"
            "   color = vec4(0.0,0.8,1.0,1.0);          \n"
            "}                                          \n"
        };
        ```
    - void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLuint* length);
        ``` C++
        glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
        glShaderSource(fragment_shader,1,fragment_shader_source,NULL);
        ```
3. 쉐이더 객체의 소스 코드를 컴파일
    - void glCompileShader(GLuint shader);
        ``` C++
        glCompileShader(vertex_shader);
        glCompileShader(fragment_shader);
        ```

4. 프로그램 객체를 생성
    - GLuint glCreateProgram()
        ``` C++
        GLuint program;
        program = glCreateProgram();
        ```

5. 쉐이더 객체를 프로그램 객체에 Attach
    - void glAttachShader(GLuint program, GLuint shader);
        ``` C++
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        ```
    - 프로그램 안에 vertex_shader, fragment_shader가 존재하게 된다.

6. 프로그램 객체에 Attach된 모든 쉐이더 객체 링크
    - void glLinkProgram(GLuint program);
        ``` C++
        glLinkProgram(program);
        ```

7. 쉐이더 객체를 삭제
    - void glDeleteShader(GLuint shader);
        ``` C++
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        ```

### startup()
- sb6::application의 가상 함수
- 쉐이더 및 프로그램 재 컴파일을 안 하도록 startup에서 프로그램 객체를 저장
- startup은 어플리케이션이 시작할 때 한 번만 실행
``` C++
class my_application : public sb6::application{
public:
    // 최종적으로 만들어진 쉐이더를 반환
    GLuint compile_shaders(void){...}
    virtual void startup(){
        // 쉐이더 저장
        rendering_program = compile_shaders();
    }
    virtual void render(double currentTime){...}
private:
    // startup에서 생성한 뒤 저장하기 위해 선언
    GLuint rendering_program;
}
```

### Vertex Array Object(VAO)
- vertex fetch 스테이지를 나타내는 객체(OpenGL 파이프라인의 입력과 관련된 모든 상태를 유지)
    - 버텍스 쉐이더에 입력할 VAO 생성(한 물체당 하나의 VAO)
    - GLuint : VAO 객체 저장 변수
    - void glGenVertexArrays(GLsizei n, GLuint * arrays);
        - VAO 객체 생성
    - void glBindVertexArray(GLuint array)
        - Gene으로 생성된 VAO객체를 파이프라인에 바인딩
``` C++
class my_application : public sb6::application{
public:
    GLuint compile_shaders(void){...}
    virtual void startup(){
        rendering_program = compile_shaders();
        glGenVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
    }
    virtual void render(double currentTime){...}
private:
    GLuint rendering_program;
    GLuint vertex_array_object;
}
```

### shutdown()
- 어플리케이션이 종료될 때 호출되는 가상 함수
    - 정리 코드 작성
    - void glDeleteVertexArrays(GLsizei n, const GLuint * arrays);
        - VAO 객체 삭제
    - void glDeleteProgram(GLuint program);
        - 프로그램 객체 삭제
``` C++
class my_application: public sb6::application{
public:
    GLuint compile_shaders(void){...}
    virtual void startup(){...}
    virtual void shutdown(){
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
    }
    virtual void render(double currentTime){...}
private:
    GLuint rendering_program;
    GLuint vertex_array_object;
}
```

### render()
```C++
virtual void render(double currentTime){
    const GLfloat red[] ={(float)sin(currentTime) * 0.5f + 0.5f,
                        (float)cos(currentTime) * 0.5f + 0.5f,
                        0.0f, 1.0f};
    glClearBufferfv(GL_COLOR,0,red);

    // 렌더링을 위해 생성한 프로그램 객체를 사용하도록 한다.
    glUseProgram(rendering_program);

    // 점 하나 그리기
    glPointSize(40.0f);
    // 어떠한 primitive를 그릴 것인가, 어디서부터, 몇개를 그릴 것인가
    glDrawArrays(GL_POINTS, 0 , 1);
}
```

## 쉐이더로 삼각형 그리기
### GL_TRIANGLES
- glDrawArrays()는 다양한 프리미티브 타입을 지원한다.
    - 점, 선, 삼각형 : GL_POINTS, GL_LINES, GL_TRIANGLES, ...
        - ! 선이나 삼각형의 경우 둘 이상의 버텍스가 동일한 위치에 있으면 primitive 생성이 취소된다.
        ```C++
        // 점이 다 중앙에 있기에 아무것도 안 나타남
        glDrawArrays(GL_TRIANGLES,0,3);
        ```

## vertex 쉐이더 수정
- gl_VertexID
    - GLSL의 내장 변수
    - glDrawArrays()에 입력으로 들어간 첫 번째 인자값부터 시작해서 세번째 인자인 count만큼의 vertex까지 한 vertex에 대해 1씩 증가
    - 각 포인트마다 한번씩 실행하는데, gl_VertexID를 통해 다른 값에 접근 가능
``` C++
const GLchar* vertex_shader_source[]={            
    "#version 430 core                                              \n"
    "                                                               \n"
    "void main(void){                                               \n"
    "   const vec3 vertices[3] = vec4[3](vec4(0.25,-0.25,0.5,1.0),  \n"
    "                                    vec4(-0.25,0.25,0.5,1.0),  \n"
    "                                    vec4(0.25,0.25,0.5,1.0));  \n"
    "    // index로 접근해서 하나하나 position 정해줌                 \n"
    "    gl_Position = vertices[gl_VertexID];                       \n"
    "}                                                              \n"
};
```
- 위 코드를 실행하면 삼각형이 그려진다.
