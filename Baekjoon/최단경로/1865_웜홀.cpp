// https://www.acmicpc.net/problem/1865
// 찾아보니 bfs가 아니라 "벨만포드"알고리즘을 써야한다고 한다.

// 다익스트라는 최단거리를 매번 구해야하기에 priority queue를 사용해야했지만, 이건 그럴 필요가 없다.

// 벨만포드 알고리즘 
// 한 노드에서 다른 노드까지의 최단 거리를 구한다.
// 간선의 가중치가 음수일 때에도 최단거리를 구할 수 있다.
// 다익스트라는 매번 방문하지 않은 노드 중 가장 짧은 거리를 선택하지만, 벨만 포드 알고리즘은 매번 모든 간선을 전부 확인하여 가중치가 음수인 간선도 확인한다.
// 대신 다익스트라보다 느리다.

// 과정
// 출발 노드 설정
// 최단 거리 테이블 초기화
// 다음 과정 정점개수-1번 반복
//      모든 간선 E개를 하나씩 확인
//      각 간선의 비용 계산하여 최단 거리 테이블 갱신
//      만약 음수 간선 순환이 발생하는지 체크하려면 이 과정을 한번 더 수행(최단거리 테이블이 갱신되면 음수 간선 순환 존재-> 처음 시작한 곳은 0일텐데, 더 작은 값으로 갱신이 되었으니 사이클이 있다.)

#include <iostream>
#include <string>
#include <vector>

#define MAX 30000000 
using namespace std;

int N,M,W;
struct edge{
    int s,e,t;
};

bool TimeMachine(int n, vector<edge>edges){
    vector<int> dist(n+1,MAX);

    int s,e,t;
    dist[1]=0;
    for(int i=1;i<N;i++){
        for(int j=0;j<edges.size();j++){
            s=edges[j].s;
            e=edges[j].e;
            t=edges[j].t;
            if(dist[e]>dist[s]+t){
                dist[e]=dist[s]+t;
            }
        }
    }
    
    // 정점 개수-1번만큼 for문을 돌린 후, 다시 한 번 확인을 했을때, 갱신이 된다면 cycle 존재
    for(int j=0;j<edges.size();j++){
        s=edges[j].s;
        e=edges[j].e;
        t=edges[j].t;
        
        // if (Dist[From] == INF) continue;
        // dist[from]이 INF라서 지나치게 되면, 뒤의 cycle의 유무를 판단할 수 없다.
        // 만약 INF인 이유가 단절된 경우라면, 단절된 정점끼리 cycle을 형성했다면, 그 cycle의 값은 알 수 없다.

        if(dist[e]>dist[s]+t){
            return true;
        }
    }
    return false;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int TC;
    cin>>TC;
    int s,e,t;
    for(int i=0;i<TC;i++){
        cin>>N>>M>>W;

        vector<edge> edges;

        for(int j=0;j<M;j++){
            cin>>s>>e>>t;
            edges.push_back({s,e,t});
            edges.push_back({e,s,t});
        }
        for(int j=0;j<W;j++){
            cin>>s>>e>>t;
            edges.push_back({s,e,-t});
        }
        if(TimeMachine(N,edges)){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
}
/* 메모리초과
#include <iostream>
#include <string>
#include <vector>

#define MAX 30000000 
using namespace std;

long long dist[MAX];
vector<pair<pair<int, int>, int> > road;
int N,M,W;
bool TimeMachine(){
    int s,e,t;
    for(int i=1;i<=N;i++){
        for(int j=0;j<road.size();j++){
            s=road[j].first.first;
            e=road[j].first.second;
            t=road[j].second;
            if(dist[e]>dist[s]+t){
                if(i==N){
                    return true;
                }
                dist[e]=dist[s]+t;
            }
        }
    }
    return false;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int TC;
    cin>>TC;
    int s,e,t;
    for(int i=0;i<TC;i++){
        cin>>N>>M>>W;
        road.clear();
        road.resize(N+1);

        for(int j=0;j<M;j++){
            cin>>s>>e>>t;
            road.push_back({{s,e},t});
            road.push_back({{e,s},t});
        }
        for(int j=0;j<W;j++){
            cin>>s>>e>>t;
            road.push_back({{s,e},-t});
        }
        if(TimeMachine()){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
}
*/

/* 인터넷에서 찾은 반례도 다 통과하는데... 
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<pair<int,int>> roads[501];
vector<pair<int,int>> holes[501];
bool visited[501];
bool TimeMachine(int startPoint){
    fill(visited,visited+501,false);
    queue<pair<int,int>> q;
    q.push({startPoint,0});

    bool isStart=true;
    bool founded=false;
    while(q.empty()==false){
        int currPoint = q.front().first;
        int currTime = q.front().second;
        //cout<<"curr "<<currPoint<<','<<currTime<<'\n';
        q.pop();
        if(currPoint==startPoint){
            if(currTime<0){
                // YES
                founded=true;
                //cout<<"YES "<<startPoint<<','<<currTime<<'\n';
            }else{
                // NO
                //cout<<"NO "<<startPoint<<','<<currTime<<'\n';
            }
        }

        if(visited[currPoint]==false || (currPoint==startPoint && isStart)){
            isStart=false;
            visited[currPoint]=true;
            // 도로를 이용하는 경우
            int nextPoint;
            for(int i=0;i<roads[currPoint].size();i++){
                nextPoint = roads[currPoint].at(i).first;
                if(visited[nextPoint]==false|| nextPoint==startPoint){
                    //cout<<"ROAD "<<currTime<<'+'<<roads[currPoint].at(i).second<<'\n';
                    q.push({nextPoint , currTime + roads[currPoint].at(i).second});
                }
            }
            // 웜홀을 이용하는 경우
            for(int i=0;i<holes[currPoint].size();i++){
                nextPoint = holes[currPoint].at(i).first;
                if(visited[nextPoint]==false || nextPoint==startPoint){
                    //cout<<"holes "<<currTime<<'+'<<holes[currPoint].at(i).second<<'\n';
                    q.push({nextPoint , currTime - holes[currPoint].at(i).second});
                }
            }
        }
    }
    return founded;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int TC;
    cin>>TC;
    for(int i=0;i<TC;i++){
        int N,M,W;
        cin>>N>>M>>W;

        for(int j=0;j<501;j++){
            roads[j].clear();
        }
        for(int j=0;j<501;j++){
            holes[j].clear();
        }

        for(int j=0;j<M;j++){
            int s,e,t;
            cin>>s>>e>>t;
            roads[s-1].push_back({e-1,t});
            roads[e-1].push_back({s-1,t});
        }
        
        for(int j=0;j<W;j++){
            int s,e,t;
            cin>>s>>e>>t;
            holes[s-1].push_back({e-1,t});
        }

        bool ans=false;
        for(int j=0;j<N;j++){
            //cout<<"\nnewStart========"<<(j+1)<<"\n";
            ans = TimeMachine(j);
            if(ans==true){
                break;
            }
        }
        if(ans){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
        //cout<<"ENDTEST========\n\n\n\n";
    }
}

/* 41% 틀림..
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<pair<int,int>> roads[501];
vector<pair<int,int>> holes[501];
bool visited[501];
bool TimeMachine(int startPoint){
    fill(visited,visited+501,false);
    queue<pair<int,int>> q;
    q.push({startPoint,0});

    bool founded=false;
    while(q.empty()==false){
        int currPoint = q.front().first;
        int currTime = q.front().second;
        //cout<<"curr "<<currPoint<<','<<currTime<<'\n';
        q.pop();
        if(currPoint==startPoint){
            if(currTime<0){
                // YES
                founded=true;
                //cout<<"YES "<<startPoint<<','<<currTime<<'\n';
            }else{
                // NO
                //cout<<"NO "<<startPoint<<','<<currTime<<'\n';
            }
        }

        if(visited[currPoint]==false){
            visited[currPoint]=true;
            // 도로를 이용하는 경우
            for(int i=0;i<roads[currPoint].size();i++){
                //cout<<"ROAD "<<currTime<<'+'<<roads[currPoint].at(i).second<<'\n';
                q.push({roads[currPoint].at(i).first , currTime + roads[currPoint].at(i).second});
            }
            // 웜홀을 이용하는 경우
            for(int i=0;i<holes[currPoint].size();i++){
                //cout<<"holes "<<currTime<<'+'<<holes[currPoint].at(i).second<<'\n';
                q.push({holes[currPoint].at(i).first , currTime - holes[currPoint].at(i).second});
            }
        }
    }
    return founded;
}

int main(){
    int TC;
    cin>>TC;
    for(int i=0;i<TC;i++){
        int N,M,W;
        cin>>N>>M>>W;

        for(int j=0;j<M;j++){
            roads[j].clear();
        }
        for(int j=0;j<W;j++){
            holes[j].clear();
        }

        for(int j=0;j<M;j++){
            int s,e,t;
            cin>>s>>e>>t;
            roads[s-1].push_back({e-1,t});
            roads[e-1].push_back({s-1,t});
        }
        
        for(int j=0;j<W;j++){
            int s,e,t;
            cin>>s>>e>>t;
            holes[s-1].push_back({e-1,t});
        }

        bool ans=false;
        for(int j=0;j<N;j++){
            ans = TimeMachine(j);
            if(ans==true){
                break;
            }
        }
        if(ans){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
}
*/