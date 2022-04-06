// https://www.acmicpc.net/problem/11403
// 플로이드-와샬 문제

#include<iostream>
#include<queue>
using namespace std;

int grid[101][101];
int N;

void bfs(){
    for(int k=0;k<N;k++){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(grid[i][k]==1 && grid[k][j]==1){
                    grid[i][j]=1;
                }
            }
        }
    }
}

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>grid[i][j];
        }
    }
    bfs();
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<grid[i][j]<<' ';
        }
        cout<<'\n';
    }
}