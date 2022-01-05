# 운영체제 #10
## 동기화의 고전 문제 3가지
- Bounded-Buffer Problem
- Readers and Writers Problem
    - Solution 1
- Dining Philosohpers Problem
    - Solution 1
    - Solution 2
- 한정적인 컴퓨터 자원을 접근하고자 하는 많은 프로세스에 어떻게 할당할 것인가?
## Bounded-Buffer Problem
- 오버헤드를 줄이기 위해서 버퍼를 많이 사용하지만, Capacity를 사용하기에 한정됨
- N개의 Item을 삽입할 수 있는 Buffer에 여러 생산자와 여러 소비자가 접근
    - int array[32] 어떤 프로세스는 이것을 쓰고, 어떤 프로세스는 이것을 읽음
    - 여러 생산자가 Item을 만들어서 Buffer에 저장, 여러 소비자가 Buffer에서 Item을 읽음
- 생산자 - 하나의 Item을 생산해 Buffer에 저장
    - Race Condition : 공유 데이터에 대해 여러 Process가 동시에 접근, 변경을 시도하는 상황
- 소비자 - Buffer에서 하나의 Item을 가져옴
    - 동작 조건 : Buffer의 상태가 Empty면 대기
- 여기서 중요한 것은, 버퍼가 제한되어있다는 것. -> 동기화 필요
- 여러 생산자, 소비자 중 자신이 버퍼(Critical Section)에 접근하여 생산, 소비할 수 있는가?
     - 생산자가 Buffer에 저장하는 동안에는 Consumer, 나머지 Producer가 사용할 수 없게 해야한다.
     - 왜냐하면 생산자가 제대로 저장하고 나서야 소비자가 정확한 겂을 사용 가능하기 때문
- 구현
    - Buffer의 구현
         - 1차원 배열로 구현
         - boolean buffer[n];으로 선언
         - 초기화
            - buffer[0...n-1] = empty;
    - 생산자 Operation
        - Buffer 배열 중, empty인 index를 찾아 full로 바꿈
        - Buffer[m]= full;
    - 소비자 Operation
        - Buffer 배열 중, full인 index를 찾아 empty로 바꿈
        - Buffer[m] = empty
- 세마포어
    - 문제 해결을 위한 세마포어
        - Empty : Buffer 내에 저장할 공간이 있음을 표시
            - 생산자의 진입을 관리
        - Full : Buffer 내에 소비할 아이템이 있음을 표시
            - 소비자의 진입을 관리
        - Mutex : Buffer에 대한 접근을 관리
            - 생산자, 소비자가 empty, full 세마포어를 진입한 경우, buffer의 상태 값을 변경하기 위한 세마포어
    - 세마포어 Value의 초기값
        - Full = 0
        - Empty = n // buffer에 empty인 entry가 n개
        - Mutex = 1
    - 총 3개의 세마포어
        - buffer 내에 저장할 공간이 없으면 대기
        - 소비자는 아이템이 있는 경우에만 사용 가능, 없으면 대기
        - 하나에 하나의 buffer에만 접근할 수 있도록 mutex사용
- 생산자 Process
    ```
    do{
        ...
        produce an item in nextp;
        ...
        P(empty);//버퍼에 적어도 하나의 공간이 생기기를 기다림
        P(mutex);//critical section에 진입하기 위해 기다림
        ...
        add nextp to buffer
        ...
        V(mutex);//critical section에서 빠져 나왔음을 알림
        V(full);//버퍼에 아이템이 있음을 알림
    }while(1);
    ```
    - P(empty)가 empty n-1이 되었을 때 진행
    - 한 번에 하나의 프로세스만 돌도록 mutex를 잡아준다.
    - mutex값을 1로 바꿔주며 다른 애들이 들어올 수 있도록 함
    - full은 0에서 1로 변함
    - 주의해야 할 점은, full이 변했어도 empty는 변하지 않음. 계속 사용되고있기 때문
        - empty : n-1, full : 1, mutex : 1
    - full, empty를 재조정하는 것은 소비자가 한다
    - full을 1에서 0으로 전환하며 진입, mutex도 1을 0으로 전환하며 진입
    - n-1은 n으로 바꿔주고, mutex는 1로 바꿔줌
- 소비자 Process
    ```
    do{
        P(full);    //버퍼에 적어도 하나의 아이템이 들어가리르 기다림
        P(mutex);
        remove an item from buffer to nextc
        ...
        V(mutex);
        V(empty);   //버퍼에 하나의 빈 공간이 생겼음을 알림
        ...
        consume the item in nextc
        ...
    }while(1);
    ```
## Readers-Writers Problem
- 여러 Readers와 Writers가 하나의 공유 데이터를 읽거나 쓰기 위해 접근
- Readers - 공유 데이터를 읽음
    - 여러 Reader는 동시에 Data를 읽을 수 있음
- Writers - 공유 데이터에 씀
    - Writer가 데이터를 수정하기 위해서는, Reader 혹은 다른 Writer가 작업을 하고 있지 않아야 함
- 생산자, 소비자와 비슷해보이긴 하지만 다름
- Reader는 말 그대로 읽기만 하고 꺼내지 않음(동시에 Data를 읽을 수 있음)
- Writer는 공유 데이터를 씀(다른 Reader나 Writer가 작업을 하고있지 않아야 함)
- Solution 1
    - 문제 해결을 위한 자료구조와 세마포어
        - Int ReadCount : 버퍼에 현재 몇 개의 Reader가 접근 중인지 표시
        - Semaphore Wrt : Writers 사이의 동기화 관리
        - Semaphore Mutex : Readcount와 wrt에의 접근이 원자적으로 수행됨을 보장
    - 초기값
        - Mutex = 1, wrt= 1, readcount =0
    - Int Readcound, Semaphore, wrt 자체도 원자적으로 하나의 프로세스만 사용하고있다고 보장할 수 없음 -> Semaphore mutex라는 것을 사용해서 ReadCount와 Semaphore wrt를 원자적으로 수행되도록 보장
    - Writer
        ```
        P(wrt); //entry section
        ...
        writing is performed
        ...
        V(wrt); //exit section
        ```
        - writer는 사실상 별 게 없고, 모두 Reader에서 처리를 해줌
    - Reader
        ```
        P(mutex);
        readcound++;
        if(readcount==1)
            p(wrt); //어떤 writer도 수행되고 있지 않음을 판별
        V(mutex);
        reading is performed
        P(mutex);
        readcount--;
        if(readcound==0)
            V(wrt);
        V(mutex);
        ```
        - readcount는 reader에서만 접근이 가능
        - mutext lock을 잡고(1->0), readcount를 1로 증가시킴(0->1), readcount가 1이면 처음 들어온 reader이기 때문에 다음 단계로 진행. wrt가 만약 0이라면 누가 쓰고 있는 것이라 기다려야한다. 지금은 1이라고 가정하고, 1을 0으로 변환하고 진입. 내가 reading하는 도중에 다른 reader들이 들어올수도 있으므로 mutex는 풀어줌. 할 일을 다 했을 때는 mutex를 잡고, readcount를 감소시키고, readcount가 0이면(내가 마지막으로 read한 것이라면)writer도 들어올 수 있도록 wrt를 풀어준다. 그리고 마지막으로 mutex를 풀어준다.
    - 문제점
        - writer의 starvation
            - readcount == 0 일때만 V(wrt)가 수행되어 P(wrt)로 대기하고 있던 writer가 수행할 수 있음
            - 첫 번째 Reader(Readcount==1)가 P(wrt)만 통과하면, 다른 Reader들은 P(mutex)에 대한 P(mutex)만 기다리면 언제든지 수행할 수 있기 때문에 writer와 상관없이 진입할 수 있음
            - 여러 reader들이 계속해서 진입할 경우, readcount는 0까지 떨어지지 않을 수 있음
        - Writer의 Starvation을 예방하는 Solution이 존재함
            - -> 시간마다 priority를 증가시키기!
## Dining-Philosophers Problem
- 고전적인 Concurrency Method
- 5명의 철학자가 한 원형 식탁에서 함께 식사를 하는 상황
- 젓가락이 5개 뿐
    - 자신의 바로 옆 젓가락만 집을 수 있음
    - 두 젓가락을 모두 집어야 식사를 할 수 있음
    - 식사를 하고 난 다음에야 두 젓가락을 모두 내려놓을 수 있음
- Deadlock과 Starvation이 발생하는 경우
    - 모두 자신의 오른쪽 젓가락을 집었을 경우
- 철학자가 process, 젓가락은 한정된 공유 자원
- solution 1
    - 단순히 젓가락을 집는 것에 대한 동기화를 부여하는 방법
        - 모든 철학자가 자신의 왼쪽 또는 오른쪽 젓가락부터 집도록 한다.
        - boolean waiting[n];
    - 세마포어
        - chopstic[5] : 각각의 젓가락에 대한 동기화 관리
    - 초기값은 모두 1
    - 철학자 process
    ```
    do{
        ...
        think
        ...
        P(chopstick[i])
        P(chopstick[(i+1)%5])
        ...
        eat
        ...
        V(chopstick[i])
        V(chopstick[(i+1)%5])
    }while(1);
    ```
    - 동시에 chopstick을 잡으면 deadlock발생...
- deadlock 해결방안
    - 한 번에 최대 4명의 철학자만 식탁에 앉도록 한다.
    - 젓가락의 상태를 미리 검사하여, 양 쪽의 젓가락이 모두 사용 가능할 때만 젓가락을 집도록 한다.
    - 철학자에게 번호를 부여하여 홀수인 철학자는 왼쪽의 젓가락을, 짝수인 철학자는 오른쪽의 젓가락을 먼저 집도록 한다.
    - 위의 해결방안들은 Starvation까지 해결해주지는 못한다
        - 각각의 방안에 대해 Starvation에 대한 고려를 추가할 수 있음
            - ex. 한 차례 굶은 철학자에게 우선궈을 줌
        - 결국 priority가 필요하겠구나(굶은 사람에게 우선권)
- Solution 2
    - 양 쪽 젓가락을 한꺼번에 집는 방법
        - 젓가락의 상태를 미리 검사하여 양 쪽의 젓가락이 모두 사용 가능할 때만 젓가락을 집도록 하는 방법
    - 사용되는 자료구조
        - state[5] : 각 철학자의 상태를 기록(THINKING, HUNGRY, EATING)
    - 문제 해결을 위한 세마포어
        - mutex : 젓가락을 집거나 놓는 수행을 Critical Section으로 관리하기 위한 세마포어
            - 초기값 : 1
        - self[5] : 철학자 각각이 젓가락 두 개를 잡기를 기다리는 세마포어
            - 초기값 : 모든 원소가 0
            - Self[i] : 의미는 철학자 i가 HUNGRY 상태이더라도, 다른 젓가락 하나를 사용할 수 없을 경우 Waiting을 하기 위한 세마포어
    ```
     - 철학자 Process
    do{
        ...
        Think
        ...
        take_chopsticks(i);
        ...
        eat
        ...
        put_chopsticks(i)
        ...
    }while(1);

    - take_chopsticks(int i){
        P(mutex);
        state[i] = HUNGRY;
        test(i);
        V(mutex);
        P(self[i]);
    }
    - put_chopsticks(int i){
        P(mutex);
        state[i] = THINKING;
        test(LEFT);
        test(RIGHT);
        V(mutex);
    }

    - test(int i){
        if(state[i]==HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
            state[i] = EATING;
            V(self[i]);
        }
    }
    ```
    - 한 번에 2개의 젓가락을 가져오고 놓음
    - take_chopsticks : mutex를 통해 진입하여 test(i)를 통해 양쪽의 철학자 상태를 검사한 후, 자신이 먹을 차례를 기다린다.
    - put_chopsticks : mutex를 통해 진입하여, test(LEFT), test(RIGHT)를 통해 양쪽의 철학자 상태를 검사한 후, 먹을 차례를 기다리는 철학자에게 signal을 보내준다. -> test(i)에서 수행
    - Test를 수행한 철학자(i)가 HUNGRY 상태이고, 양쪽의 철학자가 모두 젓가락을 집지 않은 상태 (NOT EATING)이면 take_chopsticks()에서 wait했던 자신의 세마포어 self[i]에 signal을 보내어 EAT으로 진행하도록 함
    - 이때 V를 사용해서 0값을 미리 1로 올려줌(먹고있다는 lock의 의미)
    - 이때는 오히려 V가 lock을 잡는 것으로 쓰임. 그 후에 P(self[i])으로 0으로 바꿔주면서 빠져나오게 됨
    - V를 쓰는 이유는 self[i]를 0으로 초기화했는데, 철학자가 먹을 수 있는 상태를 1이라고 정했기 때문에 V로 값을 키워주고, 먹고나서 P로 self[i]를 0으로 했어야 함
    - 해설
        - solution 2의 전략은 철학자 좌우 젓가락이 사용 가능할 때만 Critical Section에 진입함
             - i번째 철학자가 식사를 하기 위해서는 i-1 (LEFT)와 i+1 (RIGHT) 철학자가 EATING 상태가 아니어야 함
        - take_chopstick()과 put_chopstick()의 동작을 살펴 보자
    - take_chopstick()
        - test() 함수 ㅇ나에서 검사하는 LEFT와 RIGHT의 상태가 EATING이 아니어야 함
        - test()를 만족하면, signal(self[i])에 의해 self[i]의 값은 1이 되므로, wait(self[i])에서 block되지 않고 식사를 진행한다.
            - self[i]의 초기 값은 0임
    - put_chopstick()
        - 이 때, 철학자 L과 R은 i에 의해 test_chopstick()에서 wait()함수에 의해 대기 중
        - 철학자 i에 의해 실행한 test(LEFT)
            - i와 LL의 상태를 확인
        - 철학자 i에 의해 실행한 test(RIGHT)
            - i와 RR의 상태를 확인
        - 철학자 i가 식사중인 동안 LL 혹은 RR 철학자의 상태가 EATING으로 바뀐다 하더라도, tes(LEFT)와 test(RIGHT)를 통해 signal을 수행하므로 동기화에 문제가 없다.
## 체크요소들
- Data Consistency가 확보되는지
- Deadlock이 발생하는지
- Starvation 가능성이 있는지
- Concurrency를 얼마나 제공하는지