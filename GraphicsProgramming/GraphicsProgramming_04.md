# 그래픽스 프로그래밍 #4 - 3D 그래픽스를 위한 수학
## 3D 그래픽스를 위한 수학
### 벡터
- 객체의 버텍스 이동, 좌표 변환은 벡터 or 행렬의 연산을 이용함
    - GPU에 최적화 되어있기 때문

- 벡터 : 방향과 크기를 가진 값
- 스칼라 : 단일 숫자 값

- 단위 벡터 : 크기가 1인 벡터
    - 단위 벡터를 사용하면 공식이 더 단순해짐

- 벡터 합 : 대응되는 요소끼리 더하기
- 벡터 곱 : 내적, 외적
    - 내적(dot product)
        -  $\overrightarrow{v}$ = $\overrightarrow{k}$ = ||$\overrightarrow{v}$|| X ||$\overrightarrow{k}$|| X Cos  $\theta$
        - 두 벡터가 단위 벡터일 경우, 코사인 값과 동일
            - 수직일 경우 0
            - 평행일 경우 -1 or 1
        - 내적 계산
            - 두 벡터의 대응되는 요소를 곱하고, 결과값을 모두 더하기
            $\begin{pmatrix}
            0.6 \\
            -0.8 \\
            0 \\
            \end{pmatrix}
            \cdot 
            \begin{pmatrix}
            0 \\
            1 \\
            0 \\
            \end{pmatrix}
            = (0.6 * 0) + (-0.8 * 1) + (0 + 0) = -0.8
            $
    - 외적(cross product)
        - $\overrightarrow{v}$ X $\overrightarrow{k}$
        - 두 벡터에 대해 모두 수직인 벡터 계산
        - 3차원에서만 정의됨
        - 곱하는 순서 중요!

![그래픽스프로그래밍4주차_2](https://user-images.githubusercontent.com/11372675/149440153-1362c4b4-d7db-43ed-89d9-c99508f4a06b.png)

![그래픽스프로그래밍4주차_2_02](https://user-images.githubusercontent.com/11372675/149440163-2dfd9b06-3ffa-4a4a-a8fb-f97b28d50d23.png)

![image](https://user-images.githubusercontent.com/11372675/149440235-085fe1c7-249a-4651-b8dc-96c3e4ef59be.png)

![image](https://user-images.githubusercontent.com/11372675/149440264-02436a9c-5187-4796-81a6-6c1a1e5d93ac.png)

![image](https://user-images.githubusercontent.com/11372675/149440284-7cae3758-a20b-46f3-829f-c8ca8bc2fce6.png)

## 좌표변환
- OpenGL은 NDC(정규 디바이스 좌표계)에서 특정 영역만 그리도록 되어있음
    - -1과 1 사이에서 장면을 구성하는 것은 우리에게 익숙하지 않음
    - -> 우리에게 편한 좌표계에서 작업하고, 렌더링할 때만 NDC로 변환하자!
- 필요한 좌표계
    - 모델 공간(주로 원점은 모델 중심)
        - 로컬 원점으로부터 상대적인 위치
        - Local Space, Local Coordinate System, Model Space, Object Space
    - 월드 공간
        - 월드 원점으로부터 상대적인 위치
        - World Space, World Coordinate System
    - 뷰 공간(원점은 카메라)
        - 관측점으로부터 상대적인 위치
        - View Space, Eye Space, Camera Space, Camera Coordinate System
    - 렌더링
        - Clip Space -> Noramlized Device Coordinates -> Screen Coordinates
- 어떤 변환들이 일어날까?
    - 모델 공간 -> 월드 공간 : 모델-월드 변환
        - 스케일링, 회전, 이동
    - 월드 공간 -> 뷰 공간 : 월드-뷰 변환
        - 회전, 이동
    - 뷰 공간 -> 렌더링 : 프로젝션 변환
        - 프로젝션(투영)
    - 렌더링 -> : 뷰포트 변환
- 오른손 좌표계
    - OpenGL에서 사용하는 기본 좌표계
    - 엄지 오른(x), 검지 위(y), 중지 안쪽(z) (수학 공부할 때 3차원)
    - 왼손 좌표계는 엄지 오른(x), 검지 위(y), 중지 앞쪽(z)
- 월드-뷰 변환
    - 렌더링 카메라의 관측점(위치)을 원점으로, 바라보는 방향을 음의 Z축 방향으로 생각해서 버텍스들의 상대적인 위치를 계산
        - 회전과 이동 변환 행렬의 조합으로 표현 가능
    - 렌더링 카메라 정의
        - 위치(관측점), 타겟(바라보는 점), 업 방향
        - 카메라 위치에서 서로 수직인 3축을 찾아야 한다.
    - 렌더링 카메라 3축 구하기
        - 위치(관측점), 타겟(바라보는 점), 업 방향으로부터 계산 가능
        1. position : P = 위치
        2. direction : D = (P-타겟) / (||P-타겟||)
        3. Right : R = up 방향 X D
        4. Up : U = D X R
        - 여기에서 up 방향과 U는 다름. up 방향은 대충 구한 위쪽 벡터임
    - 월드-뷰 변환 매트릭스(view matrix, look at matrix)
        - 위치 벡터와 3축으로 부터 구성

        $ LookAt = 
        \begin{bmatrix}
         R_x & R_y & R_z & 0 \\
         U_x & U_y & U_z & 0 \\
         D_x & D_y & D_z & 0 \\
         0 & 0 & 0 & 1 \\
        \end{bmatrix}
        *
        \begin{bmatrix}
         1 & 0 & 0 & -P_x \\
         0 & 1 & 0 & -P_y \\
         0 & 0 & 1 & -P_z \\
         0 & 0 & 0 & 0 \\
        \end{bmatrix}
        $
        $ V_view_space = LookAt  내적
        \begin{bmatrix}
         V_x \\
         V_y \\
         V_z \\
         1 \\
        \end{bmatrix}
        $
    - vmath.h
        - 정의 : mat4 vmath::lookat(vec3 eye, vec3 target, vec3 up)
        ``` C++
        vmath::vec3 eye(5.0,2.0,3.0);
        vmath::vec3 center(0.0,0.0,0.0);
        vmath::vec3 up(0.0,1.0,0.0);

        mat4 perspM = vmath::lookat(eye,center,up);
        ```
- 프로젝션 변환
    - 클립 공간에 매핑 될 뷰 볼륨을 정의
        - 설정된 뷰 볼륨의 x,y,z 값을 -1부터 1이 되도록 변환
        1. 정사영(Orthographic Projection):
            - 평행선을 따라 매핑(얼마나 멀리 있는지 상관 안 함)
        2. 원근 투영(Perspective Projection):
            - 소실점을 따라 매핑(멀리 있는 객체는 더 작게 그리는 원근 효과 적용)
            - 더 사실적임
- 정사영
    - [Left,Right,Top,Bottom,Near Plane, Far Plane] 6개의 좌표 값으로 정의

    $ 정사영 행렬 공식 : 
    \begin{bmatrix}
     2/(right-left) & 0 & 0 & (left+right)/(left-right) \\
     0 & 2/(top-bottom) & 0 & (bottom+top)/(bottom-top) \\
     0 & 0 & 2/(near-far) & (far+near)/(far-near) \\
     0 & 0 & 0 & 1 \\
    \end{bmatrix}
    $
    - vmath.h
        - 정의 : mat4 vmath::orth(float _left, float _right, float _bottom, float _top, float _near, float -far)
        ``` C++
        mat4 orthM = vmath::orth(-50,50,-20,20,-1,-100);
        ```
- 원근투영
    - [Left,Right,Top,Bottom,Near Plane,Far Plane] 6개 좌표 값으로 정의
    
    $ 원근투영 행렬 공식 : 
    \begin{bmatrix}
     2*near/(right-left) & 0 & (right+left)/(right-left) & 0\\
     0 & 2*near/(top-bottom)  & (top+bottom)/(top-bottom) & 0\\
     0 & 0 & (near+far))/(near-far) & 2*far*near/(near-far) \\
     0 & 0 & -1 & 0 \\
    \end{bmatrix}
    $
    - vmath.h
        - 정의 : mat4 vmath::frustum(float _left, float _right, float _bottom, float _top, float _near, float _far)
        ``` C++
        mat4 perspM = vmath::frustum(-20,20,-12,12,-10,-100);
        ```
    - [Field of view, Aspect Ratio, Near Plane, Far Plane] 4개로 정의하기도 함
        - Aspect Ratio : Near Plane 폭을 높이로 나눈 값(디스플레이나 윈도우 종횡비)
        - Field of View : 세로 방향 시야 각도로 주로 정의
    - vmath.h
        - 정의 : mat4 vmath::perspective(float _fovy, float _aspect, float _near, float _far)
        ``` C++
        mat4 perspM = vmath::perspective(50,1.75,-10,-100);
        ```
- 모든 좌표 변환 적용하기
$ V_clip = M_projection * M_view(lookat) * M_model-world *
        \begin{bmatrix}
         V_x \\
         V_y \\
         V_z \\
         1 \\
        \end{bmatrix}
        $
    - v_clip : 버텍스 쉐이더의 gl_Positoin 값
    - M_projection,viwe(lookat),model-world : 미리 곱해서 하나의 4X4 행렬만 버텍스 쉐이더로 전달해서 적용 가능
