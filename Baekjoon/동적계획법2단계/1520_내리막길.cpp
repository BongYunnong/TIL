// https://www.acmicpc.net/problem/1520

#include<iostream>
using namespace std;

int N,M;
int grid[501][501];
int visited[501][501];

int dy[4]={0,0,-1,1};
int dx[4]={-1,1,0,0};

int DFS(int x,int y){
    if(x==N-1 && y==M-1)
        return 1;
    if(visited[x][y]!=-1){
        return visited[x][y];
    }

    visited[x][y]=0;
    for(int i=0;i<4;i++){
        int nx = x+dx[i];
        int ny = y+dy[i];

        if(nx<0 || ny<0 || nx>=N || ny>=M ){
            continue;
        }

        if(grid[nx][ny]<grid[x][y]){
            visited[x][y] = visited[x][y] + DFS(nx,ny);
        }
    }
    return visited[x][y];
}

int main(){
    cin>>N>>M;

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>grid[i][j];
            visited[i][j]=-1;
        }
    }
    
    cout<<DFS(0,0);
}
/* BFS - 실패
#include<iostream>
#include<queue>
using namespace std;

int N,M;
int grid[501][501];
int visited[501][501];

int dy[4]={0,0,-1,1};
int dx[4]={-1,1,0,0};

unsigned long long count=0;
void bfs(){
    queue<pair<int,int>> q;
    q.push({0,0});

    while(q.empty()==false){
        int y = q.front().first;
        int x = q.front().second;
        visited[y][x]++;
        q.pop();

        if(y==M-1 && x==N-1){
            count+=visited[y][x];
        }else{
            for(int i=0;i<4;i++){
                int ny = y+dy[i];
                int nx = x+dx[i];

                if(nx<0 || nx>=N || ny<0 || ny>=M){
                    continue;
                }

                if(grid[ny][nx]<grid[y][x]){
                    if(visited[ny][nx]==0){
                        q.push({ny,nx});
                    }else{
                        visited[ny][nx]++;
                    }
                }
            }
        }
    }
}

int main(){
    cin>>M>>N;

    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin>>grid[i][j];
        }
    }
    bfs();

    
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cout<<visited[i][j]<<' ';
        }
        cout<<'\n';
    }
    
    cout<<count;
}
*/