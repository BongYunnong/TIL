// https://www.acmicpc.net/problem/1259

// 어떤 단어를 뒤에서부터 읽어도 똑같으면 '팰린드롬'이다.
// ex. radar, sees

// 뒤에서부터 중간까지 큐에 삽입하고, 앞에서부터 큐와 하나씩 비교하기
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