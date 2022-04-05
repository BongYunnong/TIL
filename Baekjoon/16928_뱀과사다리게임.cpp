#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<pair<int,int>> snakes;
vector<pair<int,int>> ladders;

bool visited[101];
int result = 10000;
void bfs(){
    queue<pair<int,int>> q;
    q.push({1,0});
    visited[1]=true;

    while (q.empty()==false)
    {
        int start = q.front().first;
        int count = q.front().second;
        q.pop();
        if(start==100){
            result = min(result,count);
            break;
        }

        for(int i=1;i<=6;i++){
            int next = start+i;
            if(next>100 || visited[next]){
                continue;
            }
            visited[next]=true;
            bool founded=false;
            for(int j=0;j<snakes.size();j++){
                if(snakes[j].first==next){
                    q.push({snakes[j].second,count+1});
                    founded=true;
                    break;
                }
            }
            for(int j=0;j<ladders.size();j++){
                if(ladders[j].first==next){
                    q.push({ladders[j].second,count+1});
                    founded=true;
                    break;
                }
            }
            if(founded==false){
                q.push({next,count+1});
            }
        }
    }
    
}

int N,M;
int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        int x,y;
        cin>>x>>y;
        ladders.push_back({x,y});
    }
    for(int i=0;i<M;i++){
        int u,v;
        cin>>u>>v;
        snakes.push_back({u,v});
    }
    bfs();
    cout<<result;
}

/* dfs 쓰려했는데... 틀림
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<pair<int,int>> snakes;
vector<pair<int,int>> ladders;

bool visited[101][6];
int result=0x3f3f3f3f;
void FindPath(int _start,int count,int index){
    if(count>result || visited[_start][index]==true || _start>100){
        return;
    }
    cout<<_start<<"_"<<count<<'\n';
    if(_start==100){
        if(result>=count){
            result=count;
        }
        return;
    }

    for(int i=0;i<snakes.size();i++){
        if(snakes[i].first==_start){
            _start = snakes[i].second;
            break;
        }
    }
    for(int i=0;i<ladders.size();i++){
        if(ladders[i].first==_start){
            _start = ladders[i].second;
            break;
        }
    }

    for(int i=6;i>=1;i--){
        visited[_start][i]=true;
        FindPath(_start+i,count+1,i);
    }
}

int N,M;
int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        int x,y;
        cin>>x>>y;
        ladders.push_back({x,y});
    }
    for(int i=0;i<M;i++){
        int u,v;
        cin>>u>>v;
        snakes.push_back({u,v});
    }
    FindPath(1,0,0);
    cout<<result;
}
*/