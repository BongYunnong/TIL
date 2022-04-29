// https://www.acmicpc.net/problem/14938

// 내가 BFS로 구현한거 ideone에서 실행해보니 여기서 실행한 것과 다르게 나옴

// 다익스트라
// 근데 내가 BFS한거랑 크게 차이 없지 않나...?

/*
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<pair<int,int>> spots[101];
int treasure[101];
int n,m,r;

int dist[101];

int SerachTreasure(int _start){
    queue<int> q;
    int result=0;

    for(int i=1;i<=n;i++){
        dist[i]=987654321;
    }

    q.push(_start);
    dist[_start]=0;

    while(q.empty()==false){
        int curr = q.front();
        int currWeight = dist[curr];
        q.pop();

        for(int i=0;i<spots[curr].size();i++){
            int next = spots[curr].at(i).first;
            int weight = spots[curr].at(i).second;

            if(dist[next] > weight+currWeight){
                dist[next]=weight+currWeight;
                q.push(next);
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(dist[i]<=m){
            result+=treasure[i];
        }
    }

    return result;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>n>>m>>r;

    for(int i=1;i<=n;i++){
        cin>> treasure[i];
    }

    for(int i=0;i<r;i++){
        int a,b,c;
        cin>>a>>b>>c;
        spots[a].push_back({b,c});
        spots[b].push_back({a,c});
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        ans = max(ans,SerachTreasure(i));
    }
    cout<<ans;
}
*/

/*
// 플로이드-워셜
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int grid[101][101];
int treasure[101];
int n,m,r;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>n>>m>>r;

    for(int i=1;i<=n;i++){
        cin>> treasure[i];
        for(int j=1;j<=n;j++){
            if(i!=j){
                grid[i][j]=987654321;
            }
        }
    }

    for(int i=0;i<r;i++){
        int a,b,c;
        cin>>a>>b>>c;
        grid[a][b]=c;
        grid[b][a]=c;
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(grid[i][j]>grid[i][k]+grid[k][j]){
                    grid[i][j]=grid[i][k]+grid[k][j];
                }
            }
        }
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        int result=0;
        for(int j=1;j<=n;j++){
            if(grid[i][j]<=m){
                result+=treasure[j];
            }
        }
        ans = max(ans,result);
    }
    cout<<ans;
}
*/

// 단순한 BFS로도 풀 수 있을 줄 알았는데...?
// 왜 vs code랑 ideone이랑 답 다르게 나옴?
// 뭐임!!!!!! 대체 뭐임!!!!!!!!!!
/*
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<pair<int,int>> spots[101];
int treasure[101];
int n,m,r;


int SerachTreasure(int _start){
    bool visited[n+1];
    queue<pair<int,int>> q;

    int result=0;
    q.push({_start,0});
    visited[_start]=true;

    while(q.empty()==false){
        int curr = q.front().first;
        int currWeight = q.front().second;
        q.pop();
        result += treasure[curr];

        for(int i=0;i<spots[curr].size();i++){
            int next = spots[curr].at(i).first;
            int weight = spots[curr].at(i).second;

            if(visited[next]==false && weight+currWeight <= m){
                visited[next]=true;
                q.push({next,weight+currWeight});
            }
        }
    }

    return result;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>n>>m>>r;

    for(int i=1;i<=n;i++){
        cin>> treasure[i];
    }

    for(int i=0;i<r;i++){
        int a,b,c;
        cin>>a>>b>>c;
        spots[a].push_back({b,c});
        spots[b].push_back({a,c});
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        ans = max(ans,SerachTreasure(i));
    }
    cout<<ans;
}
*/