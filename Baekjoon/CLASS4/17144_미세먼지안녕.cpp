
// 첫 번째로 이상했던 것은 2만큼 값이 줄어들었던 것 -> 공기 청정기의 -1을 2번 제외해야함
// 두 번째로 이상했던 것은 x,y를 row, column으로 사용해서 뒤죽박죽이었던 것
// 마지막은 공기청정기 아랫부분에 index를 잘못 넣었다.

#include<iostream>
#include<vector>
using namespace std;

vector<pair<int,int>> washer;
vector<pair<int,int>> dusts;

int grid[51][51];
int dustPlus[51][51];

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int R,C,T;
    cin>>R>>C>>T;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            cin>>grid[i][j];
            if(grid[i][j]==-1){
                washer.push_back({i,j});
            }
        }
    }

    while(T--){
        dusts.clear();
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                if(grid[i][j]>=5)
                    dusts.push_back({i,j});
            }
        }

        // 확산
        for(int i=0;i<dusts.size();i++){
            int y = dusts[i].first;
            int x = dusts[i].second;

            // 더 이상 확산될만한 먼지가 없거나, 공기청정기이거나, 빈 공간이라면 무시
            if(grid[y][x]<5)
                continue;
            int dustWeight = grid[y][x]/5;
            for(int k=0;k<4;k++){
                int nx = x+dx[k];
                int ny = y+dy[k];

                // 밖으로 나가는 것 무시
                if(nx<0 || nx>=C || ny <0 || ny>=R)
                    continue;
                // 공기 청정기인 것 무시
                if(grid[ny][nx]==-1)
                    continue;
                
                dustPlus[ny][nx]+=dustWeight;
                dustPlus[y][x]-=dustWeight;
            }
        }

        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                grid[i][j] += dustPlus[i][j];
                dustPlus[i][j]=0;
            }
        }
        /*
        cout<<"\n---dust\n";
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                cout<<grid[i][j]<<' ';
            }
            cout<<'\n';
        }
        */

        // 공기청정기
        for(int i=0;i<washer.size();i++){
            if(i==0){
                // 반시계방향
                int y = washer[i].first;
                int x = washer[i].second;
                for(int j= y-1;j>0;j--){
                    //cout<<j<<x<<":"<<grid[j][x]<<"_"<<(j-1)<<x<<":"<<grid[j-1][x]<<'\n';
                    grid[j][0] = grid[j-1][0];
                }
                for(int j= 0;j<C-1;j++){
                    grid[0][j] = grid[0][j+1];
                }
                for(int j= 1;j<=y;j++){
                    grid[j-1][C-1] = grid[j][C-1];
                }
                for(int j= C-1;j>1;j--){
                    grid[y][j] = grid[y][j-1];
                }
                grid[y][1]=0;
            }else{
                // 시계방향
                
                int y = washer[i].first;
                int x = washer[i].second;
                for(int j= y+1;j<R-1;j++){
                    grid[j][0] = grid[j+1][0];
                }
                for(int j= 0;j<C-1;j++){
                    grid[R-1][j] = grid[R-1][j+1];
                }
                for(int j= R-1;j>=y;j--){
                    grid[j][C-1] = grid[j-1][C-1];
                }
                for(int j= C-1;j>1;j--){
                    grid[y][j] = grid[y][j-1];
                }
                grid[y][1]=0;
            }
        }
        /*
        cout<<"\n---washer\n";
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                cout<<grid[i][j]<<' ';
            }
            cout<<'\n';
        }
        */
        
    }
    int answer=0;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(grid[i][j]>0)
                answer+=grid[i][j];
        }
    }
    cout<<answer;
}