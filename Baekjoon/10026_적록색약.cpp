// https://www.acmicpc.net/problem/10026
// 뭔가 이렇게 푸는게 맞는가 싶지만 일단 맞긴 함..
// 다른 답을 보니 BFS, visited 하나로 하긴 했지만 한번 끝내고 초기화하는 작업이 필요함(+적록색약일때는 grid자체를 R->G로 바꿔줌)

#include<iostream>
#include<string>
#include<queue>
using namespace std;

int N;
char grid[101][101];

int visited[101][101];
int visited2[101][101];

int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

int count=0;
int count2=0;

void bfs(int _startX,int _startY){
    queue<pair<int,int>> q;
    q.push({_startX,_startY});
    visited[_startX][_startY]=grid[_startX][_startY];
    //cout<<grid[_startX][_startY]<<'\n'<<'\n';

    while(q.empty()==false){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        //cout<<x<<','<<y<<'\n';
        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];

            if(0<=nx && nx<N && 0<=ny && ny<N
                && visited[nx][ny]==0 && grid[nx][ny]==grid[_startX][_startY]){
                q.push({nx,ny});
                visited[nx][ny]=grid[nx][ny];
            }
        }
    }
    count++;
}


void bfs2(int _startX,int _startY){
    queue<pair<int,int>> q;
    q.push({_startX,_startY});
    visited2[_startX][_startY]=grid[_startX][_startY];
    //cout<<grid[_startX][_startY]<<'\n'<<'\n';

    while(q.empty()==false){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        //cout<<x<<','<<y<<'\n';
        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];

            if(0<=nx && nx<N && 0<=ny && ny<N
                && visited2[nx][ny]==0 
                && (grid[nx][ny]==grid[_startX][_startY]
                    || (grid[nx][ny]=='G'&&grid[_startX][_startY]=='R')
                    || (grid[nx][ny]=='R'&&grid[_startX][_startY]=='G'))){
                q.push({nx,ny});
                visited2[nx][ny]=grid[nx][ny];
            }
        }
    }
    count2++;
}

void Part1(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(visited[i][j]==0){
                bfs(i , j);
            }
        }
    }
    cout<<count;
}
void Part2(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(visited2[i][j]==0){
                bfs2(i , j);
            }
        }
    }
    cout<<count2;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;
    for(int i=0;i<N;i++){
        string tmp;
        cin>>tmp;
        for(int j=0;j<N;j++){
            grid[i][j]=tmp[j];
        }
    }
    Part1();
    cout<<' ';
    Part2();
}