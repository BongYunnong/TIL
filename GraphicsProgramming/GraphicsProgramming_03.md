# 그래픽스 프로그래밍 #3 - 파이프라인 따라가기
## 버텍스 쉐이더에 데이터 전달하기
### 버텍스 패치(vertex fetch)
- 이 작업은 자동적으로 버텍스 쉐이더에 입력 데이터를 제공
- 고정함수(하지만 vertex shader에 우리가 원하는 정보를 함께 줄 수 있도록 하는 툴 존재)
- 자동으로 버텍스 쉐이더에 입력 데이터 제공

### 버텍스 속성
- 버텍스 쉐이더에 입력 데이터를 제공할 수 있는 방법
    - 버텍스 속성으로 데이터를 입력하는 함수
    - void glVertexAttrib4fv(GLuint index, const GLfloat * v);
        - 4fv 접미사 : 4개의 변수를 사용하는 float형 vector array
        - vertex array 오브젝트를 bind시키면 vertex fetch가 바인딩된 vertex를 찾아 vertex shader에 연결해서 호출
        - GLuint index : 버텍스에서 속성을 참조하기 위한 인덱스
        - const GLfloat *v : 속성에 넣을 새로운 데이터를 가리키는 포인터    
    ``` C++
    virtual void render(double currentTime){
        ...
        glUseProgram(rendering_program);
        GLfloat attrib[] ={(float)sin(currentTime) * 0.5f,
                            (float)cos(currenTime) * 0.5f,
                            0.0f,0.0f};
        // 입력 속성 0의 값을 갱신한다.
        glVertexAttrib4fv(0, attrib);
        glDrawArrays(GL_TRIANGLES,0,3);
    }
    ```
    - 값 4개를 가진 'attrib'라는 array를 index 0의 vertex에 갱신
        - vertex가 해당 값을 가지게 된다.

    - vertex shader
        ``` C++
        #version 430 core
        // vertex shader에 입력 데이터를 제공할 수 있는 방법
        layout(location =0) in vec4 offset;
        void main(void){
            const vec4 vertices[3] = vec4[3](vec4(0.25,-0.25,0.5,1.0),
                                            vec4(-0.25,0.25,0.5,1.0),
                                            vec4(0.25,0.25,0.5,1.0));
            gl_Position = vertices[gl_VertexID] + offset;
        }
        ```
        - offset만큼 이동시키는데, vertex에서 값을 받을 때 glVertexAttrib4fv에서의 값을 받음
        - attrib의 값에 currentTime을 사용했기에 원을 그리며 삼각형이 움직임
    - 아! glVertexAttrib4fv를 layout location의 0인덱스로 가져왔구나

## 스테이지 간 데이터 전달
### in, out 지시어
- GLSL에서 쉐이더로 데이터를 가져오거나 내보내는 작업을 위함
    - 파이프라인에서 전역 변수를 선언하고 사용하는 방식
        - C++와는 사용 방법이 다름
    - in 키워드 : 이전 스테이지 계산한 값을 현재 스테이지에서 받아오는 방법
    - out 키워드 : 현재 스테이지에서 계산한 값을 다음 스테이지로 전달
    - vertex fetch ->(in vec4 A) vertex shader (out vec4 B)-> (in vec4 B) Fragment shader
        - 같은 이름의 변수를 in, out을 통해 연결
- 삼각형 색상을 vertex shader에서 하드코딩하지 말고 파이프라인에서 입력해보자!
    - 하드코딩
    ``` C++
    - vertex shader -
    #version 430 core
    out vec4 color;
    void main(void){
        color = vec4(0.0,0.8,1.0,1.0);
    }
    ``` 
    - 파이프라인에서 입력
    ``` C++
    - vertex shader -
    #version 430 core
    layout(location=0) in vec4 offset;
    layout(location=1) in vec4 color;
    out vec4 vs_color;
    void main(void){
        const vec4 vertices[3] = vec4[3](vec4(0.25,-0.25,0.5,1.0),
                                        vec4(-0.25,0.25,0.5,1.0),
                                        vec4(0.25,0.25,0.5,1.0));
        gl_Position = vertices[gl_VertexID] + offset;
        vs_color = color;
    }
    ```
    ``` C++
    - fragment shader -
    #version 430 core
    in vec4 vs_color;
    out vec4 color;
    void main(void){
        color = vs_color;
    }
    ```
    ``` C++
    - pipeline -
    // 입력 속성 0의 값을 갱신 -> 삼각형 offset
    glVertexAttrib4fv(0, attrib);
    GLfloat color[] ={0.0f,0.0f,1.0f,0.0f};
    // 입력 속성 1의 값을 갱신 -> 삼각형 color
    glVertexAttrib4fv(1, color);
    // 삼각형 그리기
    glDrawArrays(GL_TRIANGLES,0,3);
    ```
### 인터페이스 블록
- 여러 변수를 하나의 인터페이스 블록으로 그룹화
    - C언어의 구조체와 유사 : struct 대신 in, out 사용
        ``` C++
        - vertex shader - 
        layout (location = 1) in vec4 color;
        out VS_OUT{         // 블록 이름
            vec4 color;     
        }vs_out;            // 변수 이름
        void main(void){
            ...
            vs_out.color = color;
        }
        ```
        ``` C++
        - fragment shader -
        in VS_OUT{          // 블록 이름
            vec4 color;
        } fs_in;            // 변수 이름
        out vec4 color;
        void main(void){
            color = fs_in.color;
        }
        ```
        - vertex shader에서는 vs_out이라 정해놓고 fragment shader에서는 fs_in으로 이름 정함
            - -> 인터페이스 블록은 변수 이름이 같은 것이 아니라 블록 이름이 같아야 한다.

### Tessellation
- 큰 폴리곤을 더 작은 폴리곤으로 나누는 것
    - 패치(patch- 고차 primitive)를 더 작고, 단순한 여러 개의 렌더링 가능한 primitive(ex. 삼각형)으로 분할하는 작업
- 왜 굳이 OpenGL에서?
    - 최적화를 위해 lowpoly를 만든 후에 subdivision하기 위함
- Tessellation Control Shader -> Tessellation(고정) -> Tessellation Evaluation Shader

- Tessellation Control Shader(TCS)
    - 버텍스 쉐이더로부터 입력받은 후 두가지 일 수행
        1. Tessellation 레벨 결정(분할 정보)
        2. Tessellation Evaluation Shader에 보낼 데이터 생성
    - 각 Patch는 여러 제어점(control point)로 이루어짐
        - primitive가 아니라 patch로 그려야한다.
        - patch당 제어점 개수는 변경 가능(기본 값 : 3)
            - triangle의 vertex == patch의 제어점
        - void glPatchParameteri(GLenum pname, GLint value);
            - GLenum pname : GL_PATCH_VERTICES
            - GLint value : 생성할 제어점 개수
    - tessellation이 활성화되면,
        - 버텍스 쉐이더는 제어점 당 한 번씩 따로따로 수행
        - TCS는 제어점들의 그룹에 대해 배치로 수행
            - 배치의 크기는 patch당 vertex의 개수와 동일
        - TCS의 입력 제어점의 개수와 출력 제어점의 개수는 다를 수 있다.
            - layout(vertices = N) out;
            - 보통은 3을 넣겠지만 N을 4나 5로 늘릴수도 있음
    ``` C++
    - vertex shader -
    #version 430 core
    layout(vertices = 3) out;
    void main(void){
        if(gl_InvocationID == 0){
            gl_TessLevelInner[0] = 5.0;
            gl_TessLevelOuter[0] = 5.0;
            gl_TessLevelOuter[1] = 5.0;
            gl_TessLevelOuter[2] = 5.0;
        }
        gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    }
    ```
    - glInvocationID는 gl_VertexID와 비슷함
    - gl_TessLevelInner는 안쪽으로 분할
    - gl_TessLevelOuter는 바깥쪽 선분 분할

### Tessellation Engine
- 파이프라인의 고정 함수(Tessellation)
    - TCS에서 정한 Tessellation 레벨에 따라 새로운 primitive생성
    - Tessellation Evaluation Shader로 전달

### Tessellation Evaluation Shader(TES)
- 실제 vetex 좌표 계산
    - Tessellation Engine은 Primitive구성과 제어점으로부터 새로운 점의 상대적 위치(ex. 무게중심 좌표)만 계산
        - Why? 쪼개서 생성된 점들의 추가적 처리를 할 수 있도록.
        - How? 무게 중심 좌표

- 무게 중심 좌표 (barycentric Coordinates)
    - v1(2,4), v2(1,1), v3(5,1) : (v1+v2+v3)/3 = (5,2)

``` C++
#version 430 core
layout(triangles, equal_spacing, cw) in;
void main(void){
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
                    gl_TessCoord.y * gl_in[1].gl_Position +
                    gl_TessCoord.z * gl_in[2].gl_Position);
}
```
- layout의 triangles는 점 3개를 사용하겠다.
- equal_spacing은 같은 간격
- cw는 시계방향으로 진행
- gl_TessCoord가 위의 예시에서1 1/3을 뜻함

- Tesselation은 patch를 사용
    - 그리기 모드의 변경이 필요 (GL_TRIANGLES -> GL_PATCHES)
    ``` C++
    glDrawArrays(GL_PATCHES,0,3);
    ```
- 분할 결과를 보기 위해선 와이어 프레임 모드로! (GL_FILL->GL_LINE)
    ``` C++
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    ```

## Geometry Shader
- Tessellation이 완료된 Primitive(삼각형) 당 한 번 수행
    - Primitive를 구성하는 모든 vertex에 대해 접근 가능
    - 데이터 흐름의 양 명시적으로 증가, 감소 가능
        - Tessellation은 TCS에서 정하는 레벨을 통해 암묵적으로 처리
        - Geometry shader에서는 명시적으로 처리
    - primitive mode 변경 가능(삼각형 -> 점)
``` C++
#version 430 core
// 삼각형을 입력으로 받는다고 명시
layout(triangles) in;
// Geometry shader가 점을 출력하고, 최대 개수가 3개라고 명시
layout(points, max_vertices = 3) out;
void main(void){
    int i;
    for(i=0;i<gl_in.length();i++){
        gl_Position = gl_in[i].gl_Position;
        // 함수호출 하여 현재 gl_Position값을 출력
        EmitVertex();
    }
}
```
- TCS에서 넘겨받은 gl_in 배열
- 각 vertex에 대해서 EmitVertex();
- -> 코드를 실행하면 tessellation이 적용된 삼각형의 점들을 볼 수 있다.

## Vertex Post-Processing
### 클리핑
- 현재까지는 클립 공간의 3차원 vertex
    - 동차좌표계로 표현(x,y,z,w)
        - why? 수학 계산이 더 단순해짐(ex. 이동 연산을 matrix의 곱으로)
        - W 요소로 나누어 카테시안 3차원 좌표(일반적 3차원 공간)으로 변환
            - 즉, (x/w, y/w, z/w, 1)
            - 정규화된 디바이스 공간 좌표

- 정규화된 디바이스 좌표를 보고 그릴지 말지 결정
    - 좌표가 -1.0<=x<=1.0, -1.0<=y<=1.0, 0<=z<=1.0 범위일 때 렌더링
    ![image](https://user-images.githubusercontent.com/11372675/149065703-962710dc-c9ab-434e-a126-37411c7b6caa.png)
    - 이 클립공간 안에 있는 것만 그려줌
    - 노란색의 경우 점 하나만 들어와있기 때문에 추가적인 처리 필요
- 뷰포트 변환
    - 실제 그릴 윈도우 좌표계
    - 좌하단이 (0,0), 영역이 (w-1, h-1)
    - 단위는 픽셀
    - 정규화된 디바이스 좌표 -> 윈도우 좌표 변환
        - 스케일과 offset 적용
        - ex. -1.0<=x<=1.0 -> 0<=x<=w-1

- 컬링
    - 삼각형이 렌더링 카메라를 향해있는지 확인하여 그릴지 여부 판단
        - 정면 방향 : 카메라를 바라봄
        - 후면 방향 : 카메라를 등짐
        - 보통 정면 방향만 렌더링
    - 삼각형 방향 구하는 방법
        - 두 변을 벡터로 외적 -> normal값 반환
            - ! a,b 벡터가 있다면 a X b와 b X a가 값이 다름
                - OpenGL은 기본적으로 반시계방향
            ![image](https://user-images.githubusercontent.com/11372675/149066010-cf844ab7-5338-45bc-a399-beb3f285b556.png)
    - OpenGL 관련 함수
        - void glFrontFace(GLenum mode)
            - 시계방향, 반시계방향
            - GL_CW, GL_CCW
        - void glEnable(GLenum cap)
            - 기본적으로는 culling 안 하지만 이것을 통해 cull 가능
            - GL_CULL_FACE
        - void glCULLFACE(GLenum mode)
            - culling 할 면을 정함
            - GL_FRONT, GL_BACK, GL_FRONT_AND_BACK

- Rasterization
    - fragment(픽셀)로 변환하는 과정
        - 어떤 fragment들이 점, 선, 삼각형 primitive에 의해 채워지는지 결정
    - 스크린 좌표에서 점 3개 찍고, bounding box를 만든다.
        ![image](https://user-images.githubusercontent.com/11372675/149066257-ddf2385e-78ef-43cd-b07e-72fc68cfa546.png)
        - bounding box안에서 fragment가 삼각형에 의해 가려지는지, 채워지는지 확인

## Fragement Shader
### Fragment Shader
- Fragment의 색상 결정
    - 작업량 폭발적으로 증가(삼각형 하나가 수많은 fragment 생성)
    - 실제로 라이팅 계산, 재질 적용, 깊이 결정 등 복잡한 작업 수행
- gl_FragCoor : 윈도우 상에서의 fragment 위치 정보 가짐
    - 가장 왼쪽 하단 좌표가(0.5,0.5) : fragment shader가 0.5,0.5만큼 밀어버림
    - 마지막 픽셀은 (w-1+0.5, h-1+0.5)
        - 픽셀의 중앙을 나타내기 위함
    ``` C++
    #version 430 core
    out vec4 color;
    void main(void){
        color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,
                    cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,
                    sin(gl_FragCoord.x * 0.25) * cos(gl_FragCoord.y * 0.25),
                    1.0);
    }
    ```

### 입력 값의 보간
- vertex shader에서 서로 다른 값은 fragment shader에 연결하면?
    - 색을 보간하여(섞어서 넘겨줌)
``` C++
- vertex shader -
#version 430 core
out vec4 vs_color;
void main(void){
    const vec4 vertices[3]=vec4[3](vec4(0.25,-0.25,0.5,1.0),
                                vec4(-0.25,0.25,0.5,1.0),
                                vec4(0.25,0.25,0.5,1.0));
    gl_Position = vertices[gl_VertexID] + offset;
    const vec4 colors[3] = vec4[3](vec4(1.0, 0.0, 0.0, 1.0),
                                vec4(0.0,1.0,0.0,1.0),
                                vec4(0.0,0.0,1.0,1.0));
    vs_color = colors[gl_VertexID];
}
```
``` C++
#version 430 core
// 버텍스 쉐이더 out과 연결된 입력 변수
in vec4 vs_color;
out vec4 color;
void main(void){
    color = vs_color;
}
```
![image](https://user-images.githubusercontent.com/11372675/149066991-ea4c6a04-0544-4290-8cae-6f935de45bec.png)