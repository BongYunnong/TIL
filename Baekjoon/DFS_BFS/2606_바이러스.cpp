// https://www.acmicpc.net/problem/2606
// 컴퓨터에 바이러스가 퍼져서 네트워크상 연결된 다른 컴퓨터들도 감염이 된다.
// 1번 컴퓨터가 바이러스에 걸렸을 때 1번 컴퓨터를 통해 바이러스에 걸리게 되는 컴퓨터의 수 출력

// 와우! BFS구현 안 보고 풀었다! -> 알고보니 DFS였네..
// 간단하게 생각하면, 연결된 것에 하나씩 들어가본다고 생각하면 된다.

#include<iostream>
#include<vector>
using namespace std;

vector<int> computers[101];
bool visited[101];
int N,T;

void BFS(int index){
    if(visited[index]){
        return;
    }

    visited[index]=true;

    for(int i=0;i<computers[index].size();i++){
        BFS(computers[index].at(i));
    }
}

int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        visited[i]=false;
    }
    cin>>T;
    for(int i=1;i<=T;i++){
        int x,y;
        cin>>x>>y;
        computers[x].push_back(y);
        computers[y].push_back(x);
    }

    BFS(1);

    int ans=0;
    for(int i=1;i<=N;i++){
        if(visited[i])
            ans++;
    }
    // 컴퓨터 1번은 제외해야하므로 -1
    cout<<ans-1;
}