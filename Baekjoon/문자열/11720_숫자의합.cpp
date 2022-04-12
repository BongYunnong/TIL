// https://www.acmicpc.net/problem/11720
// N개의 숫자가 공백 없이 쓰여있을 때 이 숫자를 모두 합하기
#include <iostream>
using namespace std;
int main(){
    int n;
    char a[101];

    cin>>n;
    int result=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        result += a[i]-48;
    }
    cout<<result;
    
}