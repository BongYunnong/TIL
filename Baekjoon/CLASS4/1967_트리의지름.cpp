// https://www.acmicpc.net/problem/1967
// 트리의 지름을 구하기 위해서는 임의의 점에서 가장 먼 점을 구한 뒤, 그 점에서부터 가장 먼 점을 다시 구하면 된다.
#include<iostream>
#include<vector>
using namespace std;

vector<pair<int,int>> node[10002];
int result=0;
int endPoint=0;
bool visited[10002]={false,};

void dfs(int pos,int len){
    if(visited[pos]){
        return;
    }
    visited[pos]=true;
    if(result<len){
        result=len;
        endPoint=pos;
    }
    for(int i=0;i<node[pos].size();i++){
        dfs(node[pos][i].first,len+node[pos][i].second);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;
    for(int i=0;i<N-1;i++){
        int a,b,c;
        cin>>a>>b>>c;

        node[a].push_back({b,c});
        node[b].push_back({a,c});
    }
    dfs(1,0);
    result = 0;
    fill(visited,visited+10002,false);
    dfs(endPoint,0);
    cout<<result;
}

/* 플로이드로 풀려다 실패!
#include<iostream>
using namespace std;

bool canGo[10001][10001];
bool canGoDup[10001][10001];
int grid[10001][10001];
int main(){
    int N;
    cin>>N;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            grid[i][j]=0;
            canGo[i][j]=false;
        }
    }
    for(int i=0;i<N-1;i++){
        int a,b,c;
        cin>>a>>b>>c;

        grid[a][b]=c;
        grid[b][a]=c;
        canGo[a][b]=true;
        canGo[b][a]=true;
    }

    int ans=0;
    
            for(int x=1;x<=N;x++){
                for(int y=1;y<=N;y++){
                    canGoDup[x][y] = false;
                }
            }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            for(int k=1;k<=N;k++){
                if(canGoDup[i][j]==false){
                    grid[i][j] = max(grid[i][j],grid[i][k]+grid[k][j]);
                    canGoDup[i][j]=true;
                    ans = max(ans,grid[i][j]);
                        
                    cout<<"ans :"<<ans<<"  i,j  "<<i<<","<<j<<" K"<<k<<"   ";
                    cout<<grid[i][j]<<" vs "<<(grid[i][k]+grid[k][j])<<'\n';
                }
            }
        }
    }
    cout<<ans;
}
*/