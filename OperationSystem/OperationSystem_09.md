# 운영체제 #9
## 동기화 - Race Condition
- 공유 데이터에 대한 동시 접근은 데이터의 일관성(Consistency)를 해치는 결과를 낳을 수 있음
    - Race Condition : 공유 데이터에 대해 여러 Process가 동시에 접근, 변경을 시도하는 상황
- 데이터의 일관성을 유지하기 위해서는 서로 협력하여 수행되는 Process들(Cooperating Process)이 순차적으로 수행하게 만드는 기법이 필요함
    - Process 간의 동기화 (Process Synchronization)
    - ex. 은행의 입출금 문제
        - 1000원의 잔고가 남아있을 때, 500원의 입금과 500원의 출금이 동시에 일어날 경우, 그 결과는?
        - 컴파일러에 의해 잔고 처리 문장이 분해됨
        ```
        <Process A : 입금 처리>
        Register1 = Balance
        Register1 = Register1 + 500
        Balance = Register1
        ```
        ```
        <Process B : 출금 처리>
        Register2 = Balance
        Register2 = Register2 - 500
        Balance = Register2
        ```
        ```
        T0 : A Process Execute Register1 = Balance  [Register1=1000]
        T1 : A Process Execute Register1 = Register1 + 500  [Register1=1500]
        T2 : B Process Execute Register2 = Balance  [Register1=1000]
        T3 : B Process Execute Register2 = Register2 - 500  [Register2=500]
        T4 : A Process Execute Balance = Register1  [Balance=1500]
        T5 : B Process Execute Balance = Register2  [Balance=500]
        ```
        - Context Switching 상황에 따라서 500이 될 수도, 1500이 될 수도 있구나
            - 일관성이 깨졌다. -> 순서가 매우 중요하구나
## Critical Section
- Critical Section
    - 여러 Process들이 공유하는 데이터에 접근하는 Code영역
    - 한 번에 오직 하나의 Process만이 Critical Section에 진입해야 함
        - ex. 은행 입출금 문제의 Balance 증가 및 감소 관련 Code 영역
- Critical section을 가진 Process의 Modeling
    - Entry Section -Critical Section-> Exit Section -Remainder Section->
    - Entry Section에서는 혹시 다른 프로세스가 Critical Section에 들어가있는지 확인
    - Exit Section에서는 Critical Section에서 일을 다 한 후에 다른 누군가가 들어갈 수 있게 함
- Critical Section 해결의 조건들
    - Critical Section 문제를 해결하는 Algorithm은 아래와 같은 세 가지 조건을 만족해야 한다.
        - Mutual Exclusion(상호 배제)
            - 만약 Process A가 Critical Section에 진입해 있다면, 다른 모든 Process는 진입할 수 없어야 함
        - Progress(진행)
            - 만약 어떤 Process도 Critical Section내에 있지 않고, Critical Section에 진입하려는 Process가 존재하다면, Remainder Section에서 실행 중이 아닌 Process들 (진입하려는 Process들) 만이 누가 진입할 지 결정할 수 있어야 함 - 결정은 무한히 연기될 수 없음
        - Bounded Waiting
            - Process가 Critical Section에 진입할 때까지 걸리는 시간에 Limit이 존재해야 함
    - 상호 배제가 가장 필수적인, 기초적인 조건
    - 진행은 기다리고 있는 프로세스가 여러 개 있으면 어떤 프로세스가 진입할 지 정해줘야한다.
        - A가 빠져나오면, A가 아닌 BCD중 하나가 무조건 들어가야한다.
    - Bounded Waiting는 A가 빠져나오고 D가 들어가고, D가 빠져나오고 A가 들어가서 B,C가 못 들어가는 상황을 방지
- 가장 중요한 Data Consistency는 Mutual Exclusion만으로도 가능하지만 프로그램이 끝까지 정상적으로 진행되기 위해서는 Progress, Bounded Waiting이 필요
## 두 Process를 위한 Algorithm
- Turn
    - Shared Variables
        - int turn = 0;으로 초기화
        - turn = 0 일때,
    - Process p0
    ```
    while(turn != 0)
        critical Section
    turn = 1;
        remainder section
    ```
    - Process p1
    ```
    while(trun!=1)
        critical section
    trun = 0;
        remainder section
    ```
    - 만족 조건 : Mutual Exclusion
    - 불만족 조건 : Progress, Bounded Waiting
        - 두 Process수행의 순서가 정해진 대로 안 되면 진행 불가능
        - ex. p1, p1, p1 이렇게 실행 -> turn이 0이 되어서 실행 불가
        - -> turn이라는 변수를 2개로 쪼개보자!
- Flag
    - Shared Variables
        - boolean flag[2]; flag[0] = flag[1] = false로 초기화
        - flag[0] = true일 때, P0이 Critical Section에 진입 가능
        - flag[1] = true일 때, P1이 Critical Section에 진입 가능
    - Process P0
    ```
    flag[0] = true;
    while(flag[1]);
        critical section
    flag[0] = false;
        remainder section;
    ```
    - Process P1
    ```
    flag[1] = true;
    while(flag[0]);
        critical section
    flag[1]=false;
        remainder section
    ```
    - 진입 가능 여부를 bool값으로 처리하는 방법
    - 만족 조건 : Mutual Exclusion
    - 불만족 조건 : Progress, Bounded Waiting
        - 두 Process가 동시에 flag[]를 true로 할 수 있음
        - ex. 초기에 둘 다 true라서 context switiching이 일어나면 둘다 critical section에 진입하게 된다.
        - -> Flag와 Turn 둘 다 쓰자!
- Peterson Solution
    - Shared Variables
        - int turn;
        - boolean flag[2]; flag[0]=flag[1]=false로 초기화
    - Process P0
    ```
    flag[0] = true;
    turn =1;
    while(flag[1] && (turn==1));
        critical seciton
    flag[0]= false;
        remainder section
    ```
    - Process P1
    ```
    flag[1] = true;
    turn = 0;
    while(flag[0] && (turn==0));
        critical section
    flag[1] = false;
        remainder section
    ```
    - 만족 조건 : Mutual Exclusion, Progress, Bounded Waiting
        - 두 Process가 동시에 수행되더라도, turn값에 의하여 결정됨
    - Process P0에서 flag[0]=true인 이유는 상대가 먼저 들어갈 수 있도록 양보한 것
        - 하지만 critical section으로 들어가면 그것을 막아버림
    - Peterson Solution의 한계
        - 확장은 가능한가?
            - 이렇게 하면 2개의 프로세스는 되는데, 3개 이상의 프로세스는 어떻게 할 것인가?
        - 확장된 Algorithm의 증명은 어떻게 할 수 있나?
            - 어떤 경우에도 동작함을 보여야 함
        - 일반적으로 이러한 증명은 NP 문제임
            - 증명에 되더라도 매우 복잡함
        - 하드웨어로 처리하면 알고리즘이 매우 간단하게 됨
            - Acquire Lock -critical Section-> Release Lock -Remainder Section->
    - Flag를 동시에 사용하는 문제 때문에 변수를 계속 추가해줘야 했음.. 어케할까?
        - 운영체제상에서, 어떠한 순간에 프로세스에 사용되고 있는 명령어는 단 하나.
        - Flag를 하드웨어적으로 처리를 하자
        - Lock을 잡는 것, 푸는 것을 하드웨어적으로 처리
    - 간단하지만 바람직하지 않은 해결방법
        - Critical Sectin에 들어가면서 Interrupt를 Disable함
        - User Program이 Interrupt를 Control하는 것은 바람직하지 않음
        - Scalable 하지 않음
            - Process의 숫자가 많아 질 때 문제가 생길 소지
        - -> 동기화를 위한 Instruction(명령어)을 도입하자
## Synchronization Instruction
- CPU에서 지원하여 원자적(Atomatically)으로 수행되는 명령어(Instruction)을 이용
    - 원자적이란? 명령어가 수행되는 동안 방해받지 않음 (=Uninterruptible)
- Test and Set 명령어
    - Shared Variables
        - boolean lock = false;
    ```
    boolean TestAndSet(boolean *target){
        boolean rv = *target;
        *target=  true;
        return rv;
    }
    ```
    - 이 TestAndSet이 실행되는 동안 다른 프로세스가 동시에 접근이 불가하도록 보장
    - Process pi
    ```
    do{
        while(TestAndSet(&lock));
            critical Section
        lock =false;
            remainder section
    }
    ```
    - lock을 true로 바꿔주는 것이 Critical Section에 진입했다는 것을 알림
    - Lock은 한 프로세스만 사용이 가능하다는 것이 보장됨
    - 어찌됐건 TestAndSet을 거치면 lock이 true임
    - 대신 하나의 프로세스만 TestAndSet이 실행될 수 있음
- Swap 명령어
    - Shared Variables
        - boolean lock - false;
        - boolean waiting[n];
    - Process Pi
    ```
    do{
        waiting[i] = true;
        while(waiting[i]==true){
            swap(&lock, &waiting[i]);
                critical section
            lock = false;
                remainder section
        }
    }
    ```
    - Progress와 Boudned Weight까지 보장을 해주려면 Waiting[n]이런 array가 필요하겠구나
    - pi가 오면 기다리고 있다는 것을 알려주기 위해 waiting[i] = true로 전환
    - 만약 lock이 false(아무도 안 쓰고 있음)면 lock이 true로, waiting이 false가 되고, Lock이 true(누군가 쓰고 있음)면 lock이 false로, waiting이 true가 되어 while이 계속 반복됨
- 위와 같은 Instruction의 한계
    - 동기화 Instruction을 쓰면 Mutual Exclusion은 해결이 되지만 Bounded Waiting같은 조건은 User Program에서 제공해야 한다.
    - Bounded Waiting이 주어진 문제마다 조금씩 차이가 있기 때문에 User Program에서 제대로 처리하는 것을 기대하기 어려움
    - 좀 더 Comprehensive한 동기화 Primitive가 필요함
    - Counting을 해주는 것은 어찌됐건 User Program에서 해줘야 함
    - fair하게 처리해야 할 지, Prioirty에 따라 처리해야 할 지에 따라서 Bounded Waiting에 차이가 있음
        - -> User Program에서 공정하게 처리하리라 기대하기 어려움
## 세마포어(Semaphores)
- 세마포어 : 두 개의 원자적 연산을 가지는 정수 변수
    - 원자적 연산
        - Wait() 또는 P()
        - Signal() 또는 V()
    - 이 변수는 2개의 원자적인 연산(Atomic Operation)에 의해서만 접근됨
- P는 Critical Section 들어가기 전에, V는 나와서 수행함
- P와 V연산은 독립적으로, 그리고 원자적으로 수행됨
    - 하나의 Process가 P를 수행하여 세마포어의 값을 수정하는 동안, 다른 Process에서 P나 V를 수행하여 같은 세마포어의 값을 수정하지 못함
- Wait, P()는 Lock을 잡는 것
- Siganl, V()는 할 일 끝냈다고 신호를 보내는 것
- 서로 다른 Process의 Critical Section에 진입하는 순서도 중요하지만 ,그걸 위한 Lock변수에 동시에 접근하지 못하게 하는 것도 중요하다!
- ex.   
    ```
    P();
    Critical Section
    V();
    Remainder
    ```
    - Lock을 잡고 푸는 과정을 이제는 P(), V()라는 내부에 뭔가 더 추가된 함수로 처리
- 구현
    - Busy Waiting
        - Busy Waiting 이용(Original)
        ```
        -P(S)
            while (S<=0) loop;
            S=S-1;
        -V(S)
            S=S+1;
        ```
        - 세마포어의 값 -1,-2,-3 이런 것이 순서를 대변
        - Busy Waiting은 Critical Section에 진입할 조건이 될 때까지 Loop를 돌며 기다린다.
            - 단점
                - 세마포어가 1이 될 때까지 기다림
                - CPU Cycle을 낭비할 수 있음
                - 대기 중인 Process 중에서 누가 Critical Section에 진입할 지 결정하지 않음
    - Sleep Queue
        - Busy Waiting 방식의 CPU Cycle을 낭비하는 문제를 해결
        - Semaphore의 자료구조에 Sleep Queue를 추가하여, 대기중인 Process를 관리
            - Semaphore의 값이 양수가 되어 Critical Section에 진입이 가능하게 되면, Sleep Queue에서 대기 중인 Process를 깨워 실행시킴
        - Semaphore의 자료구조
        ```
        typedef struct{
                int value;
                struct process *list;
        }semaphore;
        - P(semaphore *S){
        S->value--;
            if(S->value<0){
                add this process to S->list;
                block();
            }
        }
        - V(semaphore *S){
            S->value++;
            if(S->value<=0){
                remove a process P from S->list;
                wakeUp(P);
            }
        }
        ```
        - 기다려야 한다면 일단 sleep queue에 삽입
        - 만약 다 끝내고 V가 실행되어 Semaphore를 ++해줬는데 값이 0보다 작거나 같으면 기다리고 있는 Process들이 있다는 것을 알 수 있다.
## Semaphore의 종류
- 2가지의 Semaphore
    - Counting Semaphore
        - Semaphore값은 범위가 정해져 있지 않음
        - 초기 값은 가능한 자원의 수로 정해짐
        - 관리하기 어려움
    - Binary Semaphore
        - Semaphore valuer가 가질 수 있는 값은 0과 1
        - Counting Semaphore보다 구현이 간단함
        - 원시적인 방법(test-and-set 과 비슷)
    - Binary Semaphore를 이용하여 Counting Semaphore를 구현할 수 있음
    - Binary Semaphore는 test-and-set과 같은 Hardware의 도움을 받아서 구현할 수 있음
 - Binary Semaphore의 구현
    - Test and Set 명령어를 이용하여 Binary Semaphore를 구현
    - Semaphore S : 현재 Critical Section에 진입한 Process가 있는지 나타냄(true or false)
    - P(S)
        - while(test_and_set(&S));
        - S의 값이 return되고, S는 true로 바뀜
    - V(S)
        - S = false;
        - 진입한 Process가 없음을 나타내어 Wait()에서 대기 중인 Process를 진입 가능하도록 함
- Counting Semaphore의 구현
    - Counting Semaphore를 CS라 하고, Counting Semaphore의 value는 C라 하자
    - 2개의 Binary Semaphore S1, S2를 이용
    - S1= 0, S2=  0으로 초기화(C가 양수라고 가정)
    ```
    - Wait Operation
    P(S1);
    if(C<0){
        V(S1);
        P(S2);
    }else
        V(S1);
    - Signal Operation
    P(S1);
    C++;
    if(C<=0){
        V(S2);
    }
    V(S1);
    ```
    - C가 lock을 잡기 위한 변수임
    - C를 하나의 프로세스만 처리하도록 만들기 위한 Semaphore 하나를 만들어주고(S1) Critical Section에 진입하는 것을 하나만 가능하도록 만들기 위한 S2를 만들어준다.
    - P(S1)은 C에 하나만 접근할 수 있도록 하기 위한 것이기에 누군가가 C--를 실행시키면 다른 것들이 C에 접근할 수 없게 된다.
    - P1과 P2가 온다 했을 때, P1은 C를 0으로 만든 후에 S1을 풀고 나감
    - P2가 오면 C를 -1로 만들고, 누군가가 있다는 것을 인지한 후에 S1을 풀고, P(S2)를 실행하여 누군가가 S2를 풀어주기를 기다리게 된다.
    - 빠져나올때는 P1이 P(S1)으로 C를 잡아줌(C를 풀어줬기에 C에 변경이 들어갔을 수 있음)
    - C를 ++해주고, C가 0보다 작거나 같으면 누군가가 대기하고 있다는 것을 뜻함. 이럴때는 내가 끝냈으니 S2를 풀어준다.
    - 만약 C가 1이면 아무도 대기하고 있지 않으니 그냥 S2를 풀어줄 필요가 없음
- 프로세스 내에 Thread가 여러 개 있으면??
    - Semaphore의 구현
        - Kernel이 Single Thread인 경우
            - P/V를 System Call로
            - Kernel 내에서 처리하여 Semaphore 동작을 구현함
            - Kernel 내의 수행이 Non Preemptive이므로, Kernel에 들어간 것이 Critical Section에 들어간 것임
        - Kernel이 Multithread인 경우
            - P/V를 System Call로
            - Kernel내에서 별도로 동기화를 해야 함
        - Kernel내에서 처리하면 굳이 하드웨어를 쓰지 않아도 하나의 명령어만 실행되는 것이 보장됨 (NonPreemptive-끼어들지 못함)
        - 멀티쓰레드이면, Kernel내에서 별도로 동기화를 해줘야함 -> Test and Set, Semaphore 등등 사용
    - Semaphore의 단점
        - Deadlock이 발생할 가능성이 존재함
        - P와 V의 연산이 분리되어 있기 때문에 이를 잘못 사용할 경우에 대한 대책이 없음
        - P(); -> Ciritical Section -> P();
            - Critical Section후에 Lock을 풀어주는 V();가 없으므로 한 Process가 Critical Section에 진입하면, 나올 수 없음
            - 다른 Process들이 Critical Section에 진입 못하므로 Deadlock이 발생
        - V(); -> Critical Section -> P();
            - Critical Section 전에 Lock을 걸어주는 P();가 없으므로 여러 Process가 동시에 Critical Section에 진입 할 수 있으므로, Mutual Exclusion을 보장 못 함
        - High-level 언어에서 동기화를 제공하는 방법이 필요해짐
## Deadlock
- 두 개 이상의 Process들이 끝없이 이벤트를 기다리고 있는 상황
- 그 이벤트는 기다리고 있는 Process만이 발생 시킬 수 있는 것
```
-P0
P(S);
P(Q);
...
V(S);
V(Q);
-p1
P(Q);
P(S);
...
V(Q);
V(S);
```
P0가 S를 잡고 P1이 Q를 잡으면, P0가 Q를 잡아야 하는 상황에서 P1은 S를 잡아야 하는 상태에 있음 -> 서로가 서로의 Lock을 잡고 있음
## Monitor
- High-level언어에서의 동기화 방법
    - Java의 Thread에서 동기화를 위한 방법으로 Monitor가 사용됨
- 한 순간에 하나의 Process만 Monitor에서 활동하도록 보장
- Application은 Semaphore와 같이 P와 V연산에 대한 고려 없이 Procedure를 호출하는 것 만으로 동기화를 해결할 수 있음
    - Programmer는 동기화 제약 조건(P와 V연산 같은 것)을 명시적으로 코드화할 필요가 있음
- Monitor 문법
    - Java나 C++의 클래스의 구문과 유사
    ```
    Monitor monitor-name{
        shared variable 선언
        ...
        procedure body p1(...){...}
        procedure body p2(...){...}
        procedure body p3(...){...}
        {
            초기화 코드
        }
    }
    ```
- entry queue에서 대기하고 있는 Process들은 Monitor를 사용하기 위해 기다리고 있음
- shared data를 사용하기 위해서는 monitor에 진입하여 제공되는 operation을 통해야 함
- ex. Transaction in Database
    - Transaction
        - 데이터 베이스 내에 하나의 그룹으로 처리해야 하는 명령문들을 모아놓은 작업 단위
        - Transaction 내에 묶인 하나의 작업 단위가 반드시 완전 수행
            - 만약 어느 하나라도 실패한다면 전체 명령문이 취소 됨
- 그러면 그냥 highlevel에서 하는게 제일 좋은 것 아닌가?
    - 그렇지는 않은 것이, IPC같은 것은 아예 다른 프로세스 간에서도 통신이 필요할 수 있음
