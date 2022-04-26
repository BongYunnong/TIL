// https://www.acmicpc.net/problem/14502

// 아무리봐도 좋은 방법이 생각나지 않아서 브루트포스를 사용했다.
// 연구소 크기가 최대 8*8이고, 예제 입력에도 마침 8*8의 예제가 있었기에, 2초 안에 답이 나오면 되는 상황이었다.
// 다행히도 시간초과가 걸리지 않고 바로 맞았다.

#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int grid[9][9];
int resultGrid[9][9];

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

int N,M;
vector<pair<int,int>> viruses;
int wallCount=0;

int Virus(){
    int virusCount=0;
    queue<pair<int,int>> q;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            resultGrid[i][j]=grid[i][j];
        }
    }

    for(int i=0;i<viruses.size();i++){
        q.push({viruses[i].first,viruses[i].second});
        virusCount++;
    }

    while(q.empty()==false){
        int x = q.front().second;
        int y = q.front().first;
        q.pop();

        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx<0 || nx>=M || ny<0 || ny>=N)
                continue;
            if(resultGrid[ny][nx]!=0)
                continue;
            
            q.push({ny,nx});
            virusCount++;
            resultGrid[ny][nx]=2;
        }
    }
    return virusCount;
}

int answer = 100;
void FindPos(int count){
    if(count==3){
        int result= Virus();
        //cout<<"Viruses : "<<N*M-result<<'\n';
        answer = min(answer,result);
        return;
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(grid[i][j]==0){
                grid[i][j]=1;
                FindPos(count+1);
                grid[i][j]=0;
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>grid[i][j];
            if(grid[i][j]==2){
                viruses.push_back({i,j});
            }else if(grid[i][j]==1){
                wallCount++;
            }
        }
    }

    FindPos(0);

    //cout<<N*M<<","<<wallCount<<","<<answer<<'\n';
    cout<<(N*M)-wallCount-answer-3;
}