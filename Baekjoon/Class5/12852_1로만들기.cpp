// https://www.acmicpc.net/problem/12852
// 역추적 하는 방법을 잘 알아두자.
#include <iostream>
using namespace std;
# define MAX 1000001
long N;

int results[MAX];
int tracking[MAX];
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;

    results[1]=0;
    tracking[1]=-1;

    for(int i=2;i<=N;i++){
        results[i] = results[i-1]+1;
        tracking[i]=i-1;

        if(i%2==0 && results[i]>results[i/2]+1){
            results[i]=results[i/2]+1;
            tracking[i] = i/2;
        }
        if(i%3==0 && results[i]>results[i/3]+1){
            results[i]=results[i/3]+1;
            tracking[i] = i/3;
        }
    }
    cout<<results[N]<<'\n';
    while(N!=-1){
        cout<<N<<' ';
        N = tracking[N];
    }

}

// DFS 안돼
/*
#include <iostream>
#include <queue>
using namespace std;
# define MAX 1000001
long N;
bool founded=false;
bool visited[MAX];
void dfs(int _start,int _count){
    if(founded || _start>N)
        return;
    if(_start==N){
        founded=true;
        cout<<_count<<'\n';
        for(int i=N;i>=1;i--){
            if(visited[i]){
                cout<<i<<' ';
            }
        }
        return;
    }
    if(_start*3<=N){
        visited[_start*3]=true;    
        dfs(_start*3,_count+1);
        visited[_start*3]=false;
    }   
    if(_start*2<=N){
        visited[_start*2]=true;    
        dfs(_start*2,_count+1);
        visited[_start*2]=false;   
    }
    if(_start+1<=N){
        visited[_start+1]=true;    
        dfs(_start+1,_count+1);
        visited[_start+1]=false;    
    }
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;

    visited[1]=true;  
    dfs(1,0);
}
*/