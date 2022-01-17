# 그래픽스 프로그래밍 #12 - Anti-Aliasing
## Aliasing
- 계단 현상
    - 고주파수 신호가 저주파수 신호로 보이는 것
        - 샘플링 수가 부족할 때 발생!
    ![image](https://user-images.githubusercontent.com/11372675/149685262-0f0d23f8-7a95-4afd-9eeb-be7dc4092d78.png)
- 근본적인 해결책은 샘플링 수를 높이는 것.
    - 하지만 그렇지 못하는 상황에서는? anti-aliasing을 하자
- 폴리곤의 경계에 있는 프래그먼트들을 어떻게 처리해야할까?
    - 래스터라이제이션 과정에서 픽셀의 중점을 기준으로 포함 여부 결정
- 3차원 오브젝트를 float 형으로 각 점의 좌표로 표현 -> 래스터라이제이션 -> 프래그먼트 -> 필셀 => 해상도가 샘플링 수
## Anti-Aliasing Techniques
- Aliasing and Line Drwaing
    - Lines by sampling at intervals of one pixel and drawing the closest pixels
        - results in stair-stepping
        ![image](https://user-images.githubusercontent.com/11372675/149685336-b1ac3bad-9270-47b7-a929-ee59ffa7465f.png)
    - 이것도 계단 현상이 일어난다.
- Anti-aliasing Lines
    - Idea
        - 선을 더 두껍게 만든다.
        - Fade line out(removes high frequencies)
        - Now sample the lineResults in stair-stepping
    - solution 1 : Unweighted area sampling
        - treat line as a single-pixel wide rectangle
        - color pixels according to the percentage of each pixel covered by te rectangle
        ![image](https://user-images.githubusercontent.com/11372675/149685418-19fb487d-3723-454c-a857-fa2cca0a1d48.png)
        - pixel area is unit squre
        - constant weighting fucntion
        - pixel color is determined by computing the amount of the pixel covered by the line, then shading accordingly
        - easy to compute, gives resonalbe resutls
    - solution 2 : weighted area sampling
        - treat pixel as a circle with a radius of one pixel
        - use a radially symmetric weighting function(ex. cone)
            - areas closer to the pixel center are weighted more heavily
        - better results than unweighted, slightly higher cost
    - solution 3: super-sampling
        - divide pixel up into "sub-pixels" : 2x2, 3x3, 4x4...
        - sub-pixel is colored if inside line
        - pixel color is the average of its sub-pixel colors
        - easy to implement(in software and hardware)
        ![image](https://user-images.githubusercontent.com/11372675/149685952-14b597f4-7745-4f3e-aa4b-450e192e00eb.png)
- Many Types of SuperSampling
    - Grid
        - Simplest algorithm
        - Fast and easy to implement
        - Aliasing can still occur if a low number of sub pixel is used due to the regular nature of sampling
    - Random
        - Stochastic sampling to avoid the regularity of grid
        - Samples may end up being unnecessary many in some areas of the pixel and lacking in others
    - Poisson Disc
        - Random but checks that and two are not Too Close
        - Result is even but random
        - Computational Time too expensive
    - Jittered
        - Modification of grid algorithm to approximate the poisson disc
        - A pixel is split into sub-pixels and a sample is taken from random point within the sub-pixel
        - COngregation can still occur but to a lesser degree
    - Rotated Grid
        - 2x2 grid layout is used but rotated to avoid samples aligning on the horizontal or vertical axis
        - Greatly improves the anti-aliasing quality

- OpenGL Multismapling
    - so simple
        - sb::application::init() 함수 오버라이드
            ``` C++
            virtual void init(){
                sb6::applicaiton::init();
                // sample값이 클수록 더 화질이 좋아짐
                info.samples=8;
            }
            ```
        - startup() 함수에 "glEnable(GL_MULTISAMPLE);"추가
            ``` C++
            glEnable(GL_MULTISMAPLE);
            ```