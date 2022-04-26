// https://www.acmicpc.net/problem/2638

// 치즈가 다행히도 가장자리에 안 놓인다고 해서 방법을 알 수 있었다.
// 가장자리를 다 outside vector에 저장하고, 재귀적으로 outside에서 갈 수 있는 모든 곳을 bfs로 돌아주면 된다
// 주의할 점은 visited 처리를 하는 것, 치즈가 2면이 접촉해야 녹아내리는 것(1면이 접촉하면 녹지 않으므로 잘 처리해야함)이 있다.

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<pair<int,int>> outside;
int grid[101][101];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

int N,M;

bool visited[101][101];

int answer=0;
int cheeze=0;
void MeltingCheeze(int count){
    // 탈출조건
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            visited[i][j]=false;
            if(grid[i][j]>=3){
                grid[i][j]=0;
                cheeze--;
            }else if(grid[i][j]==2){
                grid[i][j]=1;
            }
        }
    }
    if(cheeze<=0){
        answer=count;
        return;
    }


    queue<pair<int,int>> q;
    for(int i=0;i<outside.size();i++){
        q.push({outside[i].first,outside[i].second});
        visited[outside[i].first][outside[i].second]=true;
    }

    while(q.empty()==false){
        int y = q.front().first;
        int x = q.front().second;
        
        q.pop();

        for(int i=0;i<4;i++){
            int ny = y+dy[i];
            int nx = x+dx[i];

            if(nx<0||nx>=M || ny<0 || ny>=N){
                continue;
            }

            // 치즈를 만나면 부패
            if(grid[ny][nx]>0){
                grid[ny][nx]++;
                continue;
            }else if(visited[ny][nx]==false){
                visited[ny][nx]=true;
                q.push({ny,nx});
            }
        }
    }
    MeltingCheeze(count+1);
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>grid[i][j];
            if(i==0 || j==0 || i==N-1 || j==M-1){
                outside.push_back({i,j});
            }else if(grid[i][j]==1){
                cheeze++;
            }
        }
    }
    MeltingCheeze(0);
    cout<<answer;
}