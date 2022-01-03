# 운영체제 #5
## 컴퓨터 구조
- 시스템 측면에서 CPU, Memory, 마우스, 키보드 등등의 I/O장치를 어떻게 잘 다뤄야 할까?
- 단일 Bus 구조
    - Bus
        - CPU, RAM, I/O 장치 간 데이터가 전송되는 통로
            - Data 버스, Address버스
    - 단일 Bus
        - 하나의 시스템 버스에 여러가지 모듈이 연결
        - CPU, Memory, I/O의 속도가 비슷했던 초창기에 발생
        - CPU, Memroy, I/O의 속도 격차 증가 -> 병목 현상 발생
        - 초창기에는 단일 Bus로 해도 문제가 없었는데, I/O기기들이 CPU의 속도를 따라가지 못하면서 병목현생이 발생하기 시작
    - 병목 현상
        - 같은 버스에 연결된 디바이스들 사이의 속도 차이로 인해 발생
            - CPU > Memory > I/O로 속도의 격차가 커짐
        - 빠른 디바이스가 처리하는 양 만큼을 느린 디바이스가 처리하지 못함
            - 전체 시스템 속도는 느린 디바이스의 속도로 제한된다.
        - ex. CPU는 초당 5단위의 일을 처리할 수 있는데, 메모리가 초당 3 단위의 일만 전달해 줄 수 있다고 할 때, 전체 시스템 속도는 메모리의 속도로 제한된다.
    - 속도 비교
        - CPU와 메모리 속도
            - CPU는 X 기가헤르츠 -> (1/X)나노 세컨드
            - 메모리속도는 (10/X)나노 세컨드 -> 그래도 몇 나노세컨드
        - 메모리와 Disk
        - Disk와 네트워크
        - 그 밖의 I/O 장치 - CD, Keyboard
        - I/O 장치는 확연하게 느리다. 하드웨어적으로는 차이를 좁히기 어려움
- 계층적 버스 구조
    - 세분화된 버스 채용 : CPU Local Bus, Memory Bus, PCI Bus, etc
    - 이중 버스
        - CPU와 I/O 속도 격차로 인한 병목 현상 해결하고자 함
        - 빠른 CPU와 메모리는 시스템 버스에 연결
        - I/O 장치는 I/O 버스에 연결
        - CPU와 I/O에 의한 Bottleneck은 완화되었지만, 여전히 CPU와 Memory 사이의 병목 현상은 있을 수 있다. -> 완벽하지는 않구나.
- Basic HW Mechanisms
    - Event Handling Mechanisms
        - Interrupt
        - Trap
    - I/O Device Basic Concept
    - I/O 처리 기법
        - Polling
        - Direct Memory Access (DMA)
    - I/O Device Access 기법
        - I/O Instruction
        - Memory Mapped I/O
## Interrupt, Trap
- 이벤트 : 어떠한 사건이 발생
- 프로그램의 실행 내용들은 당연하게 일어나야 하는 것이기에 사건이라고 부르지 않음
- 대신 프로그램 종료, Exception, 시스템 콜, 에러 등등 프로그램의 실행과 관련 없는 것은 Event가 될 수 있다.
- 이벤트를 어떻게 처리할까?
    - 비동기적 이벤트 : 외부에서 발생한 이벤트(I/O, 네트워크 패킷 이벤트)
    - 동기적 이벤트 : 내부에서 발생한 이벤트
- 이벤트가 실행되면 기존에 하던 것을 중단하고 이벤트를 처리해주어야한다.
    - 이 이벤트가 외부에서 생성된 이벤트인가, 내부에서 생성된 이벤트인가에 따라 변동이 있음
- 이벤트 처리 기법 : Interrupt
    - 비동기적 이벤트를 처리하기 위한 기법
        - ex. 네트워크 패킷 도착 이벤트, I/O 요청
    - Interrupt 처리 순서
        - Interrupt Diable
        - 현재 실행 상태 (State)를 저장
        - ISR(Interrupt Service Routine)로 점프
        - 저장한 실행 상태 (State)를 복원
        - 인터럽트로 중단된 지점부터 다시 시작
    - Interrupt에는 우선 순위가 있으며, H/W 장치마다 다르게 설정됨
    - Note
        - ISR은 짧아야 함 (너무 길면 다른 Interrupt들이 처리되지 못함)
        - Time Sharing은 Timer Interrupt의 도움으로 가능하게 된 기술이다.
    - 외부에서 언제 발생할 지 모르는 이벤트들 -> 비동기적 이벤트로, 따로 처리 필요
    - 실행상태 저장 -> 처리를 위해 ISR -> 실행상태 복원
    - 근데 Interrupt마다 우선순위가 있고, H/W마다 다르게 설정됨
    - Timer Interrupt는 다른 Interrupt보다 우선순위가 높음
        - 운영체제 주요 기능인 context switching 관련 부분이기 때문
- 이벤트 처리 기법 : Trap
    - 동기적 이벤트를 처리하기 위한 기법
        - ex. Divide by Zero와 같은 프로그램 에러에 의해 발생
        - Trap handler에 의해 처리
        - Trap Service Routine이 있기 때문에 Interrupt와 유사하지만, Interrupt와 달리 실행 상태(state)를 저장/복원 하지 않음
            - Trap은 동기적인 이벤트이기 때문
    - 프로그램 내에서 발생한 이벤트 처리 (에러, 시스템 콜)
- Intel x86 - Interrupt & Exception
    - Interrupt
        - Hardware Interrupt
            - Generated externally by the chipset, and it is signaled by latching onto the #INTR pin of the CPU
        - Software Interrupt
            - Signaled by software running on a CPU to indicate that it needs the kernel's attention (ex. System Call)
    - Exception
        - Occurred when the processor detects an error condition while executing an instruction
        - Type of exceptions
            - Fault (ex. Page Fault, Divide Error)
            - Trap (ex. Breakpoint, Overflow)
            - Abort (ex. Machine Check)
## I/O Device Basic Concepts
- Device Register
    - 보통 하드웨어 장치는 4종류의 Register를 가짐
    - Control Register, Status Register, Input Register, Output Register
    - Register들은 메인 메모리의 일부 영역에 Mapping
        - Mapping된 영역의 주소만 알면, CPU에서 접근 가능
- I/O Controller
    - High-Level의 I/O 요청을 Low-Level Machine Specific Instruction으로 해석하는 회로
    - 장치와 직접 상호작용
- 키보드 마우스 이런 것들은 register를 가짐
- 이 장치로 무엇을 할 수 있는지(control), 이 장치가 무엇을 하고 있는지 (status), input/output과 관련된 레지스터
## I/O 처리 기법
- Polling
    - Loop 안에서 특정 이벤트의 도착 여부를 확인하면서 기다리는 방법
    - Interrupt Handler를 등록하는 방식과 반대되는 개념
        - Polling은 매 순간 이벤트의 발생 여부를 확인
        - Interrupt는 I/O가 CPU에게 신호를 보내는 방식이기 때문
    - Controller나 장치가 매우 빠른 경우, Pollin은 Event처리 기법으로 적당함
    - 이벤트 도착 시간이 길 경우, Polling은 CPU Time을 낭비
        - 컴퓨터 시스템에서 CPU Time은 매우 귀중한 자원
    - Polling은 흔히 Programmed I/O로 알려진 방식
    - 아주 원시적인 방법. CPU가 Loop를 돌면서 계속해서 체크를 하는 것
- Direct Memory Access (DMA)
    - Polling을 사용할 경우, 모든 I/O 연산은 CPU에 의해 진행
    - 전송할 데이터가 클 경우, CPU를 Polling을 위해 I/O Device의 상태 확인 및 버스에 데이터를 쓰는 행위 (PIO)에 사용하는 것은 낭비
    - DMA Controller라는 프로세서 사용
        - CPU와 DMA Controller 간의 통신으로 I/O를 수행
        - CPU가 DMA Controller에게 I/O를 요청하면, DMA Controller는 CPU를 대신하여 I/O Device와 Main Memory 사이의 데이터 전송을 수행
            - CPUP는 I/O시간 동안 다른 일을 수행할 수 있음
    - CPU가 아닌 애가 Polling처럼 하면 어떨까? -> DMA를 고용해서 대신 처리하게하자!
        - DMA라는 셔틀을 운영하고있다! -> CPU가 DMA에게 심부름을 보냄
    - DMA - Read
        1. CPU는 DMA Controller 초기화하고 전송 모드를 DMA_MODE_READ로 설정
        2. CPU는 DMA Controller에게 buffer의 주소(X),크기(C)를 알려줌
        3. DMA Controller는 disk controller에게 데이터 전송을 요청
        4. Disk Controller는 매번 byte 단위로 읽어오는 Data를 DMA Controller에게 전송
        5. DMA Controller는 전송되는 데이터를 주소 x의 버퍼에 기록. 매 전송마다 C를 감소시키고, c=0이 될 때까지 전송
        6. C값이 0이 되면, 전송이 완료 된 것이므로, DMA Controller는 전송이 완료되었음을 Interrupt를 통해 CPU에 알림
        - buffer 뿐만 아니라 target이 되는 memory의 위치도 CPU가 알려줌
            - 어디에서 어떤 것을 가져와서 어디에 저장하라
        - C값은 count값, 이게 0이 되면 완료가 되었으니, CPU에게 Interrupt로 알려줌. 그러면 CPU가 할 일을 수행
    - DMA - Write
        1. CPU는 DMA Controller를 초기화하고 전송 모드를 DMA_MODE_WRITE로 설정
        2. CPU는 DMA Controller에게 buffer의 주소(X), 크기(C)를 알려줌
        3. DMA Controller는 disck controller가 write 준비가 되었는지 확인
        4. DMA Controller는 메모리 buffer로부터 데이터를 읽어와 disk controller에게 전달
        5. DMA Controller는 전송한 데이터 크기만큼 C값을 감소 시키고, C=0이 될 때까지 전송
        6. C값이 0이 되면, 전송이 완료 된 것이므로, DMA controller는 전송이 완료되었음을 Interrupt를 통해 CPU에 알림
        - CPU는 2번 이후에 자기 할 일을 수행할 수 있다.
- DMA vs Polling
    - DMA - 추가적인 Hardware 필요
    - 성능 - DMA를 최대한 활용하기 위해서는 적당한 Parallelism이 필요
        - I/O하는 동안 CPU가 해야 할 일이 있어야 한다. -> 성능 최대
    - ex. Smartphone Camera Pixel을 읽어 들이려고 할 때 DMA가 필요한가?
        - 보정이라던가, 압축 같은 CPU가 해야 할 다른 일도 있기 때문에 DMA가 유용
## I/O Device Access 기법
- I/O Instruction
    - Controller는 보통 1개 혹은 그 이상의 Register를 가짐
        - Data, Control Signal을 처리하기 위함
    - CPU는 Controller의 Register의 Bit Pattern을 읽고 씀으로써 장치와 통신
        - 이러한 기능을 수행하기 위한 명령어들이 제공
            - ex. Intel CPU의 I/O 명령어 ( in, out, ...)
    - 복잡한 하드웨어적인 구현이 필요(명령어 자체적으로 제공을 하기 때문)
    - 메모리 매핑하는 일련의 작업 없이 그냥 명령어로 실행
- Memory Mapped I/O
    - Device Register들을 Memory 공간에 Mapping하여 사용
        - Device Register가 Memory 주소에 Mapping이 되면, Register들은 주소 공간의 일부로 여겨짐
    - CPU는 일반적인 명령어를 사용하여 I/O 작업을 수행
        - ex. mov, and, or, xor ...)
    - 메모리 영역에서 써야 하니까 편하긴 하지만 성능이 별로일 수 있음
    - 메모리 할당을 해야 하기 때문에 다른 기능을 사용할 수 없음
## 운영체제에서 필요한 HW 요점
- 컴퓨터 시스템의 전체적인 구성 : 버스
- I/O Event Mechanisms : Interrupt, Trap
- I/O Handling Mechanisms : Polling, DMA
- Access Mechanisms : Instruction, Memory Mapping