// https://www.acmicpc.net/problem/1389

// 전체 사람들에 대해서 건너건너 아는 dist 합이 가장 작은 사람 추출

// 플로이드 와샬 문제를 잘 알고있으면 쉽게 풀 수 있다.

#include<iostream>
#include<vector>
using namespace std;

int grid[101][101];

int N,M;

void bfs(){
    for(int k=1;k<=N;k++){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                if(grid[i][k]>0 && grid[k][j]>0){
                    if(grid[i][j]==0)
                        grid[i][j] =  grid[i][k]+ grid[k][j];
                    else
                        grid[i][j] = min(grid[i][j], grid[i][k]+ grid[k][j]);
                }
            }
        }
    }
}

int main(){
    cin>>N>>M;
    for(int i=0;i<M;i++){
        int x,y;
        cin>>x>>y;
        grid[x][y]=1;
        grid[y][x]=1; 
    }

    bfs();

    int tmp[N+1];
    int minDist = 10000000;
    for(int i=1;i<=N;i++){
        tmp[i]=0;
        for(int j=1;j<=N;j++){
            if(i!=j){
                tmp[i]+=grid[i][j];
                //cout<<grid[i][j]<<' ';
            }
        }
        //cout<<'\n';

        if(tmp[i]<minDist){
            minDist=tmp[i];
        }
    }
    for(int i=1;i<=N;i++){
        if(tmp[i]==minDist){
           cout<<i<<'\n';
           break;
        }
    }
}