# 운영체제 #3
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

## User Mode와 Kernel Mode
- CPU의 2가지 이상의 실행 모드
    - System Protection을 위해서 필요
        - 실행 Mode의 권한에 따라 접근할 수 있는 메모리, 실행 가능 명령어가 제한된다.
    - 각각의 Mode별로 권한(Privilege - 특권)이 설정된다.
    - Hardware 지원이 필요
        - Intel : ring 실행모드 지원 - 0~3,4개의 Mode제공
        - 그 외 프로세서 : 2개의 Mode 제공
- Kernel Mode
    - 모든 권한을 가진 실행 Mode
    - 운영체제가 실행되는 Mode
    - Privilege 명령어 실행 및 레지스터 접근 가능
        - ex. I/O 장치 제어 명령어, Memory Management Register - CR3
- User Mode
    - Kernel Mode에 비해 낮은 권한의 실행 Mode
    - 어플리케이션이 실행되는 Mode
    - Privilege 명령어 실행 불가
- 실행 Mode 전환(Execution Mode Switch)
    - User Mode에서 실행중인 Application이 Kernel Mode의 권한이 필요하 서비스를 받기 위한 방법이 필요 -> 실행 모드 전환이 통로
- System Call
    - User Mode에서 Kernel Mode로 진입하기 위한 통로
    - Kernel에서 제공하는 Protected 서비스를 이용하기 위해 필요
        - 하드웨어에 직접적인 접근이 가능한 서비스
        - Open : a file or device
        - Write : to file or device
        - Msgsnd : send a message
        - Shm : attach shared memory
    - 저는 Open 안쓰고 fopen 쓰는데요? : c라이브러리를 보면 이미 open을 사용중
    - trap이라는 function을 call하면, system call table에서 찾아서 그 코드가 구현되어있는 곳과 연결 -> 명령어 실행한 후에 리턴 값을 UserApplication에 넘겨줌
    - input값이 있는 경우 Address X 에 있는 것을 register X라는 곳에 저장을 해주고, 시스템콜을 불러서 사용할 때 register에 있는 값을 가져온다.
    - 시스템콜 종류
        | | windows | unix
        |:--:|:--:|:--:|
        |Process | Create Process() | fork()
        |Control | ExitProcess() | exit()
        |  | WaitForSingleObject() | wait()
        | File | CreateFile() | open()
        | Management | ReadFile() | read()
        |  | WriteFile() | write()
        |  | CloseHandle() | close()
        |  | SetConsoleMode() | ioctl()
        | Device | ReadConsole() | read()
        | Manipulation | WriteConsole() | write()
        | Information | GetCurrentProcessID() | getpid()
        | Maintenance | SetTimer() | alarm()
        |  | Sleep() | sleep()
        | Communication | CreatePipe() | pipe()
        |  | CreateFileMapping() | shmget()
        |  | MapViewOfFile() | mmap()
        | Protection | SetFileSecurity() | chmod()
        |  | InitializeSecurityDescriptor() | umask()
        |  | SetSecurityDescriptorGroup() | chowm()

- 일반적인 커널의 구조
    - Application이 바로 Hardware에 들어가는 것을 막고, 하드웨어가 문제면 하드웨어만 고치고, OS가 문제면 OS만 고칠 수 있도록 하기 위함

## Kernel Designs
- Kernel Desgin
    - 구현 / 개발
    - 수정 / 디버깅
    - 유지 / 보수
    - 확장
    - 성능
- Monolithic Kernel (성능 최고)
    - Kernel의 모든 Service가 같은 주소 공간에 위치
    - 커널의 모든 기능이 하나의 주소에!
    - 어플리케이션은 자신의 주소 공간에 커널 코드 영역을 매핑하여 커널 서비스 이용
    - H/W 계층에 관한 단일한 Abstraction을 정의
        - 이를 사용하기 위해, 라이브러리나 어플리케이션에게 단일한 인터페이스 제공
        - 각 주소의 커널은 똑같은 코드를 가지고 있고, 각각의 어플리케이션에게 제공
    - 장점
        - 어플리케이션과 모든 kernel 서비스가 같은 주소공간에 위치하기 때문에, 시스템콜  및 Kernel 서비스 간의 데이터 전달 시 overhead가 적음
    - 단점
        - 모든 서비스 모듈이 하나의 바이너리로 이루어져 있기 때문에 일부분의 수정이 전체에 영향을 미침(수정 및 디버깅이 힘들다)
        - 각 모듈이 유기적으로 연결되어 있기 때문에 Kernel 크기가 커질수록 유지/보수가 어려움(어디를 고쳐야할 지 모름)
        - 한 모듈의 버그가 시스템 전체에 영향을 끼침(어떤 부분에 뭐를 추가해야 할 지 잘 모름 - 확장성이 낮음)
- Micro Kernel
    - Kernel Service를 기능에 따라 모듈화하여 각각 독립된 주소 공간에서 실행
    - 이러한 모듈을 서버라 하며, 서버들은 독립된 프로세스로 구현
    - 마이크로 커널은 서버들 간의 통신(IPC)
        - 커널이 어플리케이션의 서비스 콜 전달과 같은 단순한 기능만을 제공
    - 장점
        - 각 Kernel 서비스가 따로 구현되어 있기 때문에 서로간의 의존성이 낮음
            - Monolithic Kernel보다 독립적인 개발이 가능
            - Kernel의 개발 및 유지 보수가 상대적으로 용이
        - Kernel 서비스 서버의 간단한 시작/ 종료 가능
            - 불필요한 서비스의 서버는 종료
            - 많은 메모리 및 CPU resource 확보 가능
        - 이론적으로 Micro Kernel이 Monolithic보다 안정적
            - 문제 있는 서비스는 서버를 재시작하여 해결
        - 서버 코드가 Protected memory에서 실행되므로, 검증된 S/W분야에 적합
            - ex. 의료 컴퓨터 분야
    - 단점
        - Monolithic Kernel보다 낮은 성능을 보임
            - 독립된 서버들 간의 통신 및 Context Switching
- Hypervisor
    - VirtualMachine을 보면 Window로 VirtualMachine 앱을 사용하고, VM으로 Linux를 열었음. -> Linux에서 Hardware로 접근하려면 VM, Window를 거쳐야 하기 때문에 성능이 매우 안 좋음
        - cloud servie를 사용하자
        - VM, Window 부분을 합침
    - 가상화된 컴퓨터 H/W 자원을 제공하기 위한 관리 계층
        - 게스트 OS와 H/W 사이에 위치함
        - 게스트 OS- Hypervisor가 제공하는 가상화된 H/W 자원을 이용하는 운영체제
    - 각 게스트 OS들은 각각 서로 다른 가상 머신(Virtual Machine)에서 수행되며, 서로의 존재를 알지 못함
        - H/W에 대한 접근은 Hypervisor에게 할당 받은 자원에 대해서만 수행
    - Hypervisor는 각 게스트 OS간의 CPU, 메모리 등 시스템 자원을 분배하는 등 최소한의 역할을 수행
    - 장점
        - 하나의 물리 컴퓨터에서 여러 종류의 게스트 OS 운용이 가능
            - 한 서버에서 다양한 서비스를 동시에 제공 - Cloud Service
        - 실제의 컴퓨터가 제공하는 것과 다른 형태의 명령어 집합구조(Instruction Set Architecture)를 제공
            - 다른 H/W 환경으로 컴파일 된 게스트 OS 및 응용프로그램도 실행 가능
    - 단점
        - H/W를 직접적으로 사용하는 다른 운영체제에 비해 성능이 떨어짐
            - 반가상화(Para-Virtualization)로 성능저하 문제를 해결하려함
                - 단, 게스트 OS의 H/W 의존적인 코드에 대한 수정이 요구됨
                    - 높은 기술적인 능력이 필요함
                    - OS의 소스가 공개되지 않았다면 게스트 OS로 수정이 불가








