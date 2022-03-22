// https://www.acmicpc.net/problem/11653
// 정수 N이 주어졌을 때 소인수분해하기
#include<iostream>
using namespace std;
int main(){
    long N;
    cin>>N;

    int mul=2;
    while(N!=1){
        if(N%mul==0){
            // 2부터 시작해서 값이 나누어진다면 계속 N을 해당 값으로 나누기
            cout<<mul<<'\n';
            N/=mul;
        }else{
            //안 나누어지면 나누는 값 증가시키기
            mul++;
        }
    }

}