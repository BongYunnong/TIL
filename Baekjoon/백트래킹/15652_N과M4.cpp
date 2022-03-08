#include<iostream>
using namespace std;

int N,M;
int arr[10];
void dfs(int index,int num){
    if(index==M){
        for(int i=0;i<M;i++){
            cout<<arr[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=1;i<=N;i++){
        if(i>=num){
            arr[index]=i;
            dfs(index+1,i);
        }
    }
}

int main(){
    cin>>N>>M;
    dfs(0,1);
}