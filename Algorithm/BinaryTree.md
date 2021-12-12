Binary Tree
=================
<br>

Optimal binary search tree problem
--------------------
--------------------
- Definition : key[1...n]을 정렬하고, pi는 key i를 찾게 되는 확률
    - ci는 key i 를 찾기 위해 필요한 비교연산의 수
    - 평균 탐색 시간은 c1p1 + c2p2 ... + cnpn
    - 목표는 key들을 평균 탐색 시간이 최소가 되도록 binary search tree를 조정하는 것.
- Problem: Dtermine the node containing a key in a binary search tree
    - Input : a binary search tree and a key
    - Output : a node containing the key
    - DataStructure
    ```
    struct nodetype{
        keytype key;
        nodetype* left;
        nodetype* right;
    };
    typedef nodetype* node_pointer;
    ```
- Instance
    - 전화번호를 저장한다고 했을 때, 어떻게 저장할 것인가?
    - 가나다 순? 처음부터 쭉? 
    - Tree를 만들자!

``` C++
void search(node_pointer tree, keytype keyin, node_pointer& p){
    bool found;
    p = tree;
    found = false;
    while(!found){
        if(p->key == keyin)
            found = true;
        else{
            if(keyin < p->key)
                p=p->left;
            else
                p=p->right;
        }
    }
}
```

- A[1][n] = min{A[1][k-1]+A[k+1][n] + 시그마 i가 1부터 n까지 pi}
```C++
void optsearchtree(int n, const float p[], float& minavg, index R[][]){
    for(i =1; i<=n; i++){
        A[i][i-1] = 0;
        A[i][i] = p[i];
        R[i][i] = i;
        R[i][i-1] = 0;
    }
    A[n+1][n] = 0;
    R[n+1][n] = 0;
    for(diagonal = 1; diagonal <=n-1; diagonal++){
        for(i=1, i=n+diagonal;i++){
            j=i+diagonal;
            A[i][j] = min(A[i][k-1]+A[k+1][j] + 시그마 m이i에서 j까지 Pm);
            R[i][j] = value of k that gave the minimum
        }
    }
    minavg = A[1][n];
}
```
<br>

Code
--------------------
--------------------
- binary code : each character is represented by a unique binary string, called the codeword
- fixed-length binary code : represents each message (character) using the same number of bits
- Instance
    - a : 00, b: 01, c:11
    - ababcbbbc
    - 000100011101010111
- variable-length binary code : use different number of bits
- Instance
    - some message appear more frequently
    - a : 10, b: 0, c: 11
    - ababcbbbc
    - 1001001100011
<br>


Huffman Code Problem
--------------------
--------------------
- code? 어떠한 의미를 문자로 표현한 것.
- b라는 문자가 많이 사용된다면, b를 짧게 표현하는 것이 좋다.
- Encoding Instance
    - Bits(C1) = 16(3) + 5(3) + 12(3) + 17(3) + 10(3) + 25(3) = 255
    - Bits(C2) = 16(2) + 5(5) + 12(4) + 17(3) + 10(5) + 25(1) = 231
    - Bits(C3) = 16(2) + 5(4) + 12(3) + 17(2) + 10(4) + 25(2) = 212


|Character|Frequency|C1(fixed-length)|C2|C3(Huffman)  |  
|:---: | :---: | :---: |  :---: |  :---: |  
| a | 16 | 000 | 10 | 00 |
| b | 5  | 001 | 11110 | 1110 |
| c | 12 | 010 | 1110 | 110 |
| d | 17 | 011 | 110 | 01 |
| e | 10 | 100 | 11111 | 1111 |
| f | 25 | 101 | 0 | 10 |
- fixed로 표현하면 6개를 표현하고싶다면 2<sup>2</sup>으로는 부족하기에 2<sup>3</sup>이 필요
- 빈도가 다 비슷하면 C1이 좋겠지만, 사용되는 빈도가 다르다면 variable-length 방식이 좋을 수 있다.
- 우리의 목적 : 각 메시지들의 frequency가 주어졌을 때, 평균 코드의 길이가 가장 적은 코드를 만들고싶다. => 이진트리

- a,b,c,d,e,f를 frequency를 기준으로 정렬하고, 왼쪽에 더 많이 사용된 것, 오른쪽에 덜 사용된 것을 나열하다보면, 한쪽으로 치우친 2진 트리가 만들어진다. -> C2방식


Prefix code and binary code tree
--------------------
--------------------
- prefix code
    - No codeword for one character constitutes the beginning of the codeword for another character
- Every prefix code can be represented by a binary code tree whose leaves are the characters that are to be encoded.
    - a:10, b: 0, c:11
- prefix code의 해독
    - code의 가장 처음 비트와 tree의 root에서 시작
    - code를 읽으면서 code의 값에 따라 tree의 왼쪽, 오른쪽을 선택
    - tree의 leaf에 닿으면 character를 출력하고 다시 root로 이동

- 어떻게 binary tree를 만들어야 할까?
    - frequency가 가장 작은 값 2개를 합쳐서 tree 구조를 만드는 것을 반복
    - 5, 10, 12, 16, 17, 25
    - 12, 15, 16, 17, 25
    - 16, 17, 25, 27
    - 25, 27, 33
    - 33, 52
    - 85

- Q: 왜 굳이 두 값을 더하는가?
    - A : 우리가 원했던 것은 frequency * depth였음. 5 * 4 + 10 * 4 + 12 * 3 이렇게 되어서 이것이 최소화 되기를 원했던 것임.
    - 어라? 4 * (5+10) 얘네가 가지 하나만 있었으면 5+10이 되었을 것.
    - 그런데 여기에 4가 곱해지게 된 것은 depth가 4라서 그렇다.
    - 이것은 depth가 증가할수록 한번씩 더 사용된다는 것이다.-> 12 * 1 + (5+10) * 2
    - 작은 것을 2개 합치는 기준을 가진 Greedy Algorithm이구나.


Huffman's Algorithm
--------------------
--------------------
```C++
for(i = 1; i<= n-1 ; i++){
    remove(PQ, p);
    remove(PQ, q);
    r = new nodetype;
    r->left= p;
    r->right = q;
    r->frequency = p->frequency + q->frequency;
    insert(PQ, r);
}
remove(PQ, r);
return r;
```
- n = number of characters in the file
     - 다음과 같은 n개의 tree를 생성해서 priority queue PQ에 저장
     - p->symbol = character
     - p->frequency = character의 frequency
     - p->left = p->right = NULL

- PQ는 priorityQueue임
    - priority Queue : the element with the highest priority is always removed next
    - linked list나 heap으로 구현 가능
    - In this case, the element with the highest priority is the character with the lowest frequency in the file.
    ``` 
    struct nodetype{
        char symbol;
        int frequency;
        nodetype* left;
        nodetype* right;
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