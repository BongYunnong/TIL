#include<iostream>
#include<queue>
using namespace std;

long long A,B;
void BFS(){
    queue<pair<long long,long long>> q;
    q.push({A,0});
    while(q.empty()==false){
        long long val = q.front().first;
        long long count = q.front().second;
        q.pop();
        if(val==B){
            cout<<(count+1);
            return;
        }
        
        if(val*2 <= B){
            q.push({val*2,count+1});
        }
        if(val*10+1 <= B){
            q.push({val*10+1,count+1});
        }
    }
    cout<<-1;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>A>>B;
    BFS();
}

// 처음에 long long 안 써서 틀림
// 근데 코드를 좀 더 간추릴 수 있다.
/*
#include<iostream>
#include<queue>
using namespace std;

long long A,B;
void BFS(){
    queue<pair<int,pair<long long,long long>>> q;
    q.push({0,{A,0}});
    q.push({1,{A,0}});

    while(q.empty()==false){
        int curr = q.front().first;
        long long val = q.front().second.first;
        long long count = q.front().second.second;
        q.pop();
        if(val==B){
            cout<<(count+1);
            return;
        }else if(val<B){
            if(curr==0){
                val*=2;
            }else{  
                val*=10;
                val+=1;
            }

            q.push({0,{val,count+1}});
            q.push({1,{val,count+1}});
        }
    }
    cout<<-1;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>A>>B;
    BFS();
}
*/