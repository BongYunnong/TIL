// https://www.acmicpc.net/problem/9012

// 4949_균형잡힌 세상과 비슷한 문제이다.
// 오히려 더 쉬운데, 이것은 ()만 생각해주면 된다.

#include<iostream>
#include<string>
#include<stack>
using namespace std;
int main(){
    int T;
    cin>>T;
    string tmp;
    for(int i=0;i<T;i++){
        stack<char> s;
        cin>>tmp;
        bool yes=true;
        for(int j=0;j<tmp.size();j++){
            if(tmp[j]=='('){
                s.push('(');
            }else if(tmp[j]==')'){
                if(s.empty()){
                    yes=false;
                    break;
                }
                if(s.top()=='('){
                    s.pop();
                }else{
                    yes=false;
                }
            }
        }
        if(s.empty()==false){
            yes=false;
        }
        if(yes){
            cout<<"YES";
        }else{
            cout<<"NO";
        }
        cout<<"\n";
    }
}