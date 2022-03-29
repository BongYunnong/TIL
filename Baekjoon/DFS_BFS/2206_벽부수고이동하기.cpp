// https://www.acmicpc.net/problem/2206

// N X M 행렬의 grid에서 벽을 최대 하나 부수고 끝까지 가는 최소 거리

// visited를 3차원으로 만들어서 그곳에 도착하기까지 벽을 부수지 않은 경우와(0) 부순 경우(1)를 각각 체크해준다.
// 여기서 끝나는 것이 아니라 queue도 원소를 3가지 가져야한다. 탐색하려는 요소가 벽을 부쉈는지 아닌지 확인해야하기 때문이다.

// 나는 3차원 배열에 약한 것 같다.
// 이렇게 보면 이해는 되긴 하는데 이것을 직접 구현하는 것은 너무 어렵다.
// 내가 너무 무식하게 푸는 것일까.


#include<iostream>
#include<string>
#include<queue>
#include<tuple>
using namespace std;
int N,M;
int grid[1001][1001];

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int visited[1001][1001][2];

queue<tuple<int,int,int>> q;

int result=-1;
void BFS(){
    q.push(make_tuple(0,0,0));
    while(q.empty()==false){
        int x = get<0>(q.front());
        int y = get<1>(q.front());
        int count = get<2>(q.front());
        
        //cout<<"Xy : "<<x<<","<<y<<endl;
        q.pop();

        if(x==N-1 && y==M-1){
            result =  (visited[N-1][M-1][count]+1);
            return;
        }

        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx >=0 && nx < N && ny >=0 && ny<M){
                if(visited[nx][ny][count]==false){
                    // count는 x,y까지 벽을 부쉈는지, 안 부쉈는지
                    if(grid[nx][ny]<=0){
                        // 벽이 없을 떄
                        q.push(make_tuple(nx,ny,count));
                        visited[nx][ny][count] = visited[x][y][count]+1;
                    }else if(grid[nx][ny]==1){
                        // 벽이 있을때
                        if(count==0){
                            // 지금까지 벽을 안 부수고 왔으면
                            // 벽 부수고 이동
                            q.push(make_tuple(nx,ny,1));
                            visited[nx][ny][1] = visited[x][y][0]+1;
                        }
                    }
                }
            }
        }
    }

    result=-1;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0;i<N;i++){
        string input;
        cin>>input;
        for(int j=0;j<M;j++){
            grid[i][j] = input[j]-'0';
        }
    }
    BFS();
    
    cout<< result;
}

/* 21퍼 틀림..
#include<iostream>
#include<string>
#include<queue>
using namespace std;
int N,M;
pair<int,int> grid[1001][1001];

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
bool visited[1001][1001];

queue<pair<int,int>> q;

int result=0;
void BFS(){
    
    q.push({0,0});
    while(q.empty()==false){
        int x = q.front().first;
        int y = q.front().second;
        //cout<<"Xy : "<<x<<","<<y<<endl;
        q.pop();

        if(x==N-1 && y==M-1){
            result =  (grid[N-1][M-1].first-1)*-1;
            return;
        }

        for(int i=0;i<4;i++){
            if(x+dx[i] >=0 && x+dx[i] < N && y+dy[i] >=0 && y+dy[i]<M && visited[x+dx[i]][y+dy[i]]==false){
                if(grid[x+dx[i]][y+dy[i]].first<=0){
                    if(grid[x+dx[i]][y+dy[i]].first > grid[x][y].first-1){
                        // progress 계산하고, 지금까지 부수고 이동했는지 아닌지는 그대로 대입
                        q.push({x+dx[i],y+dy[i]});
                        visited[x+dx[i]][y+dy[i]]=true;
                        grid[x+dx[i]][y+dy[i]].first = grid[x][y].first-1;
                        grid[x+dx[i]][y+dy[i]].second = grid[x][y].second;
                    }else if(grid[x+dx[i]][y+dy[i]].first == grid[x][y].first-1){
                        // 이동 거리가 같으면 안 부수고 들어간 경로로 변경
                        q.push({x+dx[i],y+dy[i]});
                        visited[x+dx[i]][y+dy[i]]=true;
                        if(grid[x+dx[i]][y+dy[i]].second==0 || grid[x][y].second==0){
                            grid[x+dx[i]][y+dy[i]].second==0;
                        }
                    }
                }else{
                    // 벽이 있을 때
                    if(grid[x+dx[i]][y+dy[i]].second==0 && grid[x][y].second==0){
                        // 아직 안 부서졌으면
                        // 부수고 이동
                        q.push({x+dx[i],y+dy[i]});
                        visited[x+dx[i]][y+dy[i]]=true;
                        grid[x+dx[i]][y+dy[i]].first = grid[x][y].first-1;
                        grid[x+dx[i]][y+dy[i]].second = 1;
                    }
                }
            }
        }
    }

    result=-1;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0;i<N;i++){
        string input;
        cin>>input;
        for(int j=0;j<M;j++){
            grid[i][j].first = input[j]-'0';
            grid[i][j].second = 0;
            visited[i][j]=false;
        }
    }
    BFS();
    
    cout<< result;
}
*/

/* 메모리 초과..
#include<iostream>
#include<string>
#include<queue>
using namespace std;
int N,M;
pair<int,int> grid[1001][1001];

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
bool visited[1001][1001];

queue<pair<int,int>> q;

int result=0;
void BFS(){
    
    q.push({0,0});
    while(q.empty()==false){
        int x = q.front().first;
        int y = q.front().second;
        //cout<<"Xy : "<<x<<","<<y<<endl;
        q.pop();
        visited[x][y]=true;

        if(x==N-1 && y==M-1){
            result =  (grid[N-1][M-1].first-1)*-1;
            return;
        }

        for(int i=0;i<4;i++){
            if(x+dx[i] >=0 && x+dx[i] < N && y+dy[i] >=0 && y+dy[i]<M && visited[x+dx[i]][y+dy[i]]==false){
                if(grid[x+dx[i]][y+dy[i]].first<=0){
                    if(grid[x+dx[i]][y+dy[i]].first > grid[x][y].first-1){
                        // progress 계산하고, 지금까지 부수고 이동했는지 아닌지는 그대로 대입
                        q.push({x+dx[i],y+dy[i]});
                        grid[x+dx[i]][y+dy[i]].first = grid[x][y].first-1;
                        grid[x+dx[i]][y+dy[i]].second = grid[x][y].second;
                    }else if(grid[x+dx[i]][y+dy[i]].first == grid[x][y].first-1){
                        // 이동 거리가 같으면 안 부수고 들어간 경로로 변경
                        q.push({x+dx[i],y+dy[i]});
                        if(grid[x+dx[i]][y+dy[i]].second==0 || grid[x][y].second==0){
                            grid[x+dx[i]][y+dy[i]].second==0;
                        }
                    }
                }else{
                    // 벽이 있을 때
                    if(grid[x+dx[i]][y+dy[i]].second==0 && grid[x][y].second==0){
                        // 아직 안 부서졌으면
                        // 부수고 이동
                        q.push({x+dx[i],y+dy[i]});
                        grid[x+dx[i]][y+dy[i]].first = grid[x][y].first-1;
                        grid[x+dx[i]][y+dy[i]].second = 1;
                    }
                }
            }
        }
    }

    result=-1;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0;i<N;i++){
        string input;
        cin>>input;
        for(int j=0;j<M;j++){
            grid[i][j].first = input[j]-'0';
            grid[i][j].second = 0;
            visited[i][j]=false;
        }
    }
    BFS();
    
    cout<< result;
}
*/