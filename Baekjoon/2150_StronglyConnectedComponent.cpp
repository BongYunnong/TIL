#include<iostream>
#include<stack>
#include<algorithm>
#include<vector>
using namespace std;

int parents[10001];
bool finished[10001];
vector<int> grid[10001];
int id;
vector<vector<int>> SCC;
stack<int> s;
int dfs(int _index){
    parents[_index] = ++id;
    s.push(_index);

    int parent = parents[_index];
    for(int i=0;i<grid[_index].size();i++){
        int neighbour = grid[_index][i];
        if(parents[neighbour]==0){
            parent = min(parent, dfs(neighbour));
        }else if(finished[neighbour]==false){
            parent = min(parent, parents[neighbour]);
        }
    }

    if(parent == parents[_index]){
        vector<int> scc;
        while(true){
            int curr = s.top();
            s.pop();
            scc.push_back(curr);
            finished[curr]=true;
            if(curr==_index){
                break;
            }
        }
        sort(scc.begin(),scc.end());
        SCC.push_back(scc);
    }
    return parent;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int V,E;
    cin>>V>>E;
    for(int i=0;i<E;i++){
        int a,b;
        cin>>a>>b;

        grid[a].push_back(b);
    }
    for(int i=1;i<=V;i++){
        if(parents[i]==0){
            dfs(i);
        }
    }

    sort(SCC.begin(),SCC.end());
    cout<< SCC.size()<<'\n';
    for(int i=0;i<SCC.size();i++){
        for(int j=0;j<SCC[i].size();j++){
            cout<<SCC[i].at(j)<<' ';
        }
        cout<<-1<<' ';
        cout<<'\n';
    }
}