// https://www.acmicpc.net/problem/7562

#include<iostream>
#include<queue>
using namespace std;

int T;
int I;

int grid[301][301];
bool visited[301][301];
int dx[8]={1,2,2,1,-1,-2,-2,-1};
int dy[8]={2,1,-1,-2,-2,-1,1,2};
void BFS(int _startX,int _startY, int _endX, int _endY){
    queue<pair<int,int>> q;
    q.push({_startX,_startY});

    while(q.empty()==false){
        int X = q.front().first;
        int Y = q.front().second;

        if(X==_endX && Y == _endY){
            return;
        }
        q.pop();

        for(int i=0;i<8;i++){
            int nx = X+dx[i];
            int ny = Y+dy[i];

            if(nx >=0 && nx < I && ny >=0 && ny < I 
                && visited[nx][ny]==false){
                visited[nx][ny]=true;
                q.push({nx,ny});
                grid[nx][ny] = grid[X][Y]+1;
            }
        }
    }
}

int main(){
    cin>>T;

    for(int i=0;i<T;i++){
        cin>>I;

        pair<int,int> start;
        pair<int,int> end;

        cin>>start.first;
        cin>>start.second;
        cin>>end.first;
        cin>>end.second;

        for(int j=0;j<I;j++){
            for(int k=0;k<I;k++){
                grid[j][k]=0;
                visited[j][k]=false;
            }
        }

        BFS(start.first,start.second,end.first,end.second);

        cout<<grid[end.first][end.second]<<'\n';
    }
}