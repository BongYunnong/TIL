//https://www.acmicpc.net/problem/1037

// 양수 A가 N의 진짜 약수가 되려면 N이 A의 배수이고, A가 1과 N이 아니어야 한다고 한다.
// 그렇다면 그냥 sort해서 맨 앞 값과 맨 뒷 값을 곱하면 N이 된다.

#include<iostream>
#include<algorithm>
using namespace std;

int countInput;
int factors[51];
int main(){
    cin>>countInput;
    for(int i=0;i<countInput;i++){
        cin>>factors[i];
    }
    sort(factors,factors+countInput);
    cout<<factors[0]*factors[countInput-1];
}