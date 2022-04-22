// https://www.acmicpc.net/problem/11866

// 1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 K(≤ N)가 주어진다. 
// 이제 순서대로 K번째 사람을 제거한다.
// 한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다.
// 이 과정은 N명의 사람이 모두 제거될 때까지 계속된다.

// 원에서 사람들이 제거되는 순서를 (N, K)-요세푸스 순열이라고 한다.

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
        // index만큼 pop해서 뒤에 push
        for(int i=0;i<index-1;i++){
            int val = q.front();
            q.pop();
            q.push(val);
        }
        // 원하는 index에 도달하면 출력하고 pop
        int val = q.front();
        cout<<val;
        q.pop();
        if(q.size()!=0){
            cout<<", ";
        }
    }
    cout<<">";
}