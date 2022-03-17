#include<iostream>
#include<queue>
using namespace std;
int main(){
    int N;
    int index;
    cin>>N;
    cin>>index;

    queue<int> q;
    for(int i=1;i<=N;i++){
        q.push(i);
    }

    cout<<"<";
    while(q.size()>0){
        for(int i=0;i<index-1;i++){
            int val = q.front();
            q.pop();
            q.push(val);
        }
        int val = q.front();
        cout<<val;
        q.pop();
        if(q.size()!=0){
            cout<<", ";
        }
    }
    cout<<">";
}