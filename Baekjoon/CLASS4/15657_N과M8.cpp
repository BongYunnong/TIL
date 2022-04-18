#include<iostream>
#include<algorithm>
using namespace std;

int input[10];
int N,M;

int answer[10];

void Search(int startIndex,int count){
    answer[count-1]=input[startIndex];
    if(count==M){
        for(int i=0;i<count;i++){
            cout<<answer[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=startIndex;i<N;i++){
        Search(i,count+1);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N>>M;

    for(int i=0;i<N;i++){
        cin>>input[i];
    }

    sort(input,input+N);

    for(int i=0;i<N;i++){
        Search(i,1);
    }
}