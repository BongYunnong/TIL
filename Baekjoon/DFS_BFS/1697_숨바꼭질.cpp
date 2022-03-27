// https://www.acmicpc.net/problem/1697

// 만약 visited를 안 하면 메모리 초과가 뜬다.
// 나는 최소값을 구해야하기에 visited를 두면 안된다고 생각했었는데, 잘 생각해보면 BFS로 먼저 접근한 것이 가장 빠르게 접근한 것이 된다.

#include<iostream>
#include<queue>
using namespace std;

queue<int> searchQueue;

int grid[100001];
bool visited[100001];

int N,K;
void BFS(){
    while(searchQueue.empty()==false){
        int x = searchQueue.front();
        visited[x]=true;
        if(x==K){
            return;
        }
        searchQueue.pop();

        if(x-1>=0 && visited[x-1]==false){
            searchQueue.push(x-1);
            if(grid[x-1] >grid[x]+1)
                grid[x-1] = grid[x]+1;
        }
        if(x+1<=100000 && visited[x+1]==false){
            searchQueue.push(x+1);
            if(grid[x+1] >grid[x]+1)
                grid[x+1] = grid[x]+1;
        }
        if(x*2<=100000 && visited[x*2]==false){
            searchQueue.push(x*2);
            if(grid[x*2] >grid[x]+1)
                grid[x*2] = grid[x]+1;
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>K;

    for(int i=0;i<100001;i++){
        grid[i] = 100001;
    }

    searchQueue.push(N);
    grid[N]=0;
    BFS();

    cout<<grid[K];
}