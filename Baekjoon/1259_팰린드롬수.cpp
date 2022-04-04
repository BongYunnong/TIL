// https://www.acmicpc.net/problem/1259
// 1의 자리 수를 생각하지 않아서 한 번 틀림

#include<iostream>
#include<queue>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    while(true){
        string tmp;
        cin>>tmp;
        if(tmp[0]=='0'){
            break;
        }else{
            bool founded=true;
            if(tmp.size()==1){

            }else{
                queue<int> q;
                for(int i=tmp.size()-1;i>=tmp.size()/2;i--){
                    q.push(tmp[i]);
                }
                int size=q.size();
                for(int i=0;i<size;i++){
                    int curr = q.front();
                    q.pop();
                    if(curr!=tmp[i]){
                        founded=false;
                    }
                }
            }
            if(founded){
                cout<<"yes\n";
            }else{
                cout<<"no\n";
            }
        }
    }
}