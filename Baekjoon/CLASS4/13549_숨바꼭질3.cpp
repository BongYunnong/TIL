// https://www.acmicpc.net/problem/13549
// dp문제인 줄 알았는데, bfs로 풀 수 있었다.
// 그냥 간단한 bfs문제이다. currPos-1,currPos+1, currPos*2를 queue에 넣어주면 되는데,
// 처음에 헤맸던 것은 저 3개의 연산을 하면서 현재의 위치가 어디인지를 어떻게 알려주는가였다.
// 이것은 bfs를 통해 queue에 다음 위치를 넣어주어서, 전달하는 방식으로 구현이 된다.

#include<iostream>
#include<queue>
using namespace std;

int grid[200100];
bool visited[200100];

int N,K;
void bfs(){
    queue<int> q;
    q.push(N);
    grid[N]=0;
    while(q.empty()==false){
        int currPos = q.front();
        q.pop();
        if(visited[currPos]==false){
            visited[currPos]=true;
            //cout<<currPos<<" ," <<grid[currPos]<<'\n';
            if(currPos==K){
                return;
            }
            if(currPos>0){
                grid[currPos-1]= min(grid[currPos-1],grid[currPos]+1);
                q.push(currPos-1);
            }
            if(currPos<100000){
                grid[currPos+1]= min(grid[currPos+1],grid[currPos]+1);
                q.push(currPos+1);
            }
            
            if(currPos<=100000){
                grid[currPos*2] = min(grid[currPos*2],grid[currPos]);
                q.push(currPos*2);
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>K;

    fill(grid,grid+200100,1000000);

    bfs();
    cout<<grid[K];
}