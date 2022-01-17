# 그래픽스 프로그래밍 #13 - Misc
## Misc
- sb6프레임워크 : OpenGL(GPU렌더링 작업을 지시하기 위한 API)

- Keyboard Input
    - virtual void onKey(int key, int action) 오버라이딩
    ``` C++
    virtual void oney(int key, int action){
        if(action==GLFW_PRESS){
            switch(key){
                case ' ':
                    pause = !pause;
                    break;
                case '1':
                    drawModel = !drawModel;
                    break;
                default:
                    break;
            };
        }
    }
    ```
- Mouse Input - 클릭
    - virtual void onMouseButton(int button, int action) 오버라이딩
    ``` C++
    virtual void onMouseButton(int button, int action){
        // LEFT - RIGHT - MIDDLE
        // PRESS - RELEASE
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
            mouseDown = true;
            int x, y;
            getMousePosition(x,y);
            mousePosition = vmath::vec2(float(x), float(y));
        }else{
            mouseDown = false;
        }
    }
    ```
- Mouse Input - 이동
    - virtual void onMouseMove(int x, int y )오버라이딩
    ``` C++
    virtual void onMouseMove(int x, int y){
        if(mouseDown){
            objYangle += float(x-mousePosition[0])/2.f;
            mousePosition = vmath::vec2(float(x),float(y));
        }
    }
    ```
- Mouse Input - 휠
    - virtual void onMouseWheel(int pos) 오버라이딩
    ``` C++
    #define MAX_FOV 120.f
    #define MIN_FOV 10.f
    virtual void onMouseWheel(int pos){
        int deltaPos = pos-wheelPos;
        if(deltaPos > 0){
            fov = vmath::min(MAX_FOV, fov + 1.0f);
        }else{
            fov = vmath::max(MIN_FOV, fov - 1.0f);
        }
        wheelPos = pos;
    }
    ```
- Window Resizing
    - virtual void onResize(int w, int h) 오버라이딩
        - 윈도우 크기가 변겨될 때 호출되는 함수
    ``` C++
    virtual void onResize(int w, int h){
        sb6::application::onResize(w,h);
        if(glViewport != NULL){
            glViewport(0,0,info.windowWidth,info.windowHeight);
        }
    }
    ```