#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;


string input;
int main(){
    cin>>input;
    stack<char> operStack;
    queue<char> valQueue;
    int operIndex=-1;
    for(int i=0;i<input.size();i++){
        if('A'<=input[i] && input[i]<='Z'){
            valQueue.push(input[i]);
        }else{
            operIndex=i;
            operStack.push(input[i]);

        }
    }
}