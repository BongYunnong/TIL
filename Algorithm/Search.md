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
