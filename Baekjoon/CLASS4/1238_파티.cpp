// https://www.acmicpc.net/problem/1238

// 그냥 플로이드워셜 알고리즘 쓰면 바로 해결!

#include<iostream>
#include<vector>
using namespace std;

#define INF 987654321

int graph[1001][1001];
int N,M,X;

int main(){
    cin>>N>>M>>X;
    for(int i=0;i<1001;i++){
        fill(graph[i],graph[i]+1001,INF);
    }

    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            if(i==j){
                graph[i][j]=0;
            }
        }
    }

    for(int i=0;i<M;i++){
        int a,b,t;
        cin>>a>>b>>t;
        graph[a][b]=t;
    }

    for(int k=1;k<=N;k++){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                graph[i][j] = min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }
    int maxWeight=0;
    for(int i=1;i<=N;i++){
        int currWeight = graph[i][X]+graph[X][i];
        if(currWeight>=INF)
            continue;
        if(maxWeight<currWeight){
            maxWeight = currWeight;
        }
    }
    cout<<maxWeight;
}