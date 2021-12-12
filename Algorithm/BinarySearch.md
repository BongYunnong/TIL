Binary Search
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