# 운영체제 #2
## 컴퓨터의 기원
- Compute + er
- 2차 세계대전
    - 암호 해석(이미테이션 게임)
    - 미사일 탄도 분석
    - 물리 계산

## Hand Operated System
- 1950년대 초반
    - 당시 컴퓨터는 현재의 컴퓨터에 비해 매우 원시적
    - 프로그램인 기계적인 스위치를 이용하여 ,1bit 단위로 컴퓨터에 입력되어 실행
    - 진공관 기반 - 엄청나게 큰 크기, 많은 열 방출
- 1950년대 중반
    - 모든 프로그램은 기계어로 쓰여짐
    - 플러그 보드(Plug-Board)에 와이어링(Wiring)을 통해 컴퓨터의 기능 제어
    - 프로그래밍 언어 및 운영체제라는 존재가 없음
    - 영구적인 저장장치가 없음 -> 매번 프로그램 다시 입력
- 1960년대 초반
    - 펀치카드 등장
    - 프로그래밍한 카드로 컴퓨터 구동 -> 플러그 보드 대체

## Mainframe - 일괄처리(Batch)
- Business Machinery로써 쓰이면서 가치 발생
    - 계산을 하는데 주로 사용되기 시작
    - 교량(Bridge) 설계 - 경제 infra와 아주 밀접
- 일괄 처리(Batch)
    - 아주 단순한 개념
    - 일단 시작한 "Job"은 끝나야 다음 Job이 수행된다.
    - Punch Card를 제출하면 메모리에 적재, 수행의 순서로 진행
    - 결과를 받기까지 중간에 User Interaction이 불가
    - 사람이 Job을 Scheduling
- CPU가 빈번히 Idle 상태로 전환
    - 기계적인 I/O 장치와 전기 장치인 CPU 사이에 현격한 속도 차 존재
    - 도저히 사람이 펀치카드로 컴퓨터를 사용해서는 안되겠다!!

## Automatic Job Sequencing - 좀 더 나은 OS
- 사람의 관여 없이, 여러 개의 프로그램을 순차적으로 실행
- 이전 작업이 종료되자마자 다음 작업을 실행하기 때문에, 일괄처리(Batch)보다 성능이 향상
    - 일괄처리 : 사람이 직접 스케줄링
    - Automatic Job Sequencing : 담당 소프트웨어가 스케줄링
- I/O에 의해 CPU가 Idle상태로 전환되는 문제는 해결하지 못했다.
    - CPU의 속도가 하드웨어보다 매우 빠름
    - CPU가 돌고있는 시간이 다 돈인데, 이걸 어떻게 해결할수는 없을까?
## Spooling - 초기 해결책
- Simultaneous Peripheral Operation On-Line
- I/O와 Computation을 동시에 수행 가능 (ex. 프린터 스풀링)
    - 인쇄할 문서를 디스크나 메모리의 버퍼에 로드(그 후에 CPU는 자기 할 일 함)
    - 프린터는 버퍼에서 자신의 처리 속도로 인쇄할 데이터를 가져옴
    - 프린터가 인쇄하는 동안 컴퓨터는 다른 작업을 수행할 수 있음
- Spooling을 통해 사용자는 여러 개의 인쇄 작업을 프린터에 순차적으로 요청할 수 있음
    - 이전 작업의 종료를 기다리지 않고, 버퍼에 인쇄 작업을 로드하여 자신의 인쇄 작업 요청

## Multiprogramming
- 2개 이상의 작업을 동시에 진행
    - 운영체제는 여러 개의 작업을 메모리에 동시에 유지
    - 현재 실행중인 작업이 I/O를 수행하고있을 경우, 다음 작업을 순차적으로 실행
    - 스케줄링 고려사항 : First Come First Served
    - Spooling하는 와중에도 Request를 하는 데에 시간이 걸린다.
        - 메모리에 올리면 운영체제가 알아서 Job을 수행하겠다!
        - 멀티 프로그래밍은 하나의 메모리에 여러가지의 Job이 적재되는 것(멀태 태스킹과는 다름)
        - 운영체제가 프로그램을 관리하기 위해서 제공하는 첫번쨰 기능
        - 이 기능이 생기면서 Job들을 "구분"할 필요성이 생김(Batch는 구분 필요 X)
        - 또한, Job1이 I/O에 들어가면, 다음 작업은 누구인가? -> Policy 필요

- 멀티 프로그래밍의 목적
    - IO에 요청을 하는 시간 마저도 CPU가 일을 하도록 만들겠다
    - CPU 활용도(Utilization)증가 = CPU Idle Time 감소
- 단점
    - 사용자는 여전히 실행중인 작업에 대해서는 관여할 수 없다.(FCFS)
    - 마우스 클릭도 I/O인데, I/O에 들어가면 다음 작업으로 넘어가기 떄문에 Runtime에서 관여할 수 없다.

## Issues with MultiProgramming
- 다른 Job이 수행되기 위해서는 현재 수행되는 Job이 I/O를 하거나 수행이 종료되어야한다.
    - Voluntary Yield(자발적 양보)에 의존
    - 의도적으로 I/O를 안하면 불공정하게 하나의 작업만 계속 수행될 가능성이 있음
- 공평성을 유지할 필요 발생
    - 누구나 컴퓨터를 오래, 많이 쓰고싶어한다.
- High Priority로 수행할 필요 발생
    - FCFS가 아니라, 더 높은 우선순위의 것을 더 빨리 해야 할 경우가 생김
- Job Scheduling으로는 해결 X
    - 그럼 Time Sharing을 쓰자

## TimeSharing
- CPU의 실행 시간(각 작업)을 타임 슬라이스(Time Slice)로 나누어 실행
    - ex. 10ms
- 모든 프로그램은 타임 슬라이스 동안 CPU를 점유하고 그 시간이 끝나면 CPU를 양보(비자발적)
- 여러 개의 작업들이 CPU 스위칭을 통해 동시에 실행된다. (마치 동시에 실행되는 것처럼 보인다.)
- CPU 스위칭이 매우 빈번하게 일어남
    - 사용자는 실행중인 프로그램에 관여가 가능

## MultiTasking
- 여러 개의 Task들이 CPU와 같은 자원을 공유하도록 하는 방법
- 하나의 Program은 동시에 실행할 수 있는 Task(Job)으로 나눠질 수 있음
    - ex. 유닉스 프로세스는 fork()시스템 콜을 이용해 여러 개의 자식 프로세스를 생성
    - ex. 안드로이드 어플리케이션은 UI 처리, 입출력 처리, 계산 처리 프로세스 등 다수의 프로세스를 생성
    - MultiTasking은 사용자가 여러 개의 프로그램을 실행할 수 있도록 하며, CPU가 Idle상태일 때는 Background 작업을 실행 가능하도록 함

## Example of DBMS MultiTasking
- Fork를 이용한 ChildProcess생성
    - 멀티 태스킹 : 여러 프로그램이 동시에 수행(Concurrent Execution)
    - 하나의  Task가 다른 Task(Child Process)를 만들 수 있는 기능을 의미
    - 자신이 필요한 기능을 Child Process 형태로 만들어 서로 협력을 통한 작업 수행

## Issues with Multitasking System
- 복잡한 메모리 관리 시스템
    - 동시에 여러 개의 프로그램이 메모리에 상주
    - 메모리 관리 및 보호 시스템 필요
- 적절한 응답 시간 제공
    - Job들은 메모리와 디스크로 Swap In/Out 될 수 있음
- Concurrent Execution제공
    - CPU 스케줄링 필요 (Policy)
- 필요에 따라서 Job들 간의 Orderly Execution이 필요
    - 동기화, Deadlock

## 그 외의 시스템
- MultiProcessor Systems
    - Symmetric vs Asymmetric Multiprocessors
- 분산 시스템
    - LAN/ WAN으로 연결
    - Client-Server Model, Peer-to-Peer Model
    - Bus와의 차이는..?
- Clustered Systems
    - 공동의 목적을 위해 여러 개의 시스템 네트워크를 통해 작업을 수행
- Embedded Systems
    - 특정 목적을 위한 운영체제 및 소프트웨어가 탑재된 형태의 시스템
    - MP3 Player, Smartphone, etc.
- Real-Time Systems
    - 시스템에서 수행하는 작업의 완료 시간 (Deadline)이 정해짐
    - Soft Real-Time, Hard Real-Time