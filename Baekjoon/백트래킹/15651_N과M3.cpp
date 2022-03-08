#include<iostream>
using namespace std;

bool visited[10];
int arr[10];
int N,M;

void dfs(int index){
    if(index==M){
        for(int i=0;i<M;i++){
            cout<<arr[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=1;i<=N;i++){
        arr[index]=i;
        dfs(index+1);
    }
}

int main(){
    cin>>N>>M;
    dfs(0);
}