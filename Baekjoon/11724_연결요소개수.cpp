#include<iostream>
#include<vector>
#include<queue>
using namespace std;

bool visited[1001];
vector<int> vertexes[1001];
int N,M;

int count=0;
void BFS(int start){
    queue<int> q;
    q.push(start);
    while(q.empty()==false){
        int curr = q.front();
        visited[curr]=true;
        q.pop();

        for(int i=0;i<vertexes[curr].size();i++){
            if(visited[vertexes[curr].at(i)]==false){
                q.push(vertexes[curr].at(i));
                visited[vertexes[curr].at(i)]=true;
            }
        }
    }

    count++;
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0;i<M;i++){
        int u,v;
        cin>>u>>v;

        vertexes[u].push_back(v);
        vertexes[v].push_back(u);
    }

    for(int i=1;i<=N;i++){
        if(visited[i]==false){
            BFS(i);
        }
    }
    cout<<count;
}