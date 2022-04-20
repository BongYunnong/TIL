// https://www.acmicpc.net/problem/9372

// 함정이라 하면 함정이 있다.
// 입력 자체가 주어지는 비행 스케줄은 항상 연결 그래프를 이룬다고 한다.
// 그런데 딱히 가중치도 없고, 그냥 가장 적은 종류의 비행기를 타야한다고 하니
// 무조건 최소 스패닝 트리가 만들어지고, 그 크기는 노드개수 N - 1이다.

// 내가 화나는 것은 위의 함정이 아니라 내가 MST랑 bfs를 구현해보았는데 계속 출력, 메모리, length 에러가 뜨는 것이다.

#include<iostream>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N,M;
        cin>>N>>M;
        for(int i=0;i<M;i++){
            int a,b;
            cin>>a>>b;
        }
        cout<<N-1<<'\n';
    }
}
/*
#include <iostream>
#include <queue>
using namespace std;

int W[1001][1001];
int N,M;

int dist[1001];
int vnear;
int MST(){
    int count=0;
    for(int i=1;i<N;i++){
        dist[i]=W[i][1];
    }

    for(int k=0;k<N-1;k++){
        int minimum=100000000;
        for(int i=2;i<N;i++){
            for(int j=0;j<N;j++){
                if(minimum>dist[j] && dist[j]>0){
                    minimum= dist[j];
                    vnear=j;
                }
            }
        }   
        count++;
        dist[vnear]=-1;

        for(int i=0;i<N;i++){
            if(W[i][vnear] < dist[i]){
                dist[i] = W[i][vnear];
            }
        }
    }
    cout<<count<<'\n';
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        cin>>N>>M;
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                W[j][k]=100000000;
            }
        }
        
        for(int j=0;j<M;j++){
            int a,b;
            cin>>a>>b;
            W[a][b]=1;
            W[b][a]=1;
        }
        MST();
    }
}
*/

// 자꾸 출력에러, 메모리 에러, length 에러가 뜸..
/*
#include <iostream>
#include <queue>
using namespace std;

int W[1001][1001];
int N,M;
bool visited[1001];

int bfs(){
    int result=0;
    queue<int> q;
    q.push(1);
    while(q.empty()==false){
        int currX = q.front();
        q.pop();
        
        for(int i=1;i<=N;i++){
            if(W[currX][i]>0){
                if(visited[i]==false){
                    visited[i]=true;
                    q.push(i);
                    result++;
                }
            }
        }
    }
    cout<<result-1<<'\n';
}

int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        cin>>N>>M;
        for(int j=0;j<=N;j++){
            for(int k=0;k<=N;k++){
                W[j][k]=100000000;
            }
            visited[j]=false;
        }
        for(int j=0;j<M;j++){
            int a,b;
            cin>>a>>b;
            W[a][b]=1;
            W[b][a]=1;
        }

        bfs();
    }
}
*/