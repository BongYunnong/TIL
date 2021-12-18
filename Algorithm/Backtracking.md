Branch And Bound
=================
<br>

(Fractional) Knapsack problem
--------------------
--------------------
- Problem : 물건 n개의 집합 S={1,2...n}와 W={w1,w2...wn}, P={p1,p2...pn}가 주어졌을 때, 배낭에 이러한 물건들을 넣어 시장에 판다고 하자. 얻을 수 있는 최대 이윤을 구하자.
- wi(>0) : 각 물건 i의 무게
- pi(>0) : 물건 i 를 시장에서 팔았을 때 얻는 이윤
- M : 배낭의 크기
- factional은 물건을 쪼갤 수 있다는 것.

1. 만약 물건을 쪼갤 수 있다면 (fractional)
    - 물건을 어떤 기준에 맞춰서 잘게 쪼갠 후 그리디하게 가져가자.
    - pi를  wi로 나누면 1 단위에 따른 이윤으로만 생각할 수 있다.
    - 여기서부터는 그 이윤들을 정렬한 후에 배낭에 넣으면 된다.
    - ex. (4-10,5-2,10-6) 이렇게 물건이 있다면, 4/10이 10개, 5/2가 2개, 10/6이 6개이다.
        - 우선 5/2의 가치를 가진 것을 먼저 넣고, 배낭의 크기에 맞춰서 10/6, 4/10을 넣으면 된다.
2. 만약 물건을 쪼갤 수 없다면 (0-1)
    - policy 1 : 제일 이윤이 높은 것을 먼저 가방에 두자.
        - 이러면 별로 좋지 않은 것이, 가치 10이고 무게 100인물건과 가치 9이고 무게 1인 물건이 있을 수 있음
    - policy 2 : 제일 무게가 작은 것부터 두는 것도 별로임
    - policy 3 : 단순하게 생각해서, 가치가 높을수록 좋고, 무게가 적을수록 좋으니(가치/무게)를 지표로 하여 그때부터 배낭 크기에 들어가기만 한다면 가치가 높은 것부터 차례대로 넣는다.
        - 나름 좋은 policy지만 optimal하지는 않음
    - policy 4 : 가치/무게를 기준으로 정렬하고, 가치가 높은 순부터 차례대로 넣을지, 안 넣을지 탐색하는 binary tree를 만들자.

    - 이 문제를 해결하려면 먼저 sum of subset 문제를 보고 오자.

<br>

The Sum of Subsets Problem
--------------------
--------------------
- Problem : there are n positive integers wi and a positive integer W. The goal is to find all subsets of the integers that sum to W. As mentioned earlier, we usually state our problems so as to find all solutions. For the purpose of the thief's application, however, only one solution need be found
- Instance
    - suppose that n= 5, W = 21, and w1=5,w2=6,w3=10,w4=11,w5=16
    - w1+w2+w3 = 5+6+10 = 21, w1+w5=5+16=21, w3+w4=10+11=21
    - solutions are {w1,w2,w3}, {w1,w5}, {w3,w4}

- Inputs : integers w1...wn and W
- Outputs : A subset of the integers that sum to W
- Instance
    - Input : (2,4,5) , 6
    - Output : {2,4}

- 하나씩 다 해보면 되긴 하지만, 다 더해야하서 2<sup>n</sup>만큼 걸림 -> 불가능
- 그렇다면 어느정도 하다가 앞으로 가능성이 없는 것(non promising)은 계산하지 말자.

<br>

The Sum of Subsets Problem
--------------------
--------------------
- Consists of doing depth-first-search of a state space tree, checking whether each node is promising, and, if it is non-promising, backtracking to the node's parent
- Pruning the state space tree
- Promising function

- 깊이 우선 탐색(depth-first-traversal)
    - preorder tree traversal
    ```C++
    void depth_first_tree_search(node v){
        visit(v);
        for(each child u of v){
            depth_first_tree_search(u);
        }
    }
    ```
    - postorder tree traversal
    ```C++
    void depth_first_tree_search(node v){
        for(each child u of v){
            depth_first_tree_search(u);
        }
        visit(v);
    }
    ```
    - inorder tree traversal(binary tree)
- 너비 우선 탐색(breadth-first-traversal)



<br>

- Backtracking algorithm - 백트랙킹의 골격
```C++
void checknode(node v){
    if(promising(v)){
        if(there is a solution at v){
            write the solution;
        }else{
            for(each child u of v){
                checknode(u);
            }
        }
    }
}
```
<br>

- Backtracking algorithm - call sos(0,0,T)
```C++
void sos(index i, int weight, int total){
    if(promising(i)){
        if(weight==W){
            cout<<include[1]...include[n];
        }else{
            include[i+1] = "yes";
            sos(i+1,weight+w[i+1], total-w[i+1]);
            include[i+1] = "no";
            sos(i+1,weight,total-w[i+1]);
        }
    }
}
bool promising(index i){
    return (weight + total >= W) && (weight==W || weight + w[i+1] <= W);
}
```
- total에서 w[i+1]을 빼주면, 남아있는 total이 된다. 남아있는 것들을 다 더해도 W보다 작을 경우, 더 진행할 필요가 없다.

- weight가 W라는 것은 solution에 도달했다는 것.
- 그 전에는 왼쪽과 오른쪽 노드에 sos를 다시 call 해야함
- promising이란? 어느 노드에 가서 다 방문을 할텐데, 이것이 더이상 진행할 필요가 있는가.

- Backtracking algorithm for the sum-of-subet problem
    - promising function?
    - nonpromising if
        - weight + w<sub>i+1</sub> > W
        - weight + total < W
        - weight is the sum of weights that have been included up to a node at level i
        - total is the total weight of the remaining weights


        
<br>

0-1 Knapsack problem
--------------------
--------------------
- Inputs : S={item i | i = 1, 2...n} where item i has integer weight w i and profit p i, and W
- Outputs : subset A of S such that weight in A is less than or equal to W and profit is maximized

- 어떤 괜찮은 값을 찾았는데, 더 optimal한 값이 있는지 체크하기는 어려움 -> 다 해봐야한다.

- totalweight = weight + 시그마 j는 i+1부터 k-1까지 Wj
- bound = profit + 시그마 j는 i+1부터 k-1까지 Pj + (W- toweight)*pk/wk
- maxprofit : the profit found so far
- bound : the upper bound of the profit(얻을 수 있는 최대 값)
- if bound <= maxprofit, the node is nonpromising

- bound를 어떻게 구할 것인가? fractional하게 생각하자. optimal한 것은 fractional한 것이기 때문에, 실제로 불가능하더라도, 이것을 기준으로 하자.

- 시간복잡도 : O(2<sup>n</sup>)
    - 이것보다 좋은 알고리즘이 없을까? 아직 못찾음

```C++
void knapsack(index i, int profit, int weight){
    if(weight<= W && profit > maxprofit){
        maxprofit = profit;
        numbest = i;
        bestset = include;
    }
    if(promising(i)){
        include[i+1] = "yes";
        knapsack(i+1, profit+p[i+1],weight+w[i+1]);
        include[i+1] = "no";
        knapsack(i+1,profit,weight);
    }
}
```

- depth first로 안하면 어떨까?
- branch and bound algorithm - breadth first
```C++
void breadth_first_traversal(state_sapce_tree T){
    Queue Q;
    initialize(Q);
    v = root of T;
    enqueue(Q, v);
    while(!empty(Q)){
        dequeue(Q,v);
        for(each child u of v){
            visit(u);
            enqueue(Q, u);
        }
    }
}
```
- Dequeue를 하면서 child들을 enqueue -> 반복
```C++
void breadth_first_branch_and_bound(state_sapce_tree T,number& best){
    Queue Q;
    initialize(Q);
    v = root of T;
    enqueue(Q, v);
    best = value(v);
    while(!empty(Q)){
        dequeue(Q,v);
        for(each child u of v){
            if(value(u) is better than best)
                best = value(u);
            // bound가 best보다 높은 것만 enqueue를 하면서 
            // 자동으로 nonpromising은 사라짐
            if(bound(u) is better than best)
                enqueue(Q, u);
        }
    }
}
```
- 또 다른 방법은 없을까?  PriorityQueue
    - Queue는 First in First out인데, Priority Queue는 가장 priority가 가장 높은 것부터 out됨
    - bound가 큰 값부터 expand를 하게 되면, 더 빠르게 가지를 없앨 수 있다.