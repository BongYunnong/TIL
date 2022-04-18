// 왜 다 생각해놓고 풀지를 못하니...
// index를 생각하는 과정을 내가 진짜 못하나보다..

#include<iostream>
#include<string>
#include<stack>
using namespace std;

int GetOperLevel(char input){
    switch(input){
        case '(':
            return -1;
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
    }
}
string input;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>input;
    stack<char> operStack;
    for(int i=0;i<input.size();i++){
        if('A'<=input[i] && input[i]<='Z'){
            cout<<input[i];
        }else{
            if(input[i]=='('){
                operStack.push(input[i]);
            }else if(input[i]==')'){
                while (operStack.empty()==false)
                {
                    char currOper = operStack.top();
                    operStack.pop();
                    if(currOper=='('){
                        break;
                    }else{
                        cout<<currOper;
                    }
                }
            }else{
                while (operStack.empty()==false &&  GetOperLevel(operStack.top())>=GetOperLevel(input[i]))
                {
                    char currOper = operStack.top();
                    cout<<currOper;
                    operStack.pop();
                }
                operStack.push(input[i]);
            }
        }
    }
    while (operStack.empty()==false)
    {
        char currOper = operStack.top();
        cout<<currOper;
        operStack.pop();
    }
}



/* 25퍼 틀림
#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;


string input;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>input;
    stack<char> operStack;
    int operIndex=-1;
    for(int i=0;i<input.size();i++){
        bool popAll =false;
        char pushOper=' ';
        if('A'<=input[i] && input[i]<='Z'){
            cout<<input[i];
            if(i==input.size()-1){
                popAll=true;
            }
        }else{
            int pastOperIndex=operIndex;
            switch(input[i]){
                case '(':
                    operIndex=-1;
                    pushOper=input[i];
                    break;
                case ')':
                    while (operStack.empty()==false)
                    {
                        char currOper = operStack.top();
                        operStack.pop();
                        if(currOper=='('){
                            break;
                        }else{
                            cout<<currOper;
                        }
                    }
                    break;
                case '+':
                    operIndex=0;
                    pushOper=input[i];
                    break;
                case '-':
                    operIndex=0;
                    pushOper=input[i];
                    break;
                case '*':
                    operIndex=1;
                    pushOper=input[i];
                    break;
                case '/':
                    operIndex=1;
                    pushOper=input[i];
                    break;
            }
            if(pastOperIndex>=operIndex && operIndex!=-1){
                popAll=true;
            }
        }

        if(popAll){
            while (operStack.empty()==false)
            {
                char currOper = operStack.top();
                if(currOper=='('){
                     break;
                }
                cout<<currOper;
                operStack.pop();
            }
        }
        if(pushOper!=' '){
            operStack.push(input[i]);
        }
    }
}
*/