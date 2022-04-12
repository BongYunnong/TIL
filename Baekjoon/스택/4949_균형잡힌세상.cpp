// https://www.acmicpc.net/problem/4949

// 괄호의 시작 부분이 오면 stack에 저장하고, 괄호의 끝 부분이 오면 pop을 하는데, 만약 pop을 한 것이 끝 부분과 매칭되지 않으면 no이다.
// 문자열을 다 체크했는데 stack이 비어있다면, yes이다.
// stack도 stack이지만 문자열을 잘 활용해야한다.

#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main(){
    while(true){
        string input;
        getline(cin,input);
        if(input.size() <= 1 && input[0]=='.')
            break;
        bool yes=true;
        stack<char> s;

        for(int i=0;i<input.size();i++){
            if(input[i]=='(' || input[i]=='['){
                s.push(input[i]);
            }else if(input[i]==')'){
                if(s.size() > 0){
                    if(s.top()=='('){
                        s.pop();
                    }else{
                        yes=false;
                        break;
                    }
                }else{
                    yes=false;
                    break;
                }
            }else if(input[i]==']'){
                if(s.size() > 0){
                    if(s.top()=='['){
                        s.pop();
                    }else{
                        yes=false;
                        break;
                    }
                }else{
                    yes=false;
                    break;
                }
            }
        }
        if(s.empty() && yes){
            cout<<"yes"<<endl;
        }else{
            cout<<"no"<<endl;
        }
    }
}

/* 틀림
int main(){
    stack<char> s;

    while(true){
        bool yes=true;
        while (s.empty()==false)
        {
            s.pop();
        }
        int count=0;
        while(true){
            char tmpChar;
            cin>>tmpChar;
            //cout<<tmpChar;
            count++;
            if(tmpChar=='.'){
                if(s.size()!=0){
                    yes=false;
                }
                break;
            }else{
                if(tmpChar=='(' || tmpChar=='['){
                    s.push(tmpChar);
                }else if(tmpChar==')'){
                    if(s.empty()){
                        yes=false;
                    }else if(s.top()=='('){
                        s.pop();
                    }else{
                        yes=false;
                    }
                }else if(tmpChar==']'){
                    if(s.empty()){
                        yes=false;
                    }else if(s.top()=='['){
                        s.pop();
                    }else{
                        yes=false;
                    }
                }
            }
        }
        if(count<=1){
            cout<<"yes"<<endl;
            break;
        }else{
            if(yes){
                cout<<"yes"<<endl;
            }else{
                cout<<"no"<<endl;
            }
        }
    }
}
*/