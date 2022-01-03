# 운영체제 #6
- 멀티 프로그래밍이 가능해졌는데, CPU 시간이 돈과 직결되기 때문에 모든 사람들이 많은 CPU 시간을 할당 받기를 원한다. -> 어떻게 할당을 해줘야 할까?
## Scheduling이란 무엇인가
- CPU Scheduling
    - 어떻게 Process에게 CPU의 사용을 할당할 것인가
        - Multiprogramming에 기반함 -> Memory 내의 실행 준비된(Ready State)의 Process들 가운데 하나에게 CPU를 할당함
- CPU Scheduling의 목표
    - CPU 사용률과 처리량의 확대
    - CPU가 노는 시간 없이 계속 돌게 하는 것이 최종 목표
## CPU Burst
- CPU - I/O Burst Cycle
    - CPU Burst : CPU로 연산을 수행하는 시간
    - I/O Burst : I/O 처리를 위해 기다리는 시간
    - 일반적인 프로세스는 두 Burst를 번갈아 가며 수행함
- Process 분류에 따른 CPU Burst의 특징
    - CPU-Bound Process : 짧은 주기의 긴 CPU Burst
        - CPU Burst가 길고, I/O가 짧다(압축, 컴파일 같은 것)
    - I/O-Bound Process : 긴 주기의 짧은 CPU Burst
        - CPU Burst가 짧고, I/O가 길다(입력이 중요한 게임 같은 것)
    - 어떤 종류의 Process가 많은지에 따라 스케줄링 기법의 효율성이 달라짐
- Histogram of CPU-Burst Times
    - 서로 다른 Process, System에도 불구하고, 대체적으로 아래와 같은 경향을 보임
## Scheduling의 종류
- CPU Scheduling의 결정은 다음 시점에 따라 이루어짐
    1. Running에서 Waiting 상태로
    2. Running에서 Ready 상태로
    3. 수행 종료
- 비선점형 스케줄링(Non-Preemptive Scheduling)
    - 1과 3의 상황에서만 수행되는 Scheduling 기법
    - Multiprogramming의 기본 Scheduling - OS가 강제로 CPU 사용을 해제하지 못함
- 선점형 스케줄링(Preemptive Scheduling)
    - 그 외의 다른 Scheduling 기법
    - OS가 현재 CPU를 사용하고 있는 Process의 수행을 정지할 수 있음
        - 2.의 상태 변이가 일어남
- OS가 다음 실행할 Job을 누구로 설정할 것인가가 1번 waiting상태로 넘어가는 단계(I/O)
- 2번은 I/O때문이 아니라 Time-Sharing을 위해서 쉬어야 할 경우 Ready 상태로 넘어감
- 비선점형 스케줄링은 OS가 강제로 "너 나와"라고 할 수 없음
- 선점형 스케줄링은 OS가 강제로 프로세스 수행을 정지 가능(운영체제 관여 증가)
    - 정지를 하고, 누구를 실행하게 할지도 결정해야 하기에 2번에 해당하는 상태 변이 실행
## Scheduling Criteria(평가기준)
- CPU 사용률(CPU Utilization)
    - 전체 시스템 시간 중 CPU가 작업을 처리하는 시간의 비율
- 처리량(Throughput)
    - CPU가 단위 시간 당 처리하는 프로세스의 개수
- 응답 시간(Response Time)
    - Interactive System에서 요청 후 첫 응답이 올 때까지의 시간
- 대기 시간(Waiting Time)
    - Process가 Ready Queue내에서 대기하는 시간의 총합
    - 스케쥴링이 잘못 되어서 어떤 프로세스가 계속 대기하고 있는 경우를 생각한 것
- Turnaround Time
    - Process가 시작해서 끝날 때까지 걸리는 시간
    - 실행 프로세스가 왔다갔다만 하다가 프로세스가 늦게 끝날 경우를 생각한 것
- 이상적인 스케줄러
    - 최대의 CPU 사용률
    - 최대의 처리량
    - 최소의 응답시간
    - 최소의 대기시간
- 모든 조건을 만족 시키는 Scheduler를 만드는 것은 현실적으로 불가능
- 상충하는 조건들이 있음 -> 용도에 따라 다른 요구사항
- 시스템의 용도에 따른 요구사항이 달라짐
    - 슈퍼 컴퓨터 - CPU 사용률
    - 개인용 컴퓨터 - 응답시간
    - 워크 스테이션 - 처리량
## Scheduling Algorithms
1. FCFS Scheduling
    - 먼저 CPU 할당을 요청한 Process에 CPU를 먼저 할당한다.
        - FIFO Queue를 사용하여 간단하게 구현 가능
        - 비선점형 스케줄링(운영체제가 관여할 수 없음)
    - ex. (Process-BurstTime) : p1-24, p2-3, p3-3
        - (1) P1,P2,P3 순서로 요청하였을 때
            - 대기 시간 : p1=0, p2=24, p3=27
            - 평균 대기 시간 : (0+24+27)/3=17
        - (2) p2,p3,p1 순서로 요청하였을 때
            - 대기 시간 : p1=6, p2=0, p3 = 3
            - 평균 대기 시간 : (6+0+3)/3 = 3
            - (1)의 경우 보다 짧은 대기 시간을 가짐
        - 작업의 수행 순서에 따라 대기 시간이 변할 수 있음
    - 짧은 대기시간을 언제나 보장하지 않는다!! -> 운영체제의 본질에 다가갈 수 없다.
2. Shortest Job First Scheduling
    - 다음 CPU Burst Time이 가장 짧은 Process에 CPU를 먼저 할당한다.
        - 최소의 평균 대기 시간을 제공
    - 비선점형 방식
        - 한 번 CPU를 할당 받으면 자신의 CPU Burst Time이 끝나기 전에는 놓지 않는다.
    - 선점형 방식
        - CPU를 할당 받아 수행 중이더라도 CPU Burst Time이 자신의 현재 남은 시간보다 짧은 시간을 가진 프로세스가 새로 생성되면 CPU를 양보한다.
        - Shortest Remaining Time First Scheduling (SRTF)
    - ex. (Process-ArrivalTime-BurstTime) : p1-0.0-7, p2-2.0-4, p3-4.0-1, p4-5.0-4
        - 비선점형(p1-p3-p2-p4)
            - 평균 대기 시간 = (0+6+3+7)/4 = 4
            - p2는 p1을 기다리다가 p3가 와서 또 양보해야함
        - 선점형(p1-p2-p3-p2-p4-p1)
            - 평균 대기 시간 = (9+1+0+2)/4 = 3
            - 남아있는 시간 기준으로 함.
3. Priority Scheduling
    - 미리 주어진 Priority에 따라 CPU를 할당
        - 비선점형 방식
            - 한 번 CPU를 할당 받으면 자신의 CPU Burst Time이 끝나기 전에는 놓지 않는다
        - 선점형 방식
            - 새로 생성된 Process가 현재 실행되는 Process보다 높은 Priority를 가지고 있는 경우, CPU를 양보한다.
    - 문제점 - 기아 상태(Starvation)
        - 낮은 Priority를 가진 Process는 전혀 수행되지 않을 수 있다.
    - 해결 방법 - Aging 기법
        - 할당을 기다리는 시간에 따라 Priority를 증가시켜 주는 방법
    - Interactive System이나 Kernel System처럼 우선순위를 정해야 할 필요성이 있을 수 있음
    - Time Burst만으로는 힘들고, Priority를 만들자
    - Shortest Job은 일종의 Priority임
    - Aging은 기다리는 시간이 길어지면 Priority를 증가시켜 주는 것
4. Round Robin Scheduling
    - CPU를 시간 단위(Time Quantum)로 할당
        - Time Sharing과 아주 유사함
        - 선점형 Scheduling 방식
        - 보통 Time Quantum은 10~100 milliseconds
        - Time Quantum만큼 수행 한 Process는 Ready Queue의 끝으로 들어가 다시 할당을 기다림
        - 문맥 전환이 많음(값 백업, 복원 하는 동안 CPU가 하는 일이 없음)
        - 응답 시간이 짧다.(컴퓨터가 프로세스를 처리할 때 계속 전환이 되지만 우리가 체크하지 못하는 것과 같음) -> 응답 시간이 적어서 많이 사용됨
    - ex. (Process-BurstTime): p1-53, p2-17,p3-68,p4-24
        - p1-p2-p3-p4-p1-p3-p4-p1-p3-p3
        - Time Quantum = 20
    - 성능
        - Ready Queue 내의 Process : n개
        - Time Quantum : q 시간
        - 각각의 Process가 할당 받는 시간 : 1/n 만큼의 CPU 시간을 q로 쪼개어 할당 받음
        - 각 Process의 다음 Time Quantum이 돌아오기까지의 대기 시간 : 최대(n-1)*q
        - 성능
            - q가 클 경우 : FCFS
            - q가 작을 경우 : 문맥 전환에 필요한 시간보다 낮다면 효율이 매우 떨어짐
            - => 적당해야한다.
5. Multilevel Queue Scheduling
    - Ready Queue를 여러 개의 Queue로 분리하여, 각각에 대해 다른 Scheduling Algorithm을 사용하는 기법
    - Foreground Queue
        - Interactive한 동작이 필요한 Process를 위한 Queue(ex. 게임)
        - Round Robin 기법 사용
    - Background Queue
        - CPU 연산 작업을 주로 수행하는 Process를 위한 Queue
        - FCFS 기법 사용
    - 각 Queue에 CPU를 어떻게 할당할 것인지를 결정해야 함
        - Queue에 대한 Priority 또는 Time Slice를 사용할 수 있음
        - CPU 연산만을 수행하는 프로세스는 CPU 처리량을 위주로 해야함(timeslice는 cpu time)
    - Real-Time Processes / Normal Processes / Batch Processes
        - Real-Time Process : 실시간 처리가 필요한 것들
        - Normal Process : Round Robin
        - Batch Process : 한 번 시작되면 끝날 때까지 실행되어야 하는 것들
6. Multilevel Feedback Queue Scheduling
    - Multilevel Queue에서 Process들이 서로 다른 Queue로 이동할 수 있도록 한 Scheduling 기법
        - Aging의 한 방법으로 사용됨
    - 필요한 요소들
        - Queue의 개수
        - 각 Queue마다의 Scheduling 기법
        - 언제 Process를 한 단계 높음 Queue로 옮길 것인가
        - 언제 Process를 한 단계 낮은 Queue로 옮길 것인가
        - 어떤 Process가 특정한 Service를 필요로 할 때 그 것을 제공하는 Queue로 옮겨줄 방법
    - 어떤 순간이 되니까 프로세스들이 Queue를 왔다갔다 해야 할 필요가 있음
    - Queue들 끼리도 이동이 가능
    - ex. Qo(Quantum =8) -> Q1(Quantum = 16) -> Q2(FCFS)
        - Q0으로 종료가 되지 않으면 Priority가 낮다고 생각하고 Q1으로 이동
        - 그래도 종료가 되지 않으면 Burst Time이 길다고 판단하여 FCFS로 수행
        - 새로운 Process가 들어오면,
            1. Q0에서 8ms동안 수행
            2. 1에서 종료가 되지 않았다면 Q1으로 이동, 16ms동안 수행
            3. 2에서도 종료가 되지 않으면 Q2으로 이동, FCFS로 수행
            - 생성되고 8+16ms동안 종료되지 않은 Process는 많은 CPU 작업을 필요로 하는 Process로 간주하여 FCFS기법을 이용해 충분한 CPU Time을 할당해주는 Scheduling 방법
## 4 Multiple Processor Scheduling의 구분
    - 여러 개의 CPU를 사용하는 System의 경우, CPU Scheduling이 매우 복잡해짐
        - 각각의 CPU에 서로 다른 I/O 장치가 연결되어 있다면?
        - 각각의 CPU가 서로 다르다면?(명령어 set, 처리 속도)
    - 비대칭 멀티프로세싱(Asymmetric Multiprocessing)
        - 하나의 CPU만이 시스템 자료 구조(Scheduling, I/O 작업 등) 관리
        - 모든 CPU가 접근할 경우보다 데이터 공유가 간단히 이루어짐
            - Kernel Multithread 지원이 안 되는 경우
    - 대칭 멀티프로세싱(Symmetric Multiprocessing)
        - 대칭 멀티프로세싱은 모든 CPU가 I/O작업 같은 프로세스에 접근이 가능한 경우
        - 매우 복잡해지긴 하지만 성능 면에서는 좋아짐
    - Processor Affinity
        - 과거에 수행하던 CPU에 Process를 배정하는 방법
    - Load Balancing
        - CPU가 동일할 경우, 동일한 Process들을 수행할 수 있음
        - CPU마다 각각의 Ready Queue를 둘 경우
            - 일부 CPU에 Process가 집중될 수 있음
        - CPU 모두에 하나의 Ready Queue만을 둘 경우
            - 사용 가능한 CPU에 차례대로 Process를 배정
    - 6개의 프로세스가 들어갈 수 있는 CPU, 4개의 프로세스가 들어갈 수 있는 CPU 이렇게 각각 Ready Queue에 차이가 있을 경우, 6개의 프로세스가 들어갈 수 있는 CPU에 집중될 가능성이 있음
        - 그것보다는 CPU 모두에 하나의 ReadyQueue만 둬서 사용 가능한 CPU에 차례대로 배정하는 것이 낫다.