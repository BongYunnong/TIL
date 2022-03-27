// https://www.acmicpc.net/problem/7576


#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int grid[1001][1001];
int N,M;

int result=0;
queue<pair<int,int>> searchQ;

void BFS(){
    while(searchQ.empty()==false){
        int x  = searchQ.front().second;
        int y  = searchQ.front().first;
        searchQ.pop();
        //cout<<"xy _ "<<x<<','<<y<<endl;
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(abs(i)+abs(j)>=2){
                    continue;
                }
                if(x+i>= 0 && x+i < M && y+j>=0 && y+j < N
                    && grid[y+j][x+i]==0){
                    //cout<<"xy_"<<(x+i)<<","<<(y+j)<<endl;
                    searchQ.push({y+j,x+i});
                    grid[y+j][x+i] = grid[y][x]+1;
                    //cout<<"day_"<<day[x+i][y+j];
                }
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    cin>>M>>N;

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>grid[i][j];

            if(grid[i][j]==1){
                searchQ.push({i,j});
            }
        }
    }

    if(searchQ.size()>0){
        BFS();
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(grid[i][j]==0){
                cout<<"-1";
                return 0;
            }
            if(result<grid[i][j])
                result = grid[i][j];
        }
    }
    cout<<result-1;
}


/* 틀린 코드 -> 예시는 결과값이 잘 나오는데, 왜 틀렸는지 모르겠음 -> 아무래도 x축, y축을 헷갈려서 그런것이 아닐까.
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

vector<pair<int,int>> inputs;


int grid[1001][1001];
bool visited[1001][1001];
int day[1001][1001];
int N,M;

int result=-1;
int count=0;
queue<pair<int,int>> searchQ;

void BFS(int _x,int _y){
    visited[_x][_y]=true;
    day[_x][_y]++;
    result = max(result,day[_x][_y]);

    while(searchQ.empty()==false){
        int x  = searchQ.front().first;
        int y  = searchQ.front().second;
        searchQ.pop();
        //cout<<"xy _ "<<x<<','<<y<<endl;
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(abs(i)+abs(j)!=1){
                    continue;
                }
                if(x+i>= 0 && x+i < N && y+j>=0 && y+j < M
                    && visited[x+i][y+j]==false
                    && grid[x+i][y+j]==0){
                    //cout<<"xy_"<<(x+i)<<","<<(y+j)<<endl;
                    visited[x+i][y+j]=true;
                    count--;
                    searchQ.push({x+i,y+j});
                    day[x+i][y+j] = day[x][y]+1;
                    //cout<<"day_"<<day[x+i][y+j];
                    if(result<day[x+i][y+j])
                        result = day[x+i][y+j];
                    //cout<<"RES_"<<result<<endl;
                }
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    cin>>M>>N;

    bool canStart=false;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>grid[i][j];

            if(grid[i][j] == 0){
                count++;
            }
            if(grid[i][j]==1){
                canStart=true;
                inputs.push_back({i,j});
                searchQ.push({i,j});
            }
        }
    }

    if(inputs.size()>0){
        BFS(inputs[0].first,inputs[0].second);
    }
    if(canStart){
        if(count==0){
            cout<<result-1;
        }else{
            cout<<-1;
        }
    }else{
        cout<<-1;
    }
    //cout<<"Count : "<<count<<'\n';

}
*/