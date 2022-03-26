// https://www.acmicpc.net/problem/1012
// M X N 크기의 밭에서 벌레가 있는 곳이 1이라 할 때,
// 약물이 상하좌우만 연쇄적으로 영향이 있다면 최소 몇 번의 약물을 뿌려야하는가?

// 생각보다 간단하다. 그냥 DFS에서 상하좌우를 다 재귀호출해주면 된다.

#include<iostream>
#include<vector>
using namespace std;

int grid[51][51];
int M,N;

vector<pair<int,int>> inputs;
void DFS(int _x,int _y){
    if(grid[_x][_y]!=1){
        return;
    }
    grid[_x][_y]=2;
    if(0<=_x-1){
        DFS(_x-1,_y);
    }
    if(_x+1<M){
        DFS(_x+1,_y);
    }
    if(0<=_y-1){
        DFS(_x,_y-1);
    }
    if(_y+1<N){
        DFS(_x,_y+1);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int T;
    cin>>T;

    for(int i=0;i<T;i++){
        int K;
        cin>>M>>N>>K;
        for(int j=0;j<M;j++){
            for(int k=0;k<N;k++){
                grid[j][k]=0;
            }
        }
        int count=0;

        inputs.clear();
        for(int j=0;j<K;j++){
            int x,y;
            cin>>x>>y;
            if(grid[x][y]==0){
                grid[x][y]=1;
                inputs.push_back({x,y});
            }
        }

        for(int j=0;j<inputs.size();j++){
            if(grid[inputs[j].first][inputs[j].second]==1){
                //cout<<"DFS "<<inputs[j].first<<inputs[j].second<<'\n';
                DFS(inputs[j].first,inputs[j].second);
                count++;
            }
        }


        cout<<count<<'\n';
    }
}