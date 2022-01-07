# 운영체제 #13
## File System
- 디렉토리 : 폴더? - 파일의 정보를 담고 있는 자료구조
- File 정의 : array of bytes
    - 다른 정의 : a collection of related information
    - address space와의 비교
        |     | File  | Address Space   |  
        |:---: | :---: | :---: |  
        | 차이점 | Fixed length   | Variable length |  
        |  | Persistent   | Volatile |  
        |  | 비 연속적임   | 연속적임 |  
        | 공통점 | 프로세스간 공유 가능   |
    - 파일의 크기를 알 수 있고, 디스크에 저장되기에 영구적이다. 또한 비연속적임(잘게 쪼개서 메모리에 비연속적으로 위치하게 됨)
- File과 Physical Disk Block 간의 Mapping을 제공
    - Disk 위치 배치를 담당함
        - File Blocks -> Disk Blocks
    - 사용자는 File이 저장된 위치를 알 필요 없음(Independence)
- Disk에 들어가 있는 File 전체를 총칭
    - File System에 따라 File들의 배치나 구성이 달라질 수 있음
- 01로 구성된 byte 집합체를 실제 physical memory의 어디에서 찾을 수 있을지 찾게 해줌
- File System은 Mapping을 제공하는 것
- 사용자는 physical memory의 어디를 봐야 하는지 저장된 위치를 알 필요가 없음

| Field | Description |
|:---:|:---:|
|Name|사람이 읽을 수 있는 기호화된 이름
|Type|운영체제에서 지원하기 위한 정보(executable,text,library,archive,multimedia,etc.)
|Location|장치에 저장되어 있는 위치|
|Size|파일의 크기|
|Protection|파일에 대한 read,write,execution 허가 정보|
- 그 외 MetaData들
    - Time, Date, User Info, etc.
- File의 정보가 저장되는 곳
    - Directory Structure에 저장
- 디렉토리를 통상 "폴더"라고 생각하는데, 정확한 정의는 "File의 정보가 저장되는 곳"이다.


| Operation | Description |
|:---:|:---:|
|Create|파일을 저장하기 위한 새로운 공간을 장치에 할당한 후, 새로운 파일에 대한 entry 정보를 만듦
|Write|파일에 인자로 받은 내용을 기록
|Read|인자로 받은 메모리 공간에 파일의 내용을 읽어와 기록|
|File Seek|파일의 current-file-position 포인터를 특정 위치로 이동시킴|
|Delete|파일 삭제|
|Open|디스크의 directory structure를 탐색하여 메모리에 캐싱|
|Close|메모리에 캐싱된 directory structure를 디스크로 저장|

- Current-File-Position Pointer란?
    - File을 읽거나 쓸 때마다 자동으로 업데이트 되는 Pointer로 File에 대해 Process가 어디까지 작업을 했는지를 기록하는 Pointer
- File Seek은 현재 참조하고 있는 파일의 위치를 찾는다. 라고 생각하면 됨

## Open/Close Semantics
- 여러 Process가 File을 공유하는 경우
- 두 개의 Open File Table 유지
    - Per Process Table : 각 Process에서 유지하는 State를 가짐
        - ex. File Pointer
    - System-wide Table : Process Independent Information
        - ex. Access Date, File Location, Open Count
- Open은 Open Count를 하나 증가시키고, Close는 감소시킨다.
- Delete 동작은 System-wide Table에서 Open Count를 확인한 후 이루어짐
    - 파일을 지우려 할 때 이 파일은 어디에서 사용중이라 지울 수 없다고 하는 것은 Delete 동작에서 OpenCount를 확인한 것이다.
## File Access Method
- 순차 접근
    - File에 있는 정보에 대한 접근은 Record의 순서대로 이루어짐
    - Operation
        - Read Next
        - Write Next
        - Reset
    - 운영체제에서는 순차접근을 사용하지 않음
        - 만약 메모장에 무언가를 쓴느데, 수정을 하려면 처음부터 다시 써야 하기 때문
- 임의 접근
    - File의 어떠한 위치라도 바로 접근하여 Read나 Write를 수행
    - Operation
        - Read n
        - Write n
        - 인자로 받는 n은 읽고자 하는 File의 Block Number
    - 대부분의 OS가 Random File Access를 사용함
    - 프로세스가 page 단위로 관리되었던 것처럼 File도 Block으로 관리됨
        - 4kb이거나 그 이상
    
| Sequential Access | Implementation for direct access |
|:---:|:---:|
|reset|cp=0;
|read next|read cp; cp = cp+1;
|write next|write cp; cp = cp+1;

## File System 구성
- disk1 = partitionA(directory+files) + partitionB(directory+files)
- 디스크 하나를 파티션으로 나누어서 C드라이브, D드라이브 이렇게 쓰기도 함
- Swapping을 위한 공간을 남겨두어서 500GB 드라이브도 480정도 쓸 수 있게 된다.
- 리눅스에서는 두개의 디스크를 하나의 파티션으로 만들기도 한다. - mount
    - partitionC = directory + files == disk2 + disk3 

## File System이 계층화
- File System은 일반적으로 여러 개의 계층으로 나뉘어져 구성
    - application programs -> virtual file system -> file-organization module -> basic file system -> I/O control -> devices
- 계층으로 나누는 이유
    - File System을 구현하고자 하는 장치가 다양할 수 있음
    - 한 System에 1개 이상의 File System을 사용 가능하게 함
    - 계층화된 구성을 통해서 File System에 유연성(Flexibility)를 제공

## Mount
- Directory와 Device를 분리
- Mount의 의미
    - 비어 있는 Directory에 임의의 Device를 "붙일 수"있다.
    - File을 사용하기 위해 Open을 하듯, File System을 사용하려면 Mount를 해야 한다.
    - /home 위에 diskA /a/b/c Directory를 Mount 하면 /home/a/b/c가 됨
- Distributed FS로 확장이 용이(유연성 증가)

- #mount disk2 /usr/ (Disk2의 파일 시스템을 /usr/ 디렉토리에 마운트)
    - disk2 구조가 usr 하위로 부착된다.

## Directory Structure Concept
- 모든 File들에 대한 정보를 가지는 Node들의 집합
- Directory Structure와 File은 모두 Disk 상에 있음
- Single-level Directory : 모든 사용자에 대해서 하나의 단일한 Directory
    - 문제점 : 동일한 이름을 가진 파일을 만들 수 없다.
        - 사용자로 Directory를 분리하자!
- Two-level Directory : 사용자마다 Directory를 분리
    - 문제점 : 각 User 입장에서는 cat 하나만 사용이 가능하고, 새로운 cat은 못 가짐
- Tree-Structured Directories
    - 효율적인 탐색
    - Grouping 특성
    - 우리가 알고있는 파일 구조와 비슷해짐
    - Sub Directory를 만들어서 효율적인 탐색이 가능해짐
    - 문제점 : 파일 공유가 불가능
- Acyclic-Graph Directories
    - 둘 이상의 서로 다른 이름을 이용(Aliasing)하여, File이나 Sub Directory를 공유
    - Dangling Pointer가 생길 수 있음
        - ex. 만약 어떤 디렉토리가 삭제된다면, 그것을 가리키던 것들이 null을 참조하게 된다.
- General Graph Directory
    - Cycle이 없도록 보장하는 방법
        - Link를 File로만 가능하도록 한다.
        - 새로운 Link를 만들 때마다 Cycle Detection Algorithm을 사용하여 Cycle이 생기지 않는지 확인한다.
    - Acyclic은 사이클이 없고, 방향성이 있었음
    - General은 그래프를 사용하되, cycle이 없도록 보장하는 방법을 사용
    - Acylic과 General중 뭐가 더 좋을까?
        - General이 Cycle을 확인하는 overhead가 큼 -> Acyclic을 많이 사용함

## File 구현
- Disk Block
    - File의 구현에 앞서, Disk Block은 File System의 입출력 단위
- File 구현에서는 File의 내용을 담고 있는 Data Block의 위치 정보를 어떻게 저장할지를 고려해야 한다.
- 운영체제마다 각기 다른 방식으로 File의 Data Block 정보를 관리하고 있으며 보통 다음의 4가지로 볼 수 있다.
    - Contiguous Allocation
    - Linked list Allocation
    - Linked list Allocation using an index
    - I-nodes
- 파일 Data Block을 어떻게 관리할 것인가?

## Contiguous Allocation
- File을 물리적으로 연속된 Disk Block에 저장
    - Frame Allocation에서의 Contiguous Allocation과 유사
- 장점
    - 구현이 간단함
    - 물리적으로 연속된 공간에 있으므로, 전체 File을 한 번에 읽어 들일 경우 성능이 매우 뛰어남
- 단점
    - File은 반드시 한번에 끝까지 기록 되어야 함
    - 운영체제에서의 File의 끝에 예비용 Block을 남겨둘 경우, Disk의 공간을 낭비하게 됨
## Linked List Allocation
- Disk의 Block을 Linked List로 구현하여, File의 Data를 저장하도록 함
- 장점
    - File의 Data Block은 Disk의 어디든지 위치할 수 있음
    - 공간의 낭비가 없음(아예없지는 않음)
- 단점
    - 저장하고 있는 것이 start와 end밖에 없기에 Random Access가 불가능
        - File의 특정 위치를 찾기 위해서는 해당 File의 시작 Node부터 찾아가야 함
    - 다음 Data Block에 대한 Pointer로 인해, Data Block에서 Data를 저장하는 공간이 반드시 2의 배수가 아닐 수도 있음
        - 대부분의 Program은 Read/Write하는 Data의 크기가 2의 배수이기 때문에, 성능 측면에서 뒤쳐질 수 있음
    - disk block pointer의 크기를 결정하는 요소는? 번호가 많으면 많을수록 디스크 블록의 크기가 커짐
## Linked List Allocation using an index
- File의 Data에 관련된 Block을 하나의 Block에 모아 둠
    - File의 Data Block중 하나를 Index Block이라 하여, 모든 Data Block의 위치를 Index Block에서 알 수 있음
- Linked List Allocation 보다 개선된 점
    - Random Access 시, 하나의 Data Block(index Block)에서 찾아가고자 하는 Data Block의 위치를 알 수 있으므로, Linked List Allocation보다 빠르게 Random Access가능
- 단점
    - 최대 File의 크기가 고정 됨
        - Index Block의 크기가 고정되어 있기 때문에, Index Block에서 수용할 수 있는 Disk Block에 대한 Pointer의 수가 한정되어 있기 때문
## I-Nodes
- File에 대한 Data Block Index들을 Table 형태로 관리하는 방법
    - 큰 Memory 영역을 관리할 경우에 1-level Paging보다 Multi-level Paging이 유리한 것과 유사
- I-node의 구성 요소
    - File에 대한 속성을 나타내는 Field
    - 작은 크기의 File 위한 Direct Index
    - File의 크기가 커짐에 따라서 요구되는 Data Block의 Index들을 저장하기 위한 index Table들
        - Single Indirect Block
        - Double Indirect Block
        - Triple Indirect Block
- 작은 파일은 Linked List Allocation using index를 사용한다고 보면 된다.
    - 이것으로 감당이 안 될 경우, index table을 단계별로 확장
## Directory 구현
- Directory Entry
    - Directory를 표현하기 위한 자료구조
    - file System의 File구현에 따라 Directory Entry를 구성하는 Field도 달라짐
        - 일반적인 Directory Entry는 File의 이름, 속성과 같은 정보가 저장되지만, I-node를 사용하는 File System에서는 File Name과 I-node Number만이 저장됨
- 2가지 구현 방법
    - Directories in MS-DOS
        - File의 구현이 Linked List Allocation인 MS-DOS에서 사용하는 Directory Entry
        - Directory Entry의 First Block Number를 통해서 실제 File의 Data Block이 시작되는 Block을 알 수 있음
            - MS-DOS는 Linked List Allocation 방식이기 때문에, 맨 처음의 Data Block을 알면 전체 File의 Data를 알 수 있음
        - 이 경우에는 i-node를 사용하지 않음
    - Directories in UNIX
        - UNIX에서 Directory Entry는 File이름과 I-node Number로 이루어짐
            - MS-DOS와 달리 File의 Attribute, OwnerShip과 같은 정보는 해당 File의 I-Node 자료 구조에 있기 때문
## Protection
- 저장된 정보에 부적절한 접근을 막는 것
- Types of Access
    - Read
    - Write
    - Execute
    - Append
    - Delete
    - List : File의 속성이나 이름의 내용
## Access Lists and Groups
- 접근 모드 : Read, Write, Execute
- 세 가지 분류의 사용자들
    - a) owner access 7 => 111
    - b) group access 6 => 110
    - c) public access 1 => 001
- 관리자에게 고유의 이름을 가지는 Group G를 만들도록 요청하고, 그 그룹에 사용자들을 추가하게 한다.
- 특정한 File 또는 하위 Directory에 대해 적절한 접근을 정의한다.