#include<iostream>
#include<queue>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    int N;
    cin>>N;

    priority_queue<int> pq;

    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;

        if(tmp==0){
            if(pq.empty()){
                cout<<0<<'\n';
            }else{
                int top = pq.top();
                cout<<top*-1<<'\n';
                pq.pop();
            }
        }else{
            pq.push(tmp*-1);
        }
    }
}