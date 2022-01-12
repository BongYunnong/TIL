# 그래픽스 프로그래밍 # 01
## 그래픽스 프로그래밍
- 컴퓨터 그래픽스 : 데이터를 렌더링하여 이미지로 생성하는 것
- 컴퓨터 비전 : 이미지로부터 데이터를 만들어내는 것

- 모델링 -> 텍스처링 -> 리깅 -> 애니메이팅 -> 라이팅 -> 렌더링
    - 모델링 ~ 라이팅 : Data를 만들어내는 과정임

- 그래픽스 프로그래밍 : 컴퓨터 그래픽 제작 과정에서 필요한 소프트웨어를 구현
    - ex. 게임(실시간), 시뮬레이션, 미디어아트, 렌더링, XR 등

## OpenGL과 그래픽스 파이프라인
- 데이터(점 위치, 조명 위치, 카메라 위치...)를 '그래픽스 파이프라인(좌표변환, 투영, 레스터라이제이션, 그림자...)'을 통해서 이미지(픽셀 값)으로 변환

- 이미지 한 장(프레임)을 그리기 위해 굉장히 반복적인 연산 발생(단순)
    - but 대부분은 독립적인 연산 -> 파이프라인 분할과 병렬화 가능 -> GPU, 그래픽스 서브시스템

- CPU는 성능이 좋음
- GPU는 성능이 좋진 않지만 코어가 많음

- 그래픽스 API(문서)
    - GPU를 활용해 그래픽스 파이프라인을 가속화하기 위한 규격
    - 어플리케이션이 활용할 수 있는 GPU의 추상화 레이어 제공
    - 그래픽스 라이브러리 : API를 구현한 실체
    - ex.
        - lowlevel : OnelGL*, DirectX, OpenGL ES*, WebGL*, Vulkan*, Metal (*는 무료)
        - highlevel :  Unity, Unreal

- 왜 OpenGL인가?
    - 가장 많은 GPU와 플랫폼이 지원하는 그래픽스 API
    - 광범위하고, 로열티 없고, Cross-Language, Cross-Platform

- Modern OpenGL
    - The Programmable Shader Pipeline
        - 모든 어플리케이션은 Shader를 사용해야만 함
        - OpenGL 버전 3.x 이상
    - Shader Program
        - GPU에서 실행되는 작은 프로그램(개발자가 GPU 그래픽스 파이프라인 제어 가능)

- Modern OpenGL Pipeline
    - [Vertex Fetch] -> (Vertex Shader) -> (Tessellation Control Shader) -> [Tessellation] -> (Tessellation Evaluation Shader) -> (Geometry Shader) -> [Rasterization] -> (Fragment Shader) -> [Framebuffer Operations]
    - [] : 고정 기능
    - () : 프로그래밍 기능

## OpenGL의 진화
- 1994년에 release, 전부 fixed-function
- OpenGL2 programmable shaders, vertex-fragmentShading
- OpenGL3
- OpenGL3.1 fixed-function제거, 거의 모든 데이터가 GPU-resident(by buffer objects)
- OpenGL3.2 Geometry Shader
- Core는 현재 출시 기능들, COmpatible은 모든 기능
- OpenGL4.1 Tessellation 쉐이더

- OpenGL ES는 임베디드 시스템(경량화된 시스템 ex 안드로이드)
- WebGL 브라우저에서 실행
- 우리는 4.3을 사용

## 프리미티브, 파이프라인, 픽셀
- 생산라인 모델
    - 데이터 플로우는 한 방향
    - 버퍼 오브젝트(점 위치, 애니메이션 정보 등등), 텍스처같은 자료구조 활용해서 데이터 저장 및 전달
    - 파이프라인의 각 스테이지에서 다음 스테이지로 정보를 전달

- OpenGL 프로그래밍 간단 요약
    1. 쉐이더 프로그램 생성
    2. 버퍼 오브젝트와 텍스쳐에 데이터를 로드
    3. 각 쉥더 프로그램에 데이터를 연결
    4. "렌더!"

- 프리미티브
    - OpenGL 렌더링의 기본 단위
        - 세 가지 기본 타입 : 점, 선, 삼각형
            - (사각형, 오각형과 같은 복잡한 서피스는 삼각형으로 분할하여 처리)
        - 왜? 삼각형은 컨벡스(convex, 볼록)하기 때문에 그리기 쉬움
            - 반대로 사각형이 오목해진 것은 concave

- 파이프라인 프론트엔드
    - 버텍스를 처리해서 점, 선, 삼각형으로 구성하여 레스터라이저로 전달
    - vertex Fetch ~ Geometry Shader
    - 프리미티브 어셈블리(primitive assembly)라고도 함
    
- 파이프라인 백엔드
    - 레스터라이저가 점, 선, 삼각형을 대량의 픽셀로 변환하여 백엔드로 전달
    - Fragment Shader ~ Framebuffer Operation
    - 깊이 및 스텐실 테스트, 프래그먼트 쉐이딩, 블렌딩, 디스플레이 출력 담당

