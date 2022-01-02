# 운영체제 #1
## 운영체제란 무엇인가?
- 하드웨어를 손쉽게, 효율적으로 사용할 수 있는 Abstraction(추상화 - 구분)을 제공해준다.
    - CPU : Process
    - Memory : Address Space
    - Disk : File
    - Network : Port
    - 운영체제의 역할은 구분을 하는 것!
- 자원의 공유 및 분배를 위한 Policy(정책)을 결정한다.
    - Policy의 예 : FIFO, LRU
    - 설계 결정(Desgin Decisions)이 중요하다. (용도에 따라 중요도가 다르므로)
    - 단순히 성능뿐만이 아니라 배터리 소모, 안정성 등등을 위한 정책이 필요하다.

## Abstraction의 필요성
- 어플리케이션, User, CPU, Memory, SSD/HDD 내부에서도 구분이 필요하다.
- 이것을 구분짓는 것이 운영체제이다.
- 0과 1로 이루어진 데이터가 CPU에 입력되었을 때, 그 데이터가 어떤 어플리케이션에서 사용되어야 하는 지 구분할 수 없다.(하드웨어는 구분 못함)

## Abstraction : Process
- Program
    - 컴퓨터를 실행시키기 위한 일련의 순차적으로 작성된 32bit(요즘엔 64bit도 있음) 명령어의 모음
    - 컴퓨터 시스템의 Disk와 같은 Secondary Storage에 binary형태로 저장
- Process
    - 실행되고 있는 프로그램의 추상화
    - Program Counter, Stack, Data Section으로 구현된다.
        - Program Counter : 현재 실행중인 명령어의 주소 레지스터
        - Stack : 실시간 데이터 저장 공간
        - Data Section : 파일로 구성된 데이터들
    - 왜 필요하지? : cpu와 같은 hardware Component로 하여금 각 Program을 구분하여 인식, 실행할 수 있도록 하기 위함

## Abstraction : Address Space
- Process가 차지하는 메모리 공간
- 왜 필요하지?
    1. Protection  Domain : 서로의 주소 공간을 침범할 수 없음
        - ProcessA가 해커의 Process, ProcessB가 은행의 process라 할 때, 주소 공간이 구분되지 않으면 치명적인 문제가 생길 수 있음
    2. (Memory Mapped) I/O Device의 관리

## Abstraction : File
- Process에서 읽고 쓸 수 있는 Persistent Storage
- 실제 저장되는 위치를 Process는 알지 못함
- 왜 필요하지?
    - 하드웨어 상으로는 0과 1로 이루어진 데이터의 어디까지가 어떠한 프로그램인지 알기 어려움
    - File이라는 기능을 통해 각각의 데이터를 구분할 수 있다
    - 영구적으로 저장해야 하는 데이터들이 필요해서 전원이 꺼져도 저장이 될 수 있는 Persistent Data를 만들기 위해 File이 만들어졌다.

## Abstraction : Port
- 컴퓨터 시스템이 메시지를 주고 받는 Communication Endpoint;
- 왜 필요하지?
    - 구분이 없으면 Process A가 Process X에 보내야 할 정보를 Process A'에 보낼수도 있기 때문에 구분이 필요
    - 어떤 Process (또는 User)가 통신의 대상인지 구분 필요
    - (부수적으로 Privacy Issue 포함)

## Policy는 왜 필요할까?
- 시스템마다 다른 효율을 관리하기 위함
- 현재 운영체제가 쓰이는 영역
    - PC(Personal Computer) - 성능
    - Server & Data Center - 성능
    - Smartphone - 성능 + 매터리 소모
    - 자동차 - 안전
    - 원자력 발전소 - 안전
    - 사용하지 않는 프로세스는 중단하거나, 더 중요한 프로세스를 먼저 하거나...



## 운영체제의 특징(Application과 비교)
- System Software
    - 목적 : 컴퓨터의 시스템을 구동시키는 SW
    - OS 이외의 System Software : Compiler / Assembler
- Application Software
    - 목적 : 특정 용도로 사용됨
    - Word, Internet Explorer, Game, ETC.
- OS는 항상 동작
- 통제 기능으로서, 항상 자원에 대한 관리/ 감시 활동
    - Supervisor Mode (<->User Mode)
- 하드웨어에 대한 제어 기능
    - Device Driver

## OS & Kernel
- OS와 Kernel에 대한 두 가지 관점
    1. OS = Kernel(Linux Kernel만 OS이다.)
    2. OS = Kernel + GUI + Library(Linux Kernel과 Ubuntu 모두 OS다)
    - 보통은 2번 관점
- Kernel
    - 운영체제의 핵심 부분으로, 자원 할당, 하드웨어 인터페이스, 보안 등을 담당
- GUI(우분투)
    - 그래픽 사용자 인터페이스 (ex. iOS vs Android)
- Library
    - 자주 사용되는 함수들의 집합 (ex. libc, win32.dll)
    












