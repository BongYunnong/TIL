# System Structure
## System Structure
- 운영체제는 규모가 매우 크고 복잡한 소프트웨어
    - 설계 시 소프트웨어의 구조를 신중히 고려해야한다.
- 좋은 설계를 통해 쉬워지는 것들
    - 개발(Develop)
    - 수정 및 디버깅(Modify and Debug)
    - 유지 보수(Maintain)
    - 확장(Extend)
    - +성능
- 디자인 목표 중에 좋은 것이란?
    - 설계하고자 하는 시스템의 목적과 관계가 있음
- Policy
    - 무엇이 되게 할 것인가? - 목적(안전, 성능 ...)
    - Supposed to be higher level, and use mechanism(highlevel로 간주)
    - 어떤 목적을 달성할 것인가? - 시스템과 연관
- Mechanism
    - 무엇을 어떻게 할 것인가? - Policy를 달성하기 위한 도구
    - ex. Concrete Algorithms, Data Structures
    - 공정한 스케줄링을 어떻게 할 것인가? - Time Scheduling Priority
- Mechanism과 Policy를 분리하여 운영체제 설계를 보다 모듈화 할 수 있음
- Abstraction(구분)
    - 운영체제에서 우선적으로 구분해야 하는 사용자/OS/Application/하드웨어를 구분하기 위해 어떤 매커니즘을 사용했을까?

## Layering
- OS의 복잡도를 낮추기 위한 방안
- Layer는 정의가 명확한 (Well-Defined)함수들로 이루어진다.
- 하나의 Layer는 인접한 Layer와만 통신
    - 위, 아래에 인접한 Layer와만 통신하며, 2단계 이상 건너뛰어야 하는 Layer와는 직접적으로 통신하지 않음
    - 설계의 복잡도를 낮출 수 있으나(a하는 사람은 a만, b하는 사람은 b만 설계), 그로 인해 Overhead가 발생한다.
    - ex. 7-layers of the OS model
    
- Layering의 장점
    - Layer의 수정이 다른 Layer와 독립적임
    - with modularity, layers are selected such that each uses functions(operations) and services of only the same(or lower) level layers
    - Modularity - 운영체제가 제공해야 하는 핵심 function별로 모듈을 나누는 것
    - Layer에 문제가 생기면 부분적으로 문제를 해결 가능
- 불완전한 Layering
    - Layer A에서 Layer C로 바로 접근하고싶은데..? 이건 너무 Critical하다.
        - 아주 Private한 부분에 악의적인 접근이 너무 쉬워진다.
        - 무분별한 하드웨어로의 접근을 막을 수 있음
    - kernel 내의 모듈들
        - signals/file system/CPU Schedulilng/Character I/O System/ Block I/O System/ Demand Paging/ Swapping/ Drivers/ Virtual Memory
        - Linux 디렉토리 / 커널 레이어 / 실제 하드웨어