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
    - S<sub>i,j</sub> = max(<br>S<sub>i-1,j</sub> + weight of the edge between(i-1,j)and(i,j) ,<br> S<sub>i,j-1</sub> + weight of the edge between(i,j-1))
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
    for i = 1 to m
        S[i,0] = S[i-1, 0] + U[i,0]
    for j = 1 to n
        S[0,j] = S[0, j-1] + L[0,j]
    
    for i = 1 to m
        for j = 1 to n
            S[i,j] = max{S[i-1,j] + U[i,j], S[i,j-1] + L[i,j]}
}
```
- U와 L은 선분의 weight