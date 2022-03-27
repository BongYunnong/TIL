// https://www.acmicpc.net/problem/2178
// N X M 크기의 배열에서 1인 곳만 탐색할 수 있다 했을때, 0,0에서 N-1,M-1로 가는 최소 거리


// BFS를 구현하려했는데 실패했다.
// 좀 더 익숙해져야한다. queue를 쓰는 것만 아는 것으로는 부족하다.

#include<iostream>
#include<string>
#include<queue>

using namespace std;

int N,M;
int grid[101][101];
bool visited[101][101];
int count[101][101]={0};


void BFS(int _x,int _y){
    visited[_x][_y]=true;
    count[_x][_y]++;

    queue<pair<int,int>> searchQueue;
    searchQueue.push({_x,_y});
    while(searchQueue.empty()==false){
        int x = searchQueue.front().first;
        int y = searchQueue.front().second;

        searchQueue.pop();

        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if((i==0 && j==0) || (abs(i)+abs(j)!=1)){
                    continue;
                }
                if(x+i >=0 && x+i<N && y+j >=0 && y+j < M
                    && visited[x+i][y+j]==false
                    && grid[x+i][y+j]==1){
                        visited[x+i][y+j]=true;
                        searchQueue.push({x+i,y+j});
                        count[x+i][y+j]= count[x][y]+1;
                    }
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N>>M;

    for(int i=0;i<N;i++){
        string input;
        cin>>input;
        for(int j=0;j<M;j++){
            grid[i][j]=input[j]-'0';
        }
    }

    BFS(0,0);

    cout<<count[N-1][M-1];
}

// DFS로 풀려 했는데, 이러면 시간초과가 된다고 한다.
// 그래서 BFS로 풀어야한다.
/* 시간초과
#include<iostream>
#include <string>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> results;
int N,M;
int grid[101][101];

void DFS(int _x,int _y,int _count){
    if(_x==N-1 && _y==M-1){
        //cout<<_count+1<<'\n';
        results.push_back(_count+1);
        return;
    }
    if(grid[_x][_y]!=1){
        return;
    }
    //cout<<"xy : "<<_x<<","<<_y<<endl;

    if(_y+1<M){
        grid[_x][_y] = 2;
        DFS(_x,_y+1,_count+1);
        grid[_x][_y] = 1;
    }
    if(_x+1<N){
        grid[_x][_y] = 2;
        DFS(_x+1,_y,_count+1);
        grid[_x][_y] = 1;
    }
    if(0<= _x-1){
        grid[_x][_y] = 2;
        DFS(_x-1,_y,_count+1);
        grid[_x][_y] = 1;
    }
    if(0<= _y-1){
        grid[_x][_y] = 2;
        DFS(_x,_y-1,_count+1);
        grid[_x][_y] = 1;
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N>>M;

    for(int i=0;i<N;i++){
        string input;
        cin>>input;
        for(int j=0;j<M;j++){
            grid[i][j]=input[j]-'0';
        }
    }

    DFS(0,0,0);

    sort(results.begin(),results.end());

    if(results.size()>0)
        cout<<results[0];
}
*/