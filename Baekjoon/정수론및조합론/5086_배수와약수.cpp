//https://www.acmicpc.net/problem/5086

// 다시 볼 때는 최대공약수를 생각했는데
// 지금 보니까 그냥 나머지를 구해도 되는구나 싶다.

#include<iostream>
using namespace std;
int main(){
    int a,b;
    while(true){
        cin>>a>>b;
        if(a==0 && b==0){
            break;
        }

        if(b%a==0){
            cout<<"factor\n";
        }else if(a%b==0){
            cout<<"multiple\n";
        }else{
            cout<<"neither\n";
        }
    }
}