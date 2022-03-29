// https://www.acmicpc.net/problem/1707

// 각 테스트케이스에서 정점과 간선이 주어졌을 때 해당 그래프가 두 집합으로 분할했을 때 각 집합에 속한 정점끼리는 인접하지 않을 수 있는 '이분 그래프'인지 확인
// 이분 그래프를 잘못 이해해서 애를 먹었다.

// 틀린 원인 1 : 임의의 점 하나에서부터 BFS를 하면 알아서 처리가 될 것이라 생각했는데, 그런건 아니었나보다
// 틀린 원인 2 : 처음에는 BFS 내부에서 값을 도출하도록 했는데, 연결되지 않은 모든 점에 대해서 처리를 해야하기 때문에 문제가 있었다. 
// 내가 u,v에 대해서만 visited를 0으로 초기화해서 틀린 줄 알았는데 그건 아니었다.

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
 
class Vertex{
public:
    int visited;    // 0: 아직, 1: 첫번째 그룹 2: 두번째 그룹
    vector<int> edges;
};
 
Vertex* graph;
 
int K;
int V,E;
 
void BFS(int _start){
    queue<Vertex> q;
 
    graph[_start].visited=1;
    q.push(graph[_start]);
 
    while(q.empty()==false){
        Vertex currVertex = q.front();
        q.pop();
 
        for(int i=0;i<currVertex.edges.size();i++){
            if(graph[currVertex.edges.at(i)].visited==0){
                if(currVertex.visited==1){
                    graph[currVertex.edges.at(i)].visited= 2;
                }else if(currVertex.visited==2){
                    graph[currVertex.edges.at(i)].visited= 1;
                }else{
                    //cout<<"ERROR : currVertex is not visited\n";
                }
                q.push(graph[currVertex.edges.at(i)]);
            }
        }
    }
}

bool isBinary()
{
    for(int i = 1; i <= V; i++)
    {
        for(int j = 0; j < graph[i].edges.size(); j++)
        {
            if(graph[i].visited == graph[graph[i].edges[j]].visited)
            {
                return false;
            }
        }
    }
    return true;
}
 
 
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
 
    cin>>K;
 
    for(int i=0;i<K;i++){
        cin>>V>>E;
 
        graph = new Vertex[V+1];

        for(int j=0;j<E;j++){
            int u,v;
            cin>>u>>v;
            graph[u].edges.push_back(v);
            graph[u].visited=0;
            graph[v].edges.push_back(u);
            graph[v].visited=0;
        }

        for(int j=1;j<=V;j++){
            if(graph[j].visited==0){
                BFS(j);
            }
        }

        if(isBinary()){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
}

/* 맞은 코드
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
 
class Vertex{
public:
    int visited;    // 0: 아직, 1: 첫번째 그룹 2: 두번째 그룹
    vector<int> edges;
};
 
Vertex* graph;
 
int K;
int V,E;
 
void BFS(int _start){
    queue<Vertex> q;
 
    graph[_start].visited=1;
    q.push(graph[_start]);
 
    while(q.empty()==false){
        Vertex currVertex = q.front();
        q.pop();
 
        for(int i=0;i<currVertex.edges.size();i++){
            if(graph[currVertex.edges.at(i)].visited==0){
                if(currVertex.visited==1){
                    graph[currVertex.edges.at(i)].visited= 2;
                }else if(currVertex.visited==2){
                    graph[currVertex.edges.at(i)].visited= 1;
                }else{
                }
                q.push(graph[currVertex.edges.at(i)]);
            }
        }
    }
}

bool isBinary()
{
    for(int i = 1; i <= V; i++)
    {
        for(int j = 0; j < graph[i].edges.size(); j++)
        {
            if(graph[i].visited == graph[graph[i].edges[j]].visited)
            {
                return false;
            }
        }
    }
    return true;
}
 
 
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
 
    cin>>K;
 
    for(int i=0;i<K;i++){
        cin>>V>>E;
 
        graph = new Vertex[V+1];
        for(int j=0;j<=V;j++){
            graph[j].visited=0;
        }
        for(int j=0;j<E;j++){
            int u,v;
            cin>>u>>v;
            graph[u].edges.push_back(v);
            graph[v].edges.push_back(u);
        }

        for(int j=1;j<=V;j++){
            if(graph[j].visited==0){
                BFS(j);
            }
        }

        if(isBinary()){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
}
*/

/* 75% 에서 틀림
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
 
class Vertex{
public:
    int visited;    // 0: 아직, 1: 첫번째 그룹 2: 두번째 그룹
    vector<int> edges;
};
 
Vertex* graph;
 
int K;
int V,E;
 
void BFS(int _start){
    queue<Vertex> q;
 
    graph[_start].visited=1;
    q.push(graph[_start]);
 
    bool biPartitie=true;
    while(q.empty()==false){
        //cout<<"while"<<endl;
        Vertex currVertex = q.front();
        q.pop();
 
        //cout<<currVertex.visited<<" edge count : "<<currVertex.edges.size()<<'\n';
 
        for(int i=0;i<currVertex.edges.size();i++){
            if(graph[currVertex.edges.at(i)].visited==0){
                if(currVertex.visited==1){
                    graph[currVertex.edges.at(i)].visited= 2;
                }else if(currVertex.visited==2){
                    graph[currVertex.edges.at(i)].visited= 1;
                }else{
                    //cout<<"ERROR : currVertex is not visited\n";
                }
                q.push(graph[currVertex.edges.at(i)]);
                //cout<<"Push : "<<currVertex.edges.at(i)<<" is "<<graph[currVertex.edges.at(i)].visited<<endl;
            }else if(graph[currVertex.edges.at(i)].visited == currVertex.visited){
                //cout<<"Compare : "<<currVertex.edges.at(i)<<" is "<<graph[currVertex.edges.at(i)].visited<<endl;
                biPartitie=false;
                break;
            }else{
                //cout<<"What?  "<<graph[currVertex.edges.at(i)].visited<<endl;
            }
        }
    }
 
    if(biPartitie){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
 
}
 
 
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
 
    cin>>K;
 
    for(int i=0;i<K;i++){
        cin>>V>>E;
 
        graph = new Vertex[V+1];
        int start=-1;
        for(int j=0;j<E;j++){
            int u,v;
            cin>>u>>v;
            start = u;
            graph[u].edges.push_back(v);
            graph[u].visited=0;
            graph[v].edges.push_back(u);
            graph[V].visited=0;
        }
 
        BFS(start);
    }
}
*/