# 운영체제 #12
## 가상 메모리
- 멀티프로그래밍 때문에 여러가지 프로그램을 메모리에 올리려다보니까 가상 메모리가 필요
- 메모리에 이미 누군가가 있다면, 누구를 쫓아낼 것인가?
## Page Replacement
- Memory 과다 할당 상태(Over Allocation Memory)
    - Multi Programming System에서 Memory 내에 위치한 User Process의 수가 증가함에 따라 발생
    - 모든 User Process가 사용하는 Page 수보다 물리 Memory의 Frame 수가 적은 상황
- 해결 방법
    - Page Fault 처리에 Page Replacement를 추가
- What is page replacement?
    - 물리 Memory에 위치한 Page를 Disk에 저장하고, 요구된 Page가 해당 Frame을 할당 받도록 하는 방법
- ex. A3이 스토리지에 있는데, A3가 필요해서 가져오라 했더니 메모리에 공간이 없음. A3를 가져오기 위해서 누구를 쫓아낼 것인가?
    - 단순히 page fault만 할 것이 아니라 page replacement가 필요하다.
## page fault with page replacement
1. 디스크에서 요구된 page의 위치를 찾는다.
2. 물리 Memory에서 Free Frame을 찾는다.
    - Free Frame이 있다면 사용한다.
    - 없다면, Page Replcaement Algorithm을 사용하여 교체할 Frame(Victim Frame)을 선택한다.
    - 교체할 Frame을 Disk에 저장하고, Page Table을 변경한다.
3. 요구된 Page를 2에서 선택된 Free Frame으로 읽어 들이고, 해당 Page Table을 적절하게 변견한다.
4. User Process를 재시작한다.
## Basic Page Replacement
- 특정 알고리즘으로 쫓아낼 victim선택
- storage로 백업(swap out)
- v(valid)를 i(invalid)로 바꿈
- storage에서 원하는 것을 가져옴
- i를 v로 바꿈
## Page Replacement 고려 사항
- 각각의 User Process에게 어떻게 Frame을 분배해 줄 것인가?
    - Frame Allocation Algorithm
- Page 교체가 필요할 때 어떻게 교체할 Page를 고를 것인가?
    - Page Replacement Algorithm
- 위 Algorithm들은 모두 Page 교체에 의한 I/O 작업 수행 횟수를 최대한 줄이려는 목적을 갖고 있으며, 적합한 Algorithm의 사용은 System의 성능을 크게 좌우하는 요소임
    - I/O 작업은 매우 큰 비용을 사용하기 때문
## Page Replacement Algorithms
- 어떤 Page Replacement Algorithm을 사용할 것인가?
    - 가장 낮은 Page Fault 발생 빈도를 가진 Algorithm
    - 즉, 가장 낮은 I/O작업 횟수를 요구하는 Algorithm
- 여러 Algorithm들을 비교하기 위해 아래 환경을 가정
    - 세 개의 Frame이 할당됨
        - Page Fault 발생 빈도는 Frame의 개수와 반비례함
    - Page를 참조한느 순서 - 20번
        - 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 7, 0, 1
    - 한번 참조된 Page는 Page 교체가 일어나기 전에는 물리 Memory에 위치한다.
        - 다시 참조할 때 물리 Memory에 Page가 존재하는 경우에는 Page Fault가 발생하지 않음
- Optimal Algorithm
    - 앞으로 가장 오랫동안 사용되지 않을 Page부터 먼저 교체함
        - 모든 Algorithm 중 가장 낮은 Page Fault 발생 빈도를 가지는 이론상 최적의 Algorithm
        - 앞으로 어떤 Page가 사용될지를 미리 알 수 없다.
        - 실제 구현 불가능
    - 7/x/x -> 7/0/x -> 7/0/1 -> 2/0/1 -> 2/0/3 -> 2/4/3 -> 2/0/3 -> 2/0/1 -> 7/0/1
    - page fault 발생 횟수 : 9번
- FIFO Algorithm
    - 먼저 frame이 할당된 page를 먼저 교체
        - 가장 단순한 Algorithm
        - FIFO Queue를 이용해 구현 가능
        - 멀티미디어 Data로 인해 주목 받음
    - 7/x/x -> 7/0/x -> 7/0/1 -> 2/0/1 -> 2/3/1 -> 2/3/0 -> 4/3/0 -> 4/2/0 -> 4/2/3 -> 0/2/3 -> 0/1/3 -> 0/1/2 -> 7/1/2 -> 7/0/2 -> 7/0/1
    - Page Fault 발생 횟수 : 15번
        - 굉장히 많은 page fault 발생 -> 일반적으로는 쓰지 않음
        - 미디어에서는 잘 사용되는데, 미디어는 이전의 것을 쓰지 않기 때문
- SCR Algorithm(Second Chance Replacement)
    - FIFO 기법의 단점을 보완하는 기법
    - 오랫동안 주 기억 장치에 존재하던 Page들 중에서 자주 사용되는 Page의 교체를 방지하기 위해 고안됨
    - FIFO Queue를 만들고 사용하되 참조 Bit를 두어 Page를 관리한다.
    - 참조 Bit(Reference Bit)
        - 최초로 Frame에 Load될 때와 Page가 참조되었을 때마다 1로 set
        - 일정 주기마다 다시 0으로 Reset된다.
    - 제거 대상으로 선택된 Page의 참조 bit가 1로 Setting된 경우, 최근에 사용된 Page이므로, 제거하는 대신 참조 Bit만 0으로 Reset
    - 일정 주기의 기준을 정하는 것이 매우 어려움 -> page의 수에 비례하지 않을까?
        - -> 원형 Queue로 만듦
- Clock Algorithm
    - SCR기법의 발전형
    - 환형 Queue를 사용하여 Frame을 관리
    - 다음에 제거될 Page를 가리키는 Hand라는 Pointer를 둔다.
    - Hand는 Queue를 따라 1칸씩 이동한다.
    - Hand가 가리키는 Page의 참조 Bit가 1이라면, 최근에 접근한 Page이므로 제거하는 대신 참조 bit만 0으로 Reset
    - 하지만 여전히 spatial locality, temporal locality를 완벽하게 해결하지는 못함
- LFU Algorithm
    - Least Frequently Used
    - 사용 빈도가 가장 적은 Page를 교체하는 기법
    - 지금까지 가장 적게 참조된 Page가 교체 대상으로 선택된다.
    - 7/x/x -> 7/0/x -> 7/0/1 -> 2/0/1 -> 2/0/3 -> 4/0/3
    - 문제 : 일단 Program 실행 초기에 많이 사용된 page는, 그 후로 사용되지 않더라도 Frame을 계속 차지하는 문제가 있음 -> starvation을 초래한다.
- NRU Algorithm
    - Not Recently Used
    - 최근에 사용하지 않은 Page를 교체하는 기법
    - Page마다 참조 Bit와 변형 Bit를 두어 관리
    - 참조 Bit(Reference Bit)
        - 최초로 Frame에 Load될 때와 Page가 참조되었을 때마다 1로 Set
        - 일정 주기마다 다시 0으로 Reset
    - 변형 Bit(Modified Bit)
        - 최초로 Frame에 Load될 때는 0
        - Page의 내용이 바뀔 때 1로 Set
    - Page 교체가 필요한 시점에 다음 순서대로 교체 대상으로 삼는다.
        - 참조 0, 변형 0 
        - 참조 1, 변형 0
        - 참조 0, 변형 1
        - 참조 1, 변형 1
    - 문제 : 여전히 Optimal 하지 않음..
- LRU Algorithm
    - Least Recently Used
    - 가장 오랜 시간 참조되지 않은 Page부터 먼저 교체
        - Page 사용의 지역성(Locality)를 고려하여 Optimal Algorithm과 유사하며 실제 구현 가능한 Algorithm
        - 구현 
            - Counter의 사용 : 참조된 시간을 기록
            - Queue의 사용 : 한 번 사용한 page를 Queue의 가장 위로 이동시킨다.
                - 가장 위의 Page : 가장 최근에 사용된 Page
                - 가장 아래의 Page : 가장 오래 전에 사용된 Page
    - 7/x/x -> 7/0/x -> 7/0/1 -> 2/0/1 -> 2/0/3 -> 4/0/3-> 4/0/2 -> 4/3/2 -> 0/3/2 -> 1/3/2 -> 1/0/2 -> 1/0/7
    - 최근에도 활발하게 사용중
    - 문제 : 프로세스 내부에서 page를 왔다갔다 하는 것이라 프로그램 전체적으로 보았을 때 임팩트가 별로 없음 -> 프로세스 중에서도 오랫동안 사용되지 않는 프로세스는 스토리지로 보내는 것이 좋지 않을까? -> Swapping
## Swapping
- Page Out으로 Memory 부족을 해결하지 못할 경우 필요한 기법
- Swap Out 대상이 된 Process 전체를 Secondary Storage로 보낸다.
- 이렇게 Page Out이나 Swapping에 사용되는 Secondary Storage(Backing Store)를 Swap 영역이라 한다.
## Contiguous Memory Allocation
- 각 프로세스를 어떻게 할당할까?
- Single Partition Allocation<1>
    - 가장 단순하게 Memory를 사용
    - User Program 영역을 한 번에 1개의 User Program만 사용하도록 한다.
- Multiple Partition Allocation<2>
    - <1>의 방법에 Multiprogramming 개념을 추가하여 user Program영역을 여러 개의 user Program이 사용하도록 한다.
- No Partition<3>
    - 각 Program이 필요에 따라 전체 User Program영역을 사용
    - 이 경우, Page/Swap Out시에 Garbage Collection이 필요하다
- 프로그램 안에를 보면 사용되고 있지 않은 부분이 있음 -> 만약 User Program 4를 할당하고 싶은데, 그 공간을 활용하면 할당할 수 있다. -> 파티션을 아예 나누어버리면 Program 4가 들어가지 못하고, 들어오게 하려면 누군가를 out해야 한다. -> I/O
- 페이지처럼 잘게 쪼개는 건 어떨까
- Garbage Collection이 필요한 것은 만약 어떤 한 부분을 지우면 그것과 관련된 다른 프로그램 조각들도 함께 제거가 되어야 하기 때문
## Memory Allocation Problem
- User Program이 Load될 때, 물리 Memory의 OS 영역을 제외한 User 영역에 배치됨
    - Protection, Relocation, 그리고 Swap 기법을 사용함
    - Program을 Memory에 Load할 때, Memory의 빈 공간 중 어디에 Program을 Load할 지에 대한 고려가 필요
- First-Fit
- Best-Fit
- Worst-Fit
## Fragmentation
- External Fragmentation
    - Program에게 할당 후 남은 Memory의 총 공간은 새로운 할당 요청에 충분하지만, 그 공간이 연속적이지 않아 사용할 수 없는 경우
        - Paging은 External Fragmentation을 해결하기 위한 방법
- Internal Fragmentation
    - 할당된 Memory의 크기가 요청된 Memory의 크기보다 조금 더 커서 할당에는 성공했짐나, 그 차이만큼의 영역을 사용할 수 없는 경우
    - Paging에서 Page Frame은 4kb로 고정되었지만, 요청한 물리 memory 영역이 3998B인 경우, 2B의 Internal Fragmentation이 발생하게 된다.
## Protection과 Relocation
- Protection
    - Contiguous Memory Allocation 방법을 사용할 때, OS의 Memory 영역과 User Program의 Memory 영역은 서로 구분되어야 한다.
    - 서로의 영역을 침범하지 못하도록 보호를 해야 한다.
- Relocation
    - User Program은 재배치 가능한 주소로 표현됨
    - 재배치 가능한 주소를 이용하여 Program이 어느 위치에 Load되더라도 쉽게 Code의 주소를 결정할 수 있어야 함
- Protection과 Relocation을 위한 Hardware의 지원
    - Limit Register와 Relocation Register를 이용하여 구현
- Limit Register : 참조가 허용되는 주소의 최대값
    - Limit Register의 값을 비교하여 참조하는 주소가 허용되는 영역인지를 판별
- Relocation Register : Program이 차지하는 주소 영역 중 첫 번째 주소
    - 재배치 가능한 주소를 통해서 실제 물리 Memory의 주소로 참조 가능하게 함
    
