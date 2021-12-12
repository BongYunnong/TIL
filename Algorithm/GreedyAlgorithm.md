Greedy Algorithm
=================
<br>

Greedy
--------------------
--------------------
- 스쿠루지 영감의 목적 : 오늘 밤 내 금고에 돈이 가장 많게 하는 것
- 그리디 알고리즘 : 목표를 하나 정해서 매 순간 그 기준에 부합하는 최고의 선택을 한다.

<br>

Give Change
--------------------
--------------------
- Problem : 코인의 개수가 최소가 되도록 잔돈을 주기.
- Instance : 25 1개, 10 2개, 5 1개, 1 2개

- 가장 큰 단위부터 줄까?
    - 만약 16센트라면, 25못주고, 10주고, 5주고, 1줘서 최적임
    - 하지만 다른 Instance에서는 최적이 아닐 수 있다.

- Instance : 12 1개, 10 1개, 5 1개, 1 4개
    - 아까처럼 하면 12주고, 1 4개를 줘야함 -> 5개의 동전.
    - 그냥 10, 5, 1 3개를 주면 될 것을 5개의 동전을 줘야 함
    - 아, 항상 최적의 알고리즘은 아니구나.


<br>

Minimum Spanning Tree Problem(MST)
--------------------
--------------------
- 해결방법 1
    - 아무 노드나 하나를 잡고, 연결된 edge 중 가장 값이 작은 edge와 연결된 노드를 방문한다.
    - 하지만 이렇게 하면 spanning tree가 안 될 수도 있고, minimum이 아닐 수도 있다.
    - 그러니 모든 노드에 대해서 위의 것을 반복한다.
    - 하지만 이래도 문제는 있음

- 해결방법 2
    - 임의의 노드를 하나 선택한다. 
    - 선택된 모든 노드에 대해서 아직 선택되지 않은 노드와의 edge cost가 제일 작은 것을 고른다.
    - v1에서 시작했을 경우, v2로 가고, 그 후에 v1과 v2를 연결

- Prim's greedy Algorith for MST
```C++
F={}
Y={v1}
while(the instance is not solved){
    Select a vertex v in V-Y that that is nearest to Y;
    Add the vertex v to Y;
    Add the edge (on the shortest path) to F;
    if(Y==V)
        The Instance is solved;
}
```
```C++
void MST(int n, int W[][], set_of_edges& F){
    F= empty_set;
    inY[1] = 1;
    for(i=2; i<=n ; i++){
        inY[i] = 0;
    }
    repeat(n-1 times){
        min = "infinite";
        for(j=1;j<=n;j++){
            for(i=1;i<=n;i++){
                if(inY[j]==1 && inY[i] == 0){
                    if(W[j][i] < min){
                        min = W[j][i];
                        vnear = i;
                        near = j;
                    }
                }
            }
        }
        e = vnear와 near를 잇는 edge;
        e를 F에 추가
        inY[vnear] = 1;
    }
}
```
- 위의 코드는 Graph Matrix를 이용해서 j에서 i까지 가는 distance를 갱신하는 것
- J가 시작 vertex, i가 도착 vetex. j는 방문한 상태이고, i는 방문하지 않은 상태
- edge가 최소라면 vnear와 near를 갱신하여 e에 추가한다. 그리고 vnear는 방문했다는 뜻으로 1로 갱신한다.
- 하지막 이 방법도 좀 낭비가 된다. i,j를 for문으로 반복하기 때문이다.
- 시간복잡도 : n+n번이 n번 -> n * (n<sup>2</sup> + n) -> O(n<sup>3</sup>)

<br>

```C++
void MST(int n, int W[][], set_of_edges& F){
    F= empty_set;
    for(i=2; i<=n ; i++){
        nearest[i] = 1;
        distance[i] = W[1][j];
    }
    repeat(n-1 times){
        min = "infinite";
        for(i=2;i<=n;i++){
            if(0<=distance[i]<min){
                min = distance[i];
                vnear = i;
            }
        }
        e = vnear와 nearest[vnear]를 잇는 edge;
        e를 F에 추가
        distance[vnear] = -1;
        for(i=2;i<=n;i++){
            if(W[i][vnear] < distance[i]){
                distance[i] = W[i][vnear];
                nearest[i] =vnear;
            }
        }
    }
}
```
- Distance를 처음에 vi와 v1사이의 가중치로 초기화
    - 이 distance는 현재 탐색하려는 노드에서의 다른 i노드와의 거리
- repeat문에 들어가서는 distance에 있는 것들 중 가장 작은 것을 뽑아낸다.
- distance가 -1이면 방문했다는 것이기에 그럴 경우는 배제한다.
- 가장 작은 것을 찾아내면 vnear로 뽑아낸 index에 위치한 distance 요소를 -1로 만들어서 방문했다는 것을 알린다.(edge 추가하고싶으면 추가)
- 만약 그래프에서 i에서 vnear까지 가는 것이 distance[i]보다 작으면, distance를 그 값으로 갱신하고, 가장 가까운 것인 nearest[i]도 vnear로 갱신한다.
- 처음에 그냥 v1과 이어진 vi의 가중치만 생각했기 때문에 원래 갈 수 없는 곳이었는데, vnear가 새로 갱신되면서 갈 수 있게 된다.
- distance를 갱신하는 이유는 다음 loop에 사용해야하기 때문
- 위의 코드와 다른 점은, distance라는 배열을 만들어서 inY의 역학롸 최소의 가중치를 저장하는 역할을 동시에 했다는 것이다.
- 시간복잡도 : O(n<sup>2</sup>)
- Optimal할까? Yes


<br>

- Kruskal Algorithm
    - Edge의 최소 값을 찾아서 두 정점을 잇는다.
    - 이때, 추가시킨 edge가 cycle을 만들면 무시한다.
    - 과연 Optimal할까? Yes



Single Source Shortest Path Problem
--------------------
--------------------
1.	방향이 있는 그래프 G가 주어졌을 때 vertex u에서 vertex w로 가는 가장 짧은 길 찾기
    - Input : G, u, w Output : u에서 w로 가는 가장 짧은 길
2.	방향이 있는 그래프 G가 주어졌을 때 u에서 다른 모든 vertex로 가는 가장 짧은 길 찾기
    - Input : G, u Output : u에서 다른 모든 vertex로 가는 가장 짧은 길
3.	방향이 있는 그래프 G가 주어졌을 때 u에서 v로 가는 모든 짝 중에서 가장 짧은 길 찾기
    - Input : G  Output : u에서 w로 가는 가장 짧은 짝과 길 (Graph가 out됨)

- 1번은 그냥 길이 있으면 다 해보면 되지만, u에서w까지 가는 길이 너무 많으면 기하급수적으로 커짐
- 3번은 All pair shortest path problem을 쓰면 됨 -> dynamic programming
- 2번은 3번을 구하면 그 중의 일부가 2임.


Dijkstra Algorithm
--------------------
--------------------
- Problem : Given a directed weighted graph G and a vertex u of G, find the shortest paths from the vertex u to all the other vertices
- Input : G, u
- Output : shortest path length to all the other vertices

- 해결방법
    - 임의로 정한 v1에서 먼저 출발하여 가장 weight가 적은 edge로 탐색
    - 방문한 노드를 거가까지 가는데에 필요했던 비용과 함께 저장
    - 다음 경로를 선택하려 할 때 그 list에 있는 노드들과 연결된, 방문되지 않은 노드와의 edge 가중치 + 자신까지 오는 데 필요했던 가중치를 비교
```C++
F={}
Y={v1}
while(the instance is not solved){
    Select a vertex v in V-Y that has a shortest path from v1;
    Add the vertex v to Y;
    Add the edge (on the shortest path) to F;
    if(Y==V)
        The Instance is solved;
}
```
```C++
void dijkstra(int n, const number W[][], set_of_edges& F){
    index i, vnear;
    edge e;
    index touch[2...n];
    number length[2...n];
    F = empty_set;
    for(i=2; i<=n ;i++){
        touch[i] = 1;
        length[i] = W[1][i];
    }

    repeat(n-1 times){
        min = "infinite";
        for(i=2;i<=n;i++){
            if(0 <= length[i] < min){
                min = length[i];
                vnear = i;
            }
        }
        e=  edge from vertex indexed by touch[vnear] to vertex indexed by vnear
        Add e to F;
        for(i= 2; i<=n; i++){
            if(length[vnear] + W[vnear][i] < length[i]){
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        }
        length[vnear] = =1;
    }
}
```
- touch[i] : index of vertex V in Y
    - <v,vj> is the last edge on the current shortest path from v1 to vi using only vertices in Y as intermediates.
- length[i] : length of the current shortest path from v1 to vi using only vertices in Y as intermediates.
- length중에서 가장 작은 것을 찾아서 vnear에 저장
- Distance 값을 업데이트 해줘야한다.
    - Y가 변하지 않았을때의 length와 Y가 변한 후의 Length값(새로운 길+가중치)를 비교한다.
    - length값이 -1이면 해당 index의 값이 Y에 저장된 것

- 시간복잡도
    - 2n * (n-1) => Θ(n<sup>2</sup>)
    - 플로이드 알고리즘은 O(n<sup>3</sup>)이라서, 2번 문제를 풀기 위해 분할한 것이 다익스트라 알고리즘.
    - Greedy 알고리즘이지만 항상 Optimal하다.