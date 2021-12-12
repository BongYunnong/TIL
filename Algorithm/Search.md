Search
=================
<br>

Search Problem 1
--------------------
--------------------
- Determine whether the number x is in the list S of n numbers. The asnwer is yes if x is in S and no if it is not.
- n개의 숫자를 가진 리스트 S안에 숫자 x가 존재하는지 확인하는 문제

    - Input : List S, x, n
    - Output : S안에 x가 있다면 true, 없다면 false

- Instance
    - Input : S=[10,7,11,5,13,8] , x = 5
    - Output : yes

<br>
<br>

Search Problem 2
----------------------
----------------------
- Where is the key x in the array S of n keys?
- n개의 숫자를 가진 배열 S안에 숫자 x의 위치를 확인하는 문제
    - Input : List S, x, n
    - Output : S 안의 x의 위치 (S안에 없다면 -1)

- Instance
    - Input : S=[10,7,11,5,13,8] , x = 5
    - Output : 3   
   
<br>
위의 두 문제는 다른 문제이다.
<br>
<br>



```C++
#include <iostream>
#inlcude <math.h>
using namespace std;
int listS[100];
int n;
int x;
int index = -1;
int main(){
    std::cin >> n;
    for(int i=0;i<n;i++){
        cin >> listS[i];
    }
    std::cin >>x;
    for(int i=0;i<n;i++){
        if(listS[i] ==x){
            index =i;
            break;
        }
    }
    if(index >= 0){
        std::cout<<"Yes"<<endl;
        std::cout<<index<<endl;
    }else{
        std::cout<<"NO"<<endl;
        std::cout<<-1<<endl;
    }
}
```
1. X와 같은 요소를 찾을 때까지 listS에 있는 모든 요소를 차례대로 검사한다.
2. 만일 x와 같은 요소를 찾으면 listS의 위치를 out하고, S를 모두 검사하고도 찾지 못하면 0을 out한다.

```C++
void search(int n, const keytype S[], keytype x, index& location){
    location =1;
    while(location <= n && S[location] != x)
        location++;
    if(location > n)
        location = 0;
}
```

<br> 알고리즘을 공부하고싶다면, 문제가 무엇인지부터 파악을 하자.
<br> 문제를 파악하는 것은 input, output을 통해 problem을 해결하는 것이다.

- 컴퓨터가 할 수 있는 일
    - Write into a memory
    - Read from a memory
    - Compare two data read from a memory (number, character, string ... )
    - Operation with data read from a memory( * + shift ... )

<br>

Search Problem 3
----------------------
---------------------
- 전화번호부에서 전화번호를 찾는 문제
- Problem : 전화번호부와 사람이 주어졌을 때, 그 사람의 전화번호부를 찾는 문제
- Instance : "서울시 전화번호부"에서 "홍길동"의 전화번호를 찾는 문제
1. Instance로 받은 이름을 자음, 모음, 받침 모두 분리한 후 전화번호부에 있는 이름들의 첫 글자 자음과 비교, 동일할 경우 모음과 비교, 동일할 경우 받침 비교.
2. 책의 반절 부분을 열고, 맨 앞의 이름과 instance이름을 비교, 그 후 instance가 있을만한 곳의 반절 부분을 여는 것을 반복
----------------------
- Problem : Determine whether x is in the sorted array S of n keys
- n개의 숫자를 가진, 정렬된 배열 S안에 숫자 x의 위치를 확인하는 문제
    - Input : List S, x, n
    - Output : S 안의 x의 위치 (S안에 없다면 -1)

- Instance
    - Input : S=[10,7,11,5,13,8] , x = 5
    - Output : 3   

```C++
int Search(int startIndex, int endIndex){
    middleIndex = (startIndex + endIndex)/2;
    if(startIndex >= endIndex){
        cout<<"-1"<<endl;
    }
    if(x == S[middleIndex]){
        cout<<middleIndex<<endl;
    }
    else if(x < S[middleIndex])
        Search(0,(int)(S.length/2)-1);
    else
        Search((int)(S.length/2),endIndex);
}
```
- Sequential Search와 Binary Search는 input 개수 n이 커질수록 기하급수적인 차이를 보인다.
- array가 정렬이 되어있지 않다면 Binary Search 방법은 아예 사용하지 못한다.
- Sequential Search는 input 개수가 굉장히 적을 때 효율적이다.   
<br>
- Sequential Search는 하나씩 찾는 것이기에 n임.
- Binary Search는 2의 제곱만큼 증가하기 때문에 log<sub>2</sub>N임.
>Binary Search 알고리즘이 더 좋다.

<br>
    
Sort Problem
--------------------
--------------------
- Problem : 배열 S의 요소들을 크기 순으로 정렬하는 문제
    - Input : array S
    - Output : S


- 방법 1
    - S에서 가장 큰 max를 찾아서 어디에 둘까?
        - S의 맨 뒤에 두자 -> 원래 있던 요소는?
        - 가장 쉬운 방법은 T라는 임시 array를 만든다.
            - 다음에는 max를 빼고 나머지 것에서 찾아야한다.
            - 나중에 T에 있는 것을 그대로 S에 대입한다.
        - 새로운 T를 만들어야 한다는 단점(메모리 2배, copy하는 시간)
            - S의 위치와 max의 위치를 바꿔주자.
            - 반복할 때 array count - 찾은개수 만큼 반복하면 된다.
- 방법 2
    - 버블 sort : 앞의 것과 뒤의 것을 계속 비교해서 큰 것을 뒤로 보냄
<br><br>


---------------------
---------------------

<br>

선택 정렬
----------------------
---------------------
- 가장 작은 것을 앞으로 보내자.
- 시간복잡도 : n * (n+1) / 2 => O(n<sup>2</sup>)
```C++
for(int i=0;i<10;i++){
    min = 9999;
    for(int j=i;j<10;j++){
        if(min > array[j]){
            min = array[j];
            index=  j;
        }
    }
    temp = array[i];
    array[i] = array[index];
    array[index] = temp;
}
```

<br>

버블 정렬
----------------------
---------------------
- 옆에 있는 값과 비교하자.
- 시간복잡도 : O(n<sup>2</sup>)
- swapping을 계속 해주는 것이기에 가장 느림
```C++
for(int i=0;i<10;i++){
    min = 9999;
    for(int j=0;j<9-i;j++){
        if(array[j] > array[j+1]){
            temp = array[j];
            array[j] = array[j+1];
            array[j+i] = temp;
        }
    }
}
```

<br>

삽입 정렬
----------------------
---------------------
- 각 숫자를 적절한 위치에 넣자.
- 시간복잡도 : 최악의 경우 O(n<sup>2</sup>)
- 거의 정렬된 상태에서 가장 빠름
```C++
for(int i=0;i<9;i++){
    int j = i;
    while(j>=0 && array[j] > array[j+1]){
        temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
        j--;
    }
}
```
<br>



힙 정렬
----------------------
---------------------
- 힙 : 최소, 최댓값을 빠르게 찾아내기위한 완전이진트리
- 최대 힙 : 부모가 지식보다 큰 힙
- 힙 생성 알고리즘 시간복잡도 : O(logn) 
- 전체 힙 정렬 시간복잡도 : O(n)
```C++
#include<stdio.h>
int number=9;
int heap[9] = {7,6,5,8,3,5,9,1,6};
int main(){
    // 힙 만들기 (정렬은 아직)
    for(int i=1; i<number ;i++){
        int c = i;
        do{
            int root = (c-1)/2;
            if(heap[root] < heap[c]){
                int temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            c= root;
        }while(c!=0);
    }
    // 완성된 힙 정렬
    for(int i=number-1; i>=0 ; i--){
        int temp = heap[0];
        heap[0] = heap[1];
        heap[i] = temp;
        // 첫번째와 마지막 바꾸기
        int root= 0;
        int c = 1;
        do{
            c = 2* root + 1;
            // 왼쪽(c)과 오른쪽(c+1) 자식중에 큰 값 고르기.
            // c < i-1은 정렬한 것을 제외하기 위함
            if(c<i-1 && heap[c] < heap[c+1]){
                c++;
            }
            // 자식이 루트보다 크다면 교환
            if(c<i && heap[root] < heap[c]){
                temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            root = c;
        }while(c < i);
    }
}
```