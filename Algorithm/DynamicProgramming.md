Dynamic Programming
=================
<br>

Divide and Conquer
--------------------
--------------------
- Divide a problem into smaller instances and blindly solve these smaller instances
- Top-down approach
<br>

Dynamic Programming
--------------------
--------------------
- Divide a problem into smaller instances
- Solve smaller instances first and Store the results
- Whenever needed, look the results, instead of recompute
- Bottom-up approach

<br>

n th Fibonacci Term - recursive version
--------------------
--------------------
- f[0] = 0
- f[1] = 1
- f[n] = f[n-1] +f[n-2] (n>=2)
```C++
int fib(int n){
    if(n<=1)
        return n;
    else
        return fib(n-1) + fib(n-2);
}
```
- 이 방법의 문제점 : fib(5)는  fib(4) + fib(3)인데, fib(4)가 fib(3)+fib(2)라서 fib가 중복된다.


<br>

n th Fibonacci Term - Dynamic Programming
--------------------
--------------------
```C++
int fib2(int n){
    f[0] = 0;
    if(n>0){
        f[1] = 1;
        for(i=2;i<=n;i++){
            f[i] = f[i-1] + f[i-2];
        }
    }
    return f[n];
}
```
- reculsive를 사용하지 않고, 애초에 array를 만들어서 순차적으로 계산
- Dynamic Programming은 계산한 값을 저장해두었다가 필요할 때 쓰는 방식으로 반복된 계산을 피하는 것.

<br>

Manhattan Tourist Problem (MTP)
--------------------
--------------------
- 왼쪽 위에서 오른쪽 아래로 이동하는데, 주요 관광지를 거치는 문제
- 관광지마다 가중치가 있다.
- 방향성이 있는 Graph
- Problem : Find the longest path(only eastward and southward) in a weighted grid
- Input : A weighted grid G with two distinct vertices, one labeled "source" and the other labeled "sink"
- Output : A longest path (only eastward and southward) in G from "source" to "sink"
<br><br>

- 모든 길을 다 찾아보자!
    - for(for(for(for(for(for(...))))))
    - 문제는 경우의 수가 너무 많다는 것.
    - 풀리기는 하겠지만, 좋은 알고리즘이 아니다.

- Recurrence
    - Let s<sub>i,j</sub> be the longest path length from the source to (i, j)
    - S<sub>i,j</sub> = max(<br>S<sub>i-1,j</sub> + weight of the edge between(i-1,j) and (i,j) ,<br> S<sub>i,j-1</sub> + weight of the edge between(i,j-1) and (i,j))
    - 왼쪽 위에서부터 오른쪽, 아래로 순차적으로 최대 값을 갱신하면 longest path를 구할 수 있다.
```C++
MTR(n,m){
    if(n==0 && m==0) return 0;
    if(n==0)
        return MTR(0,m-1) + length of the edge from (0,m-1) to (0, m)
    if(m==0)
        return MTR(n-1,0) + length of the edge from (n-1,0) to (n, 0)

    x = MTR(n-1,m) + length of the edge from (n-1, m) to (n,m)
    y = MTR(n,m-1) + length of the edge from (n,m-1) to (n,m)
    return max{x,y} 
}
```
- 이것은 recursive한 해결법

```C++
MT_DP{
    S[0,0] = 0
    // 먼저 오른쪽으로 쭉 진행하는 길과 아래로 쭉 진행하는 길을 계산
    for i = 1 to m
        S[i,0] = S[i-1, 0] + U[i,0]
    for j = 1 to n
        S[0,j] = S[0, j-1] + L[0,j]
    // 차근차근 계산
    for i = 1 to m
        for j = 1 to n
            S[i,j] = max{S[i-1,j] + U[i,j], S[i,j-1] + L[i,j]}
}
```
- U와 L은 선분의 weight

<br>

Chained matrix multiplication
--------------------
--------------------
- i X j 행렬과 j X k 행렬을 곱하기 위해서는 i X j X k번 만큼의 곱셈이 필요하다.
- 연쇄적으로 행렬을 곱할 때, 어떤 행렬곱셈을 먼저 수행하느냐에 따라 필요한 곱셈의 횟수가 달라지게 된다.
- 예를 들어서, 다음 연쇄행렬곱셈을 생각해보자.
    - A<sub>1</sub> * A<sub>2</sub> * A<sub>3</sub>
    - A<sub>1</sub>의 크기 10 * 100, A<sub>2</sub>의 크기 100 * 5, A<sub>3</sub>의 크기 5 * 50
    -  A<sub>1</sub> *  A<sub>2</sub>를 먼저 계산한다면, 곱셈의 총 횟수는 7500회
    -  A<sub>2</sub> *  A<sub>3</sub>를 먼저 계산한다면, 곱셈의 총 횟수는 75000회
    - 따라서, 연쇄적으로 행렬을 곱할 때 곱셈의 횟수가 가장 적게 되는 최적의 순서를 결정하는 알고리즘을 개발하는 것이 목표이다.
- Instance
    - Input : Matrix A는 사실 d0, d1, d2 ... dk이다. (10,100,5,50)
    - Output : 1-2-3
<br>

- 내 생각 : 가장 큰 수부터 곱을 하면 어떨까?
- M[i][j] = Minimum number of multiplications needed to multiply A<sub>i</sub> through A<sub>j</sub> (if i < j)
    - M[i][i]=0;
    - M[1][2] = A1 * A2 => d0 * d1 * d2
    - M[2][3] = A2 * A3 => d1 * d2 * d3
    - M[n-1][n] = d(n-2) * d(n-1) * dn
    - 우리가 궁극적으로 원하는 것? M[1][n] => A1(A2...An) or (A1*A2)(A3...An)...(A1....An-1)*An

| 0   |           |              |               |    |
|:---: | :---: | :---: |  :---: | :---: |   
| M[1][2] = d0 * d1* d2  | 0            |   |    |
| M[1][3] = M[1][k]+M[k+1][3]+d0*d3*dk | M[2][3] = d1 * d2 *d3       | 0 | |
| M[1][4] = M[1][k]+M[k_1][4]+d0*d4*dk | M[2][4] = M[2][k] + M[k+1][4] + d1*d4*dk       | M[3][4] = d2 * d3 *d4  |  0|

> M[i][j] = M[i][k] + M[K+1][j] + d(i-1) * dj * dk <br> =di * M[i+1][j] or M[i][j] * d(j-1) <br> M[1][n] = d0 * M[2][n] or M[1][n] * d(n-1)

```C++
int mat(int n){
    int a,b;
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<n-i;j++){
            a = j;
            b = j+1;
            if(a==b){
                dp[a][b] = 0;
            }else{
                dp[a][b] = 9999999;
                for(k=a;k<b;k++){
                    dp[a][b] = min(dp[a][b],
                                    dp[a][k]+dp[k+1][b] 
                                    + matrix[a][0]*matrix[k][1]*matrix[b][1]);
                }
            }
        }
    }
    return dp[0][n-1];
}
int min(int x, int y){
    return x < y ? x: y;
}
```


<br>

Minimum Multiplication
--------------------
--------------------
- Problem : Determining the minimum number of elementary multiplications needed to multiply n matrices and an order that produces that minimum number.
    - Input : the number of matrices n, array of integers d[0...n], d[i-1]Xd[o] is the dimension of the ith matrix
    - Output : minmult, the minimum number of elementary multiplications needed to multiply the n matrices. 2d array P
- Instance
    - A(20X2) * B(2X30) * C(30X12) * D(12X8)
    - output : 1232
    - A(B(CD)) 30 * 12 * 8 +  2 * 30 * 8   + 20 * 2 * 8  = 3680
    - (AB)(CD) 20 * 2 * 30 +  30 * 12 * 8  + 20 * 30 * 8 = 8880
    - A((BC)D) 2 * 30 * 12 +  2 * 12 * 8   + 20 * 2 * 8  = 1232
    - ((AB)C)D 20 * 2 * 30 +  20 * 30 * 12 + 20 * 12 * 8 = 10320
    - (A(BC))D 2 * 30 * 12 +  20 * 2 * 12  + 20 * 12 * 8 = 3120
    
``` C++
int minmul(int n, const int d[]){
    for(i=1 ; i<=n ; i++){
        M[i][i] =0;
    }
    for(diagonal = 1; diagonal <= n-1; diagonal++){
        for(i=1, j=1+diagonal; i<= n-diagonal ; j++,i++){
            M[i][j] = minimum(M[i][k] + M[k+1][j] + d[i-1]*d[k]*d[j]);
            (where i <= k <= j-1)
        }
    }
    return M[i][n];
}
```
- 시간복잡도 : N + N<sup>2</sup>

- M[i][j] 하나하나를 써줘야 할 때 기본적으로 N<sup>2</sup>만큼을 우선 채워줘야 한다.

<br>

- 그런데 최적의 정보는 이 안에 없음
- 이것을 추가한 코드는 아래와 같다.
<br>

```C++
int minmult(int n, const int d[], index P[][]){
    index i,j,k,diagonal;
    int M[1...n][1...n];
    for(i = 1; i<= n ; i++){
        M[i][i]= 0;
    }
    for(diagonal = 1; diagonal <= n-1 ; diagonal++){
        for(i = 1; i<= n - diagonal ; i++){
            j = i + diagonal;
            M[i][j] = minimum(M[i][k] + M[k+1][j] + d[i-1]*d[k]*d[j]);
            P[i][j] = a value of k that gave the minimum;
        }
    }
    return M[1][n];
}
```
<br>

Binomial Coefficient
--------------------
--------------------
- <sub>n</sub>C<sub>k</sub> = n! / k!(n-k)! (0<=k<=n)
- = <sub>n-1</sub>C<sub>k-1</sub> + <sub>n-1</sub>C<sub>k</sub>
    - 이렇게 되는 이유는, 1을 포함한 부분집합, 1을 포함하지 않은 부분집합으로 나누어서 두개를 합친 것과 전체의 부분집합이 똑같기 때문.
- recursive version
    - 계산 값이 중복
```C++
int bin(int n, int k){
    if(k==0 || n==k){
        return 1;
    }else{
        return bin(n-1,k-1) + bin(n-1,k);
    }
}
```
- Dynamic Programming
```C++
int bin2(int n, int k){
    index i, j;
    int B[0...n][0...k];
    for(i = 0; i<= n; i++){
        for(j = 0; j<= minimum(i,k); j++){
            if(j==0 || j == i)
                B[i][j] = 1;
            else
                B[i][j] = B[i-1][j-1] + B[i-1][j];
        }
    }
    return B[n][k];
}
```
- 시간 복잡도
    - 1+2+3+..+k + (K+1) * (n-k+1)
    - = k(k+1)/2 + (n-k+1)(k+1)
    - (2n-k+2)(k+1)/2 ∈ 0(nk)

<br>

Shortest Paths Problem
--------------------
--------------------
- Problem : 가중치 포함, 방향성 그래프에서 모든 노드에서 모든 다른 노드로의 최단경로 찾기
- 최적화 문제(optimization problem) : 주어진 문제에 대하여 하나 이상의 많은 해답이 존재할 때, 이 가운데에서 가장 최적인 해답을 찾아야 하는 문제
- Input : directed graph Matrix
- Output : shortest path Matrix

<br>

- 첫번째 방법 : 임의의 노드에서 임의의 노드로 가는 모든 path를 체크
    - 하지만 경우의 수가 너무 많다.

- 두번째 방법 : 동적 계획식 설계전략
    - 그래프의 인접행렬(adjacent matrix)식 표현 : W
    - W[i][j] = 이음선의 가중치(i to j 이음선 존재) | ∞ (i to j 이음선 존재X)| 0(i=j)
    - 그래프에서 최단경로의 길이의 표현 : 0 <= k <= n인, D<sup>(k)</sup>[i][j] = {v1,v2,v3... vk}의 정점들 만을 통해서 vi에서 vj로 가는 최단경로의 길이
    - k는 경유하는 정점

- Chained matrix multiplication
> D<sup>(k)</sup>[i][j] = minimum( D<sup>(k-1)</sup>[i][j] , D<sup>(k-1)</sup>[i][k] + D<sup>(k-1)</sup>[k][j] )

- D(k)[i][j]와 D(k-1)[i][j]의 관계는?
    - K를 거치는 방법
        -  D(k)[i][j] = D(k-1)[i][k] + D(k-1)[k][j]
    - K를 거치지 않는 방법
        - D(k)[i][j] = D(k-1)[i][j]
    - D(k)[i][j] = min{D(k-1)[i][k] + D(k-1)[k-1][j], D(k-1)[i][j]}
-  문제를 해결하기 위해서
    - D(0)[i][j]는 알고있음
    - D(0)[i][j]를 활용해서 D(1)[i][j]를 도출
    - D(1)[i][j]를 활용해서 D(2)[i][j]를 도출
    ...
    - D(n)[i][j]를 도출


Floyd의 알고리즘 1
--------------------
```C++
void floyd(int n, const number W[][], number D[][][]){
    int i, j, k;
    D[0] = W;
    for(k=1; k<= n ; k++){
        for(i=1; i<= n; i++){
            for(j=1; j<= n; j++){
                D[k][i][j] = minimum{D[k-1][i][j], D[k-1][i][k]+D[k-1][k][j]};
            }
        }
    }
}
```
- 시간복잡도
    - 2차원 배열을 2차원 배열에 집어넣음 n*n
    - K가 1부터 n번, i도 n번, j도 n번 -> minimum은 비교 한 번, assign 한 번 -> 2*n<sup>3</sup>번
    - O(n<sup>3</sup>)
- 공간복잡도
    - n<sup>3</sup>

<br>

Floyd의 알고리즘 2
--------------------
```C++
void floyd(int n, const number W[][], number D[][]){
    int i, j, k;
    D = W;
    for(k=1; k<= n ; k++){
        for(i=1; i<= n; i++){
            for(j=1; j<= n; j++){
                D[i][j] = minimum{D[i][j], D[i][k]+D[k][j]};
            }
        }
    }
}
```
- 이거는 1과 다르게, 2차원 배열만 사용함.
- k-1을 통해 k를 만들어내면, k-1 정보는 필요가 없어진다.
- 메모리는 항상 n<sup>2</sup>(k-1만드는 것)+n<sup>2</sup>(k만드는 것) 만큼 필요
- 이게 왜 됨?
    - K가 크다면, 아직 덮어지지 않은 영역이기에 괜찮음
    - K가 적으면, 덮어진 영역에 있으니 이미 K로 업데이트 되었음
    - 그렇다면, K를 만들 떄 K로 업데이트 된 것을 사용한 것은 아닐까?
    - 맞긴 한데, 문제가 없다. D(k)(i)(k)가 D(k-1)(i)(k)와 같기 때문.
    - 1부터 k까지를 거친다고 해봐야 1부터 k-1까지를 거쳐서 가는 것과 같음
    - D(k-1)(i)(k)도 k에서 출발하기 때문에 D(k)(i)(k)와 같음
- 시간복잡도 : T(n) = n * n * n = n<sup>3</sup> ∈ 0(n<sup>3</sup>)

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
- A[i][j] = min{A[i][k-1]+A[k+1][j] + 시그마 m이 i부터 j까지 pm}
```C++
void optsearchtree(int n, const float p[], float& minavg, index R[][]){
    for(i =1; i<=n; i++){
        A[i][i-1] = 0;
        A[i][i] = p[i];
        R[i][i-1] = 0;
        R[i][i] = i;
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