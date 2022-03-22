// https://www.acmicpc.net/problem/1712
// A의 고정비용, B의 가변 비용, C의 가격
// 최초로 이익이 발생하는 판매량은?

#include<iostream>
using namespace std;
int main(){
    long long a,b,c;

    cin>>a>>b>>c;
    long long  count =0;

    if(c>b){
        // 가격이 가변비용보다 크다면, (가격-가변비용)을 몇 번 곱해야 A가 되는지 체크하고
        // 이익이 발생해야하므로 거기에 1을 추가한다.
        cout<< a/(c-b)+1;
    }else{
        // 가격이 가변비용보다 작으면 이익을 내는 것이 불가능하다.
        cout<<-1;
    }
}