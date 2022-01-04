# 운영체제 7
## 컴파일러(Compiler)
- 역할
    - 사람이 이해할 수 있는 플그래밍 언어로 작성된 Source COde를 컴퓨터(CPU)가 이해할 수 있는 기계어로 표현된 Object 파일로 변환
- Source Code (ex. c file)
    - 프로그램이 수행하고자 하는 작업이 프로그래밍 언어로 표현되어 있다.
- Object (ex. o file)
    - 컴퓨터가 이해할 수 있는 기계어로 구성된 파일
        - 자체로는 수행이 이루어지지 못함
        - 프로세스로 변환되기 위한 정보가 삽입되어야 함
    - Relocatable Addresses (Relative Address)로 표현
        - 심볼들의 주소가 상대적인 값으로 표현됨(상대 주소 - 정확하지 않은 임의의 주소)
        - ex. 시작 주소로부터 26바이트 지점
## 링커(Linker)
- 역할
    - 관련된 여러 Object 파일들과 라이브러리들을 연결하여, 메모리로 로드 될 수 있는 하나의 Executable로 변환
- Executable (ex. exe file)
    - 특정한 환경(OS)에서 수행될 수 있는 파일
    - 프로세스로의 변환을 위한 Header, 작업 내용인 Text, 필요한 데이터인 Data를 포함한다.
    - Absolute Addresses로 표현
        - 심볼들의 주소가 절대값으로 표현됨
        - ex. 32026번 주소
- 컴파일러와 링커는 결과물이 수행될 OS와 CPU에 따라 다른 형태의 파일을 만든다.
    - 가장 큰 차이는, 컴퍼알러는 아직까지 심볼들의 주소가 상대적이라는 것
    - 링커가 심볼들을 어떤 위치에 저장할 지 정함 -> 이 주소가 절대주소
    - 옛날에는 메모리 하나에 하나의 프로그램만 들어가서 가상으로 가진 주소가 실제 메모리의 공간에서도 진짜 주소가 되어서 절대주소라는 이름을 넣음
    - 시대가 변하면서 프로그램을 메모리에 다 넣을 수 없어서 부분적으로 넣었기에 가상 메모리의 주소와 절대주소가 완전 일치하지는 않지만 그래도 "절대주소"라는 명칭을 계속 사용한다.
## Cooperating Processes
- Independent process cannot affect of be affected by the execution of another process
- advantages of process cooperation
    - Information Sharing
    - Computation Speed-up
    - Modularity
    - Convenience
- 협력을 하고자 할 때, 어떻게 할 수 있을까? -> IPC
## IPC - Inter Process Communication
- Inter Process Communicaiton
    - Process들 간에 데이터 및 정보를 주고 받기 위한 Mechanism
    - Kernel에서 IPC를 위한 도구를 제공
        - system call의 형태로 Process에게 제공됨
- IPC의 필요성
    - Process 협력 모델 (Cooperation Process Model)을 구현하기위해 IPC가 반드시 필요
        - 실행중인 Process는 협력하는 다른 Process의 영향을 받음
- ex. 안드로이드 앱을 만들 때, UI Activity, Camera Activity 이렇게 따로 프로세스를 만듦. 프로세스간의 정보를 어떻게 주고받을 것인가? -> IPC
- IPC 모델 1 - 공유 메모리(Shared Memory)
    - Process의 특정 Memory 영역을 공유
    - 공유한 memory 영역에 읽기/쓰기를 통해서 통신을 수행
    - 응용 프로그램 레벨에서 통신 기능 제공
        - 공유 메모리가 설정되면, 그 이후의 통신은 Kernel의 관여 없이 진행 가능
    - ex. 데이터 베이스
    - 구현 IPC - Shared Memroy
    - 특정한 메모리 영역은 전역변수라고 생각하면 편함
    - shared memory는 별도의 복잡한 보내고 받는 기능 없이 메모리 읽기/쓰기만을 통해서 통신 수행
    - Kernel에서 특별히 다른 것을 하지 않아도 응용 프로그램 영역에서 통신 가능
    - 단점 : 저장한 메모리는 다른 기능을 위해 쓸 수 없음
- IPC 모델 2 - 메시지 교환(Message Passing)
    - Process간 Memory 공유 없이 동작 가능
    - 고정길이 메시지, 가변길이 메시지를 송/수신자끼리 주고 받음
    - Kernel을 통한 메시지 통신 기능을 제공
    - ex. 클라이언트 - 서버 방식의 통신
    - 구현 IPC - Pipe / Message Queue / Socket
    - 메모리 공유를 하지 않음 -> 전통적인 보내기 / 받기 방식으로 통신
    - socket처럼 주고 받음(대신 kernel이 메시지 주고받는 것을 도와줌)
    - 단점 : Kernel을 꼭 거쳐야 하기 때문에, context switching이 필요함
- IPC의 기본 동작
    - Shared Memory
        - Read and Write
        - Process들의 주소 공간의 일부를 공유 메모리로 설정하여, 프로그램에서 바로 접근
        - A,B,C가 있을 때, B가 만들고, C가 수저하고, A가 읽으려 하면 이 순서를 잘 지키도록 해야 한다.(동기화 이슈 해결 필요)
    - Message Passing
        - Send and Receive
        - Kernel을 경유하여 Message 전송
        - Kernel에서 데이터를 버퍼링
        - 많은 Context switching이 필요하므로 성능적인 손실이 있음, kernel이 꼭 필요
        - 하지만 메모리를 자유롭게 활용할 수 있고, 동기화 이슈가 없음
- IPC에서 동기화의 필요성
    - Shared Memory - 부가적인 방법이 필요
        - Memory 영역에 대한 동시적인 접근을 제어하기 위한 방법이 필요
        - 접근 제어 방식은 Locking이나 세마포어(Semaphore) 방법이 있음
    - Message Passing - Kernel이 동기화 제공
        - Send와 Receive와 같은 연산에 대해서는 Kernel이 동기화
        - Send와 Receive를 수행할 때에는 Program에서 동기화에 대한 고려 없이 사용 가능
## 구현 IPC
- Pipe
    - 하나의 Process가 다른 Process로 데이터를 직접 전달하는 방법
        - 데이터는 한 쪽 방향으로만 이동함. 따라서 양방향 통신을 위해서는 두개의 Pipe가 필요(Half Duplex)
        - 1대 1의 의사소통만이 가능
        - 보내어진 순서대로만 받음
        - Pipe(256)이런식으로 선언하여 용량 제한이 있기 때문에, Pipe가 꽉 차면 더 이상 쓸 수 없음
        - 만약 프로세스 C도 통신을 하고싶다 하면 새로운 Pipe들을 만들어야한다.
    ``` C++
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>
    #define MAXLINE 4096
    int main(void){
        int n, fd[2];
        pid_t pid;
        char line[MAXLINE];

        if(pipe(fd)<0){
            perror("pipe error");
            exit(-1);
        }
        if((pid-fork()) < 0){
            perror("fork error");
            exit(-1);
        }else if(pid > 0){
            close(fd[0]);
            write(fd[1], "hello world\n",14);
        }else{
            close(fd[1]);
            n = read(fd[0], line, MAXLINE);
            write(STDOUT_FILENO, line, n);
            waitpid(pid,NULL,NULL);
        }
        exit(0);
    }
    ```
    - fd가 parent에서 child로 토인하기 위한 pipe라고 보면 됨(fd1이 보내고, fd0이 받고)
    - 만약 child에서 parent로 보내고 싶으면 새로운 fd를 만들어줘야함
    - 왜 굳이 0, 1? -> 커널에서 이미 pipe관련된 것을 만들어뒀는데, 1이 보내기, 0이 받기로 약속함
- Signal
    - 특정 Process에게 Kernel을 통해 Event를 전달하는 방법
        - 송신 Process: 여러 신호 중 하나를 특정 Process에 보냄. 이 동작은 수신할 Process의 상태에 무관하게 수행
        - 수신 Process: 신호 종류에 따라 신호 처리 방법을 지정 가능
            - 무시
            - 단순히 신호를 붙잡아 둠
            - 특정 처리 루틴 (Signal Handler)를 두어 처리
        - 비동기적인 동작
            - Process A가 Signal을 Process B에게 보내더라도, Signal 처리는 Process B가 Scheduling 되어야 가능함
    - 마치 Interrupt를 주는 것처럼 송신. 수신할 Process의 상태에 무관하므로 비동기적
    - 하지만 Interrupt는 무조건 처리를 해야하는 반면, Signal은 수신자가 신호 종류에 따라 신호 처리 방법을 지정 가능
    ``` C++
    #inlcude <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <signal.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    void SignalHandlerChild(int signo){
        printf("Signal Handler\n");
        fflush(stdout);
    }
    int main(void){
        pid_t pid;
        struct sigaction act_child;

        act_child.sa_hanlder = SignalHandlerChild;
        act_child.sa_flage = 0;
        sigemptyset(&act_child.sa_masx);
        sigaction(SIGUSR1, &act_child,0);
        switch(pid=fork()){
            case -1:
                perror("fork failed");
                exit(-1);
            break;
            case 0:
                sigpause(SIGUSR1);
                return 0;
            break;
            defualt:
                sleep(3);
                kill(pid, SIGUSR1);
                waitpid(pid,0,0);
        }
        return 0;
    }
    ```
    - Sigpause(SIGUSR1) 이것이 시그널
    - act_child.sa_handler = 이 부분이 미리 시그널을 정의하는 것(운영체제, 커널마다 달라서 굳이 중요하게 볼 필요 없음)
    - case 0이 parent process, default가 child process
    - child Process가 sleep 중이라도 시그널이 오면 처리하게 된다.
- Shared Memory
    - 두 개 이상의 Process들이 하나의 Memory 영역을 공유하여 통신하는 방법
        - Memory의 직접 사용으로 빠르고 자유로운 통신 가능
        - 둘 이상의 Process가 동시에 Memory를 변경하지 않도록, Process간의 동기화가 필요
        - 복잡해보이는 메모리 영역을 배열처럼 만듦
        - ptrShm[0]=11, ptrShm[1]=22;가 쓰는 부분
        - 이해하기 가장 좋은 예는 faster, slower pid
- Message Queue
    - 고정된 크기를 갖는 Message의 연결 리스트(Linked List)를 이용하여 통신을 하는 방법
        - Message 단위의 통신 - Message의 형태는 통신하고자 하는 Process간의 약속이 필요
            - Message의 형태는 사용자가 정의하여 사용
        - 여러 Process가 동시에 접근 가능 - 동기화 필요
        - Queue와 LinkedList를 합쳤다고 보면 됨(먼저 오는 것부터 먼저 빠져나감)
        - Int, char이런식으로 데이터를 저장했던 것이 무조건 Message 형식으로 바뀜
        - 약속을 통해 '어디에서 어디까지는 어떤 형식이다'라고 Message 형태를 정의 가능
- Socket
    - An end-point for communication
    - Port를 이용하여 통신하는데 사용됨
        - Port는 운영체제가 제공하는 Abstraction임
        - Port 번호를 이용하여 통신하려는 상대 Process의 Socket을 찾아감
    - 다른 IPC와 달리 Process의 위치에 Independent
        - Local 또는 Remote
        - Port의 도움으로 가능
            - Local의 경우, Port 번호만으로 식별
            - Remote의 경우, IP주소 + Port 번호 조합으로 식별
    - 연결(Connection)의 Semantics를 정할 수 있음
    - Process Independent
        - Port를 사용하기 때문에 Machine Boundary와 관계 없음
        - ex. Port로 여러 Web Browser를 생성
            - Remote Machine은 Local Machine의 Port만 보임(Socket은 보이지 않음)
            