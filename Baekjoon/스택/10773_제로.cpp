#include<iostream>
#include<stack>
using namespace std;
int main(){
    int K;
    stack<int>s;
    int tmp;
    cin>>K;
    for(int i=0;i<K;i++){
        cin>>tmp;
        if(tmp==0){
            s.pop();
        }else{
            s.push(tmp);
        }
    }
    int result = 0;
    while(s.empty()==false){
        result+=s.top();
        s.pop();
    }

    cout<<result;
}