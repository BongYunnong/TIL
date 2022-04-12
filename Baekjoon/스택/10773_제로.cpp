// https://www.acmicpc.net/problem/10773

// 장부 관리하는데 실수를 하면 0을 외쳐서 최근에 쓴 수를 지우게 함
// 제대로 된 모든 수의 합은?

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