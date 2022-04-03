// 트리의 지름 구하는 공식
// 1.트리에서 임의의 정점 v1을 잡는다.
// 2.정점 v1에서 가장 먼 정점 v2를 찾는다.
// 3.정점 v2에서 가장 먼 정점 v3를 찾는다.
// 정점 v2와 v3를 연결하면 트리의 지름이 된다.
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int v,target,maxVal;
vector<pair<int,int>> vertexes[100001];

bool visited[100001];

void DFS(int node, int sum){
    visited[node]=true;
    if(maxVal<sum){
        maxVal = sum;
        target= node;
    }
    for(int i=0;i<vertexes[node].size();i++){
        int next = vertexes[node][i].first;
        int weight = vertexes[node][i].second;
        if(!visited[next]){
            DFS(next,sum+weight);
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>v;
    for(int i=0;i<v;i++){
        int vertex;
        cin>>vertex;

        while(true){
            int num1;
            cin>>num1;
            if(num1==-1){
                break;
            }else{
                int length;
                cin>>length;
                vertexes[vertex].push_back({num1,length});
            }
        }
    }

    DFS(1,0);
    fill(visited,visited+100001,false);
    DFS(target,0);

    cout<<maxVal;
}


/* 시간초과 + 틀림
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int V;
int dist[100001];
bool visited[100001];
vector<pair<int,int>> vertexes[100001];

void BFS(int _x){
    queue<int> q;
    q.push(_x);
    for(int i=0;i<=V;i++){
        dist[i]=0;
        visited[i]=false;
    }
    while(q.empty()==false){
        int curr = q.front();
        q.pop();

        visited[curr]=true;
        //cout<<'\n'<<curr<<"__";
        for(int i=0;i<vertexes[curr].size();i++){
            int next = vertexes[curr][i].first;
            int weight = vertexes[curr][i].second;
            
            if(dist[next] < dist[curr]+weight && visited[next]==false){
                dist[next] = dist[curr]+weight;
                q.push(next);
                //cout<<next<<"_";
            }
        }
    }
    //cout<<"\n";
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>V;
    for(int i=0;i<V;i++){
        int vertex;
        cin>>vertex;

        while(true){
            int num1;
            cin>>num1;
            if(num1==-1){
                break;
            }else{
                int length;
                cin>>length;
                vertexes[vertex].push_back({num1,length});
                vertexes[num1].push_back({vertex,length});
            }
        }
    }

    int max=-1;
    // 각 정점에 대해서 모든 정점의 거리를 찾고, 가장 큰 값 도출
    for(int i=1;i<=V;i++){
        BFS(i);

        for(int j=1;j<=V;j++){
            if(max < dist[j]){
                max = dist[j];
                //cout<<"max "<<max;
            }
        }
        //cout<<'\n';
    }
    cout<<max;
}
*/