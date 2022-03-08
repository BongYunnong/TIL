#include<iostream>
using namespace std;

bool visited[10];
int arr[10];
int N,M;
void FindNext(int index,int currNum){
    if(index==M){
        for(int i=0;i<M;i++)
            cout<<arr[i]<<' ';
        cout<<'\n';
        return;
    }
    
    for(int i=currNum;i<=N;i++){
        if(visited[i]==false){
            visited[i]=true;
            arr[index]=i;
            FindNext(index+1,i+1);
            visited[i]=false;
        }
    }
}

int main(){

    cin>>N>>M;
    FindNext(0,1);
}