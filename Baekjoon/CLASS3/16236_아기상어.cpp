// https://www.acmicpc.net/problem/16236
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;

int board[22][22];
int check[22][22];

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

int ans = 0, babysize = 2,N,x,y;
int eatFish=0;

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>board[i][j];
            if(board[i][j]==9){
                x=i;
                y=j;
            }
        }
    }
    while(true){
        for(int i=0;i<=N;i++){
            for(int j=0;j<=N;j++){
                check[i][j]=-1;
            }
        }
        check[x][y]=0;
        board[x][y]=0;

        queue<pair<int,int>> q;
        vector<pair<int,int>> fish;

        if(eatFish>=babysize){
            eatFish-=babysize;
            babysize++;
        }
        q.push({x,y});

        while(!q.empty()){
            auto cur = q.front();
            q.pop();

            for(int i=0;i<4;i++){
                int nx = cur.first+dx[i];
                int ny = cur.second+dy[i];

                if(nx<0 || nx>=N || ny<0 || ny>=N)
                    continue;
                
                if(check[nx][ny]!=-1)
                    continue;
                if(board[nx][ny]>babysize)
                    continue;
                else if(board[nx][ny]==babysize || board[nx][ny]==0){
                    check[nx][ny]=check[cur.first][cur.second]+1;
                    q.push({nx,ny});
                }else if(board[nx][ny]<babysize && board[nx][ny]>=1){
                    check[nx][ny]=check[cur.first][cur.second]+1;
                    fish.push_back({nx,ny});
                    q.push({nx,ny});
                }
            }
        }
        if(fish.size()==0){
            cout<<ans<<'\n';
            return 0;
        }
        else if(fish.size()==1){
        }else{
            int minDsit = 1e5;
            for(auto& x : fish){
                minDsit = min(minDsit,check[x.first][x.second]);
            }
            int mincnt=0;
            vector<pair<int,int>> minfish;
            for(auto& x : fish){
                if(minDsit==check[x.first][x.second]){
                    minfish.push_back({x.first,x.second});
                }
            }
            if(minfish.size()!=1){
                sort(minfish.begin(),minfish.end());
            }
            fish=minfish;
        }
        x=fish[0].first;
        y=fish[0].second;
        board[x][y]=0;
        eatFish++;
        ans+=check[x][y];
    }
}


/* 테스트케이스 해봤을 때 하나때고 다 답이 나오고, 그 하나도 내가 직접 해보니 더 잘 나와서 그냥 제출했는데, 틀림

#include<iostream>
#include<queue>
using namespace std;

int grid[21][21];
int search[21][21];
int N;

int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};

int sharkSize=2;
int feedCount=2;
int remainCount=0;

bool checkFish(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j] > 0 && grid[i][j]<sharkSize){
                //cout<<"check : "<<i<<","<<j<<" : "<<grid[i][j]<<" - "<<sharkSize<<'\n';
                return true;
            }
        }
    }
    return false;
}

queue<pair<int,int>> q;
int bfs(pair<int,int> _startPoint,int initVal){
    while (q.empty()==false)
    {
        q.pop();
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            search[i][j]=initVal;
        }
    }
    q.push(_startPoint);

    while(q.empty()==false){
        int x = q.front().first;
        int y=  q.front().second;
        if(remainCount==0){
            //cout<<"Found : "<<search[x][y]<<'\n';
            return search[x][y];
        }else if(checkFish()==false){
            //cout<<"CannotFoundAnymore : "<<search[x][y]<<'\n';
            return search[x][y];
        }

        //cout<<x<<","<<y<<" : "<<search[x][y]<<" sharkSize : "<<sharkSize<<" feedCount"<<feedCount<<" remain : "<<remainCount<<endl;

        q.pop();
        for(int i=0;i<4;i++){
            int nx = dx[i]+x;
            int ny = dy[i]+y;

            if(search[nx][ny]!=initVal){
                continue;
            }
            if(nx<0 || nx>=N || ny<0 || ny>=N)
                continue;

            search[nx][ny]=search[x][y]+1;

            if(grid[nx][ny]==0){
                q.push({nx,ny});
            }else if(grid[nx][ny]<sharkSize){
                grid[nx][ny]=0;
                remainCount--;
                feedCount--;
                if(feedCount<=0){
                    sharkSize++;
                    feedCount=sharkSize;
                }
                return bfs(make_pair(nx,ny),search[nx][ny]);
            }else if(grid[nx][ny]==sharkSize){
                q.push(make_pair(nx,ny));
            }
        }
    }
}

int main(){
    cin>>N;
    pair<int,int> startPoint;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>grid[i][j];
            if(grid[i][j]==9){
                startPoint={i,j};
                grid[i][j]=0;
            }else if(grid[i][j]!=0){
                remainCount++;
            }
        }
    }
    
    feedCount = sharkSize;
    cout<<bfs(startPoint,0)<<'\n';
}

*/

/* DFS로 풀려 한 시도
#include<iostream> 
#include<vector>

using namespace std;

bool visited[21][21];
int grid[21][21];
int N;

int dx[4]={0,-1,1,0};
int dy[4]={1,0,0,-1};

int sharkSize=2;
int remainCount=0;

int time=0;

vector<pair<int,int>> fishes;

int minResult=100000000;
void dfs(pair<int,int> start,int _remainCount, int count){
    if(_remainCount<=0){
        if(minResult>count){
            minResult=count;
        }
        return;
    }

    if(count>minResult){
        return;
    }
    
    for(int i=0;i<4;i++){
        int nx = start.first+dx[i];
        int ny = start.second+dy[i];
        if(nx<0 || nx>=N || ny<0 || ny>=N)
            continue;

        if(grid[nx][ny]==0){
            
        }else if(grid[nx][ny]<sharkSize){
            grid[nx][ny]=0;
            _remainCount--;
        }else if(grid[nx][ny]==sharkSize){

        }else{
            continue;
        }
        dfs({nx,ny},_remainCount,count+1);
    }
}

int main(){
    cin>>N;

    pair<int,int> startPoint;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>grid[i][j];
            if(grid[i][j]==9){
                startPoint=make_pair(i,j);
            }else if(grid[i][j]!=0){
                remainCount++;
                fishes.push_back(startPoint);
            }
        }
    }

    sharkSize=2;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            visited[i][j]=false;
        }
    }

    visited[startPoint.first][startPoint.second]=true;
    dfs(startPoint,remainCount,0);
    sharkSize++;

    cout<<minResult;
}
*/