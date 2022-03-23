#include<iostream>
#include<queue>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    int N;
    cin>>N;
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<N;i++){
        int x;
        cin>>x;

        if(x==0){
            if(pq.empty()){
                cout<<0<<'\n';
            }else{
                pair<int,int> tmpPair = pq.top();
                cout<<-tmpPair.second<<'\n';
                pq.pop();
            }
        }else{
            pq.push({-abs(x),-x});
        }
    }
}