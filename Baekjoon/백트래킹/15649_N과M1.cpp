#include<iostream>
using namespace std;

int arr[10];
bool lock[10];
int N,M;
void FindNext(int index){
    if(index==M){
        for(int i=0;i<M;i++){
            cout<<arr[i]<<" ";
        }
        cout<<'\n';
        return;
    }
    for(int i=1;i<=N;i++){
        if(lock[i]==false){
            lock[i]=true;
            arr[index]=i;
            FindNext(index+1);
            lock[i]=false;
        }
    }
}

int main(){
    cin>>N>>M;
    FindNext(0);
}