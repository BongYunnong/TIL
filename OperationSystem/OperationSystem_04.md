# 운영체제 #4
## 프로그램이 만들어지는 과정
- Source Code -Compiler-> Object File -Linker-> Executable File -Loader-> Memory
    - Executable File이 Memory에 저장되는 시점에 운영체제가 개입
## 컴파일러
- 역할 : 사람이 이해할 수 있는 프로그래밍 언어로 작성된 Source Code를 컴퓨터(CPU)가 이해할 수 있는 기계어로 표현된 Object파일로 변환
- Source Code (c file): 프로그램이 수행하고자 하는 작업이 프로그래밍 언어로 표현됨
- Object (o file)
    - 컴퓨터가 이해할 수 있는 기계어로 구성된 파일
        - 자체로는 수행이 이루어지지 못함
        - 01011001 이렇게 되어있기 때문에 프로세스로 변환되기 위한 정보가 삽입되어야 한다.
    - Relocatable Addresses(Relative Address)로 표현
        - 심볼들의 주소가 상대적인 값으로 표현된다.
        - 메모리에 올라갈 때 절대적인 주소로 하면 어디에 저장될 지 정해지지 않았기에 문제가 생김
        - ex. 시작 주소로부터 26바이트 지점
## 링커
- 역할 : 관련된 여러 Object 파일들과 라이브러리들을 연결하여, 메모리로 로드 될 수 있는 하나의 Executable로 변환
    - 라이브러리는 API를 생각하면 된다.(function의 묶음)
    - "라이브러리의 이 지점으로 가면 너가 원하는 함수가 있다."
- Executable (exe file)
    - 특정한 환경(OS)에서 수행될 수 있는 파일
    - 프로세스로의 변환을 위한 Header, 작업 내용인 Text, 필요한 데이터인 Data를 포함한다.
    - Absolute Addresses로 표현
        - 심볼들의 주소가 절대값으로 표현된다.
        - 아직 Physical Address는 아니다.
        - ex. 32026번 주소
- 컴파일러와 링커는 결과물이 수행될 OS와 CPU에 따라 다른 형태의 파일을 만든다.

## 로더
- 역할 : Executable을 실제 메모리에 올려주는 역할을 담당하는 운영체제의 일부
- 동작 과정
    - Executable의 Header를 읽어, Text와 Data의 크기를 결정
    - 프로그램을 위한 Address Space를 생성
    - 실행 명령어와 Data들을 Executable로부터 생성한 Address Space로 복사
    - 프로그램의 Argument들을 Stack으로 복사
    - CPU내 Register를 초기화하고, Start-up Routine으로 Jump
        - 컴퓨터마다 환경이 다를 수 있기에 register 초기화, 실행지점으로 jump
- 관건은 어떻게 메모리에 적재할 것인가이다.
## Runtime System
- 역할 : Runtime System은 응용 프로그램의 효율적인 실행을 지원하기 위해, 프로그램과 연결하여 상호 작용합
- C Runtime System Program Execution
    - GCC는 Start-up Code Object파일을 추가하여 프로그램을 컴파일 하며, 이 때 기본 라이브러리들도 동적으로 링크 된다.
    - Process를 시작하기 위해 커널은 Program Counter를 _start 함수의 주소로 지정
    - _start 함수는 동적으로 링크된 C라이브러리 및 쓰레드 환경을 초기화하기 위해 _lib_start_main_함수를 호출
    - 라이브러리 초기화를 진행한 이후, 프로그램의 main함수가 호출된다.

## Process Concept
- 역할
    - Execution Unit과 Protection Domain과 같은 Process-Abstraction을 위함
    - Execution Unit : 스케줄링의 단위(쓰레드가 여러 개 있으면 관리 필요)
    - Protection Domain : 서로 침범 불가
- Processs Implemented with
    - Program Counter : 현재 실행중인 명령어가 어떤 위치에 있는지
    - Stack : 실행과정의 데이터
    - Data Section : bgm같은 원래 데이터
- 프로세스는 디스크에 저장된 프로그램으로부터 변환되어 메모리로 로딩된다.

## Program Image
- Program Image가 exe, Loader가 OS라고 이해하자
- Laoder가 Text Size를 할당해줄 때 header의 text size 참고, text 복사해서 메모리에 적재
- Header의 Data Size 참고해서 할당
- 정적으로 선언이 되었지만 값이 할당이 안 된 요소들을 위해 미리 할당을 해주는 것이 bss
- 할당이 된 애들은 stack에 들어감

## Process State
- 운영체제는 멀티 프로세싱(메모리에 여러 프로세스가 올라갈 수 있음)을 지원하기 때문에 어떤 프로세싱은 실행되고있고, 실행 안 해도 되는지에 대한 State가 필요하다
- 종류
    - New : The Process is being Created
    - Running : Instructions are being executed
    - Waiting : The Process is Waiting for some event to occur
        - ex. an I/O completion or reception of a signal
    - Ready : The Process is Waiting to be assigned to a processor
    - Terminated : The Process has finished execution
- 커널 내에 Ready Queue, Waiting Queue, Running Queue를 두고 프로세스들을 상태에 따라 관리한다.
    - I/O하고있으면 대기중이기 때문에 Waiting으로 처리
    - New나 Waiting이 준비가 되면 Ready
    - 요즘엔 멀티코어라서 CPU가 여러 일을 처리할 수 있기에 Running Queue도 존재
- Process의 lifeCycle
    - Admit은 새로 생성된 프로세스가 실행 가능한지 체크
    - Time Sharing에 의해서 Timer Interrup 되거나 I/O로 들어가게 된다.

## Process Contorl Block - PCB
- Process Control Block : Each process is represented in the OS by PCB
    - 운영체제가 PCB를 통해 프로세스를 구분, 관리할 수 있다.
- Information associated with each Process
    - Process State
    - Program Counter
    - CPU Registers
    - CPU Scheduling Information
    - Memory Management Information
    - Accounting Information
    - I/O Status Information
## 문맥 전환 (Context Switch)
- Process 자체적으로 정보를 관리하기 위한 것들이 엄청 많구나!
- PC에 저장된 값이나 레지스터에 저장된 값들이 실행되는 프로세스가 바뀔 때 메모리에 저장된다(백업). 나중에 이 메모리에서 data를 가져온다(불러오기).
- Context Switching time is overhead
    - 문맥 전환중에는 시스템이 다른 일을 할 수 없기에 overhead가 됨
- Systemcall의 횟수, Context Switching의 overhead가 속도에 큰 영향
- PCB의 사이즈, register의 사이즈에 따라 속도가 변화

## 프로세서 구조에 따른 문맥전환의 차이
- CISC
    - 복잡한 명령어 셋 구성 -> 효율 높임, 클럭 속도 저하
    - 복잡한 회로 -> 물리적인 공간 차지 -> 레지스터 용량 저하
        - ex. Intel Pentium Processor
- RISC
    - 간단한 명령어 셋 구성 -> 클럭 속도 높임 -> 빠른 수행 속도
    - 절약된 물리적 공간에 보다 많은 레지스터 장착
        - 문맥 전환 시 레지스터 내용 변경에 보다 큰 오버헤드가 발생함
        - ex. ARM Processor
- CISC는 하나의 명령어 안에 여러 개의 동작을 담을 수 있음 -> 효율적이지만 복잡하고, 많은 공간을 차지 -> 백업하고 로드할 레지스터의 용량이 저하 => 성능 측면에서는 불리하지만 overhead는 낮음
- RISC는 간단한 명령어(하나의 명령어가 하나의 동작만) -> 빠름 - 레지스터를 많이 넣을 수 있음 but 문맥 전환에 큰 overhead가 발생
    - PCB의 크기도 중요하지만 하드웨어 레지스터의 크기도 영향을 줄 수 있구나.
- PCB0을 백업해두고, PCB1을 불러온다.
    - 이 과정에서 idle이 되어 아무것도 할 수 없는 context switching overhead가 발생
    - PCB1이 실행되고 있는데, interrup로 인해 실행이 끝나야 할 상황이 오면 PCB1을 저장하고, PCB0을 불러온다.
- Time Sharing에 의해 프로세스가 실행될 수 있는 시간은 제한되어있는데, Context Switching 때문에 Idle하는 상태가 길어지면 길어질수록 실제 실행할 수 있는 시간이 매우 줄어듦


## Process Creation
- 프로세스는 병렬적으로 실행될 수 있어야 한다.
- 프로세스는 동적으로 생성되고, 제거될 수 있어야 한다.
- 프로세스는 아주 큰 존재이기 때문에 아예 새로 만들기에는 무리가 있음
    - 아, Parent Process를 복사해서 Child Process를 만들면 되지 않을까?
        - 복사 대상이 Parent Process
        - 복사 받은 대상을 Child Process

- The Processes in the system can execute concurrently, and they must be created and terminated dynamically
- OS provides process createion and process termination mechanisms.
- Process Creation
    - Parent Process vs Child Process
    - Resource Sharing
        - Parent and Children share all resources
        - Children share subset of parent's resource
        - Parent and Child share no resource
    - Execution
        - Parent and Children execute concurrently
        - Parent waits until children terminate
- Memory(Text and Data Section)
    - Child process is a duplicate of the parent process
    - Child process has a program loaded into it.
    - Unix example
        - A new process created by fork system call
        - A new process (child process) consists of a copy
        - of the memory of the original process (parent process)
        - Exec(2) : to replace the memory with a new program
    - 복제를 한 후에 디스크에 있는 정보로 업데이트를 해줌
    - Fork 시스템콜을 통해서 parent를 복사한 child를 생성
    - 새로운 프로그램을 붙여넣기(linux에는 exec이라는 시스템콜이 있음)

- Linux
```
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char* argv[]){
    int counter=0;
    pid_t pid;
    printf("Creating Child Process\n");
    pid = fork();
    if(pic<0){ // Error in fork
        fprintf(stderr, "fork failed, errno : %d\n", errno);
        exit(EXIT_FAILURE);
    }else if(pid>0){ // This is Parents Process
        int i;
        printf("Parents(%d) made Child(%d)\n", getpid(), pid);
        for(i=0;i<10;i++){
            printf("Coutner:%d\n", counter++);
        }
    }else if(pid==0){ // This is child process
        int i;
        printf("I am Child Process %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL); // Run "ls =l" at/bin/ls
        for(i = 0;i<10;i++){ // Cannot be run
            printf("Counter : %d\n", counter++);
        }
    }
    wait(NULL);
    return EXIT_SUCCESS;
}
```
- Window
```
BOOL CreateProcess{
    LPCSTR IpAllicationName,
    LPTSTR IpCommandLine,
    LPSECURITY_ATTRIBUTES IpProcessAttributes,
    LPSECURITY_ATTRIBUTES IpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID IpEnvironment,
    LPCTSTR IpCurrentDirectory,
    LPSTARUPINFO IpStartupInfo,
    LPPROCESS_INFORMATION IpProcessInformation
};
...
#include <stdio.h>
#include <windos.h>
enum{loop=100};
int main(int argc, char *argv[]){
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemroy(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemroy(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);
    si.IpReserved =NULL;
    si.IpTitle = L"ChildProcess.exe";
    si.IpDesktop = NULL;
    si.dwX = 0;
    printf("Parent Process ID : %d\n", GetCurrentProcessId());
    if(!CreateProcess(L"ChildProcess.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
        fprintf(stderr,"Create Process failed(%d)\n", GetLastError());
        return EXIT_FAILURE;
    }
    pritnf("Child Process ID : %d\n", pi.dwProcessId);
    int i;
    for(i=0;i<loop;++i){
        printf("PID : %d, i : %d\n", GetCurrentProcessId(), i);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("child process exit\n");
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return EXIT_SUCCESS;
}
```
- PCB는 Linux에 가깝고, Window에서는 위와 같음.

## Process Termination
- 프로세스가 끝났는데 지워지지 않고 있으면 여러 에러사항이 있을 수 있음
- 프로세스가 끝났으면 운영체제에게 "나를 지워주세요"라고 요청해야함 -> exit system call
- the abory function causes abnormal process termination to occur
    - the SIGABRT signal is sent to the calling process
    - Core dump is made

## Cooperating Processes
- Independent Process cannot affect or be affected by the execution of another process
- Advantages of process cooperation
    - Information sharing
    - Computation speed-up
    - Modularity
    - Convenience
- 운영체제를 개발하다보니까 프로세스간에 협력하는 것이 이득일 경우가 있네?
    - ex. DBMS - 여러 프로세스가 Read/Write를 동시에 함 -> Interprocess communication이 가능하도록 하자!