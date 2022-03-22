// https://www.acmicpc.net/problem/4153
// 세 변의 길이로 삼각형이 직각인지 아닌지 확인하기
#include<iostream>
using namespace std;
int main(){
    int a,b,c;
    while(true){
        cin>>a>>b>>c;
        if(a==b&&b==c&&c==0){
            break;
        }

        // 그냥 3가지 경우의 수 다 해보기
        if(a*a+b*b==c*c || b*b+c*c==a*a || a*a+c*c==b*b)
            cout<<"right"<<'\n';
        else
            cout<<"wrong"<<'\n';
    }
}