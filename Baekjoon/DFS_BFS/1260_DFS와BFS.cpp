#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

vector<int> dots[1001];
int N,M,V;


bool DFSVisited[1001];
bool BFSVisited[1001];

void DFS(int index){
    if(DFSVisited[index]){
        return;
    }
    cout<<index<<' ';
    DFSVisited[index]=true;
    for(int i=0;i<dots[index].size();i++){
        if(dots[index][i]>0 && DFSVisited[dots[index][i]]==false){
            DFS(dots[index][i]);
        }
    }
}

void BFS(int index){
    queue<int> bfsQueue;
    BFSVisited[index]=true;

    bfsQueue.push(index);
    while(bfsQueue.empty()==false){
        int tmp = bfsQueue.front();
        bfsQueue.pop();
        cout<<tmp<<' ';
        for(int i=0;i<dots[tmp].size();i++){
            int next = dots[tmp][i];
            if(BFSVisited[next]==false){
                BFSVisited[next]=true;
                bfsQueue.push(next);
            }
        }
    }
}

int main(){
    cin>>N>>M>>V;

    for(int i=0;i<M;i++){
        int x,y;
        cin>>x>>y;

        dots[x].push_back(y);
        dots[y].push_back(x);
    }

    for(int i=0;i<M;i++){
        sort(dots[i].begin(),dots[i].end());
    }

    DFS(V);
    cout<<'\n';
    BFS(V);
}