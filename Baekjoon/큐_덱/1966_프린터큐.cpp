#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
bool Compare(int a,int b){
    return a>b;
}
int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N;
        cin>>N;
        int M;
        cin>>M;

        int index=0;
        queue<pair<int,int>> q;
        int* arrs = new int[N];
        for(int j=0;j<N;j++){
            int val;
            cin>>val;
            q.push({j,val});
            arrs[j] = val;
        }
        sort(arrs,arrs+N,Compare);

        while(q.size()>=1){
            if(q.front().second==arrs[index]){
                if(q.front().first==M){
                    cout<<index+1<<'\n';
                    break;
                }else{
                    q.pop();
                    index++;
                }
            }else{
                pair<int,int> tmp = q.front();
                q.pop();
                q.push(tmp);
            }
        }
    }
}