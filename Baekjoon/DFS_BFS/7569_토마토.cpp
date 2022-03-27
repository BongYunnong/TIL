// https://www.acmicpc.net/problem/7569
// 7576 토마토 문제를 풀면 그나마 간단하게 풀 수 있다.

// 중요한 것은 grid에 day count를 추가하는 방법이고, x축, y축을 헷갈리지 않는 것 같다.

#include<iostream>
#include<queue>
#include<vector>
#include<tuple>
using namespace std;

int grid[101][101][101];
int N,M,H;

int result=0;
queue<tuple<int,int,int>> searchQ;

void BFS(){
    while(searchQ.empty()==false){
        tuple<int,int,int> tmpTuple = searchQ.front();
        
        int y  = get<0>(tmpTuple);
        int x  = get<1>(tmpTuple);
        int z  = get<2>(tmpTuple);
        searchQ.pop();
        //cout<<"xy _ "<<x<<','<<y<<endl;
        for(int k=-1;k<2;k++){
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                    if(abs(i)+abs(j)+abs(k)<=1){
                        if(x+i>= 0 && x+i < M && y+j>=0 && y+j < N && z+k>=0 && z+k<H
                            && grid[y+j][x+i][z+k]==0){
                            //cout<<"xy_"<<(x+i)<<","<<(y+j)<<endl;
                            searchQ.push(make_tuple(y+j,x+i,z+k));
                            grid[y+j][x+i][z+k] = grid[y][x][z]+1;
                            //cout<<"day_"<<day[x+i][y+j];
                        }
                    }
                }
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    cin>>M>>N>>H;

    for(int k=0;k<H;k++){
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                cin>>grid[i][j][k];

                if(grid[i][j][k]==1){
                    searchQ.push(make_tuple(i,j,k));
                }
            }
        }
    }

    if(searchQ.size()>0){
        BFS();
    }
    
    for(int k=0;k<H;k++){
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                if(grid[i][j][k]==0){
                    cout<<"-1";
                    return 0;
                }
                if(result<grid[i][j][k])
                    result = grid[i][j][k];
            }
        }
    }
    cout<<result-1;
}
