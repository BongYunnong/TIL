// https://www.acmicpc.net/problem/11727

// F(n) = F(n-1) + 2*F(n-2)이다.
// 내가 생각했던과 다른 것은 2*2 박스가 있었다는 것

// 나머지를 구할 때, 더하기라면 각각을 더하기 전에 미리 나머지를 구한 뒤 더하고, 그 후에 나머지를 구하면 정상적으로 값이 나온다.

#include<iostream>
using namespace std;

long long arr[1001];

int main(){
    int n;
    cin>>n;

    arr[1] = 1;
    arr[2] = 3;
    arr[3] = 5;
    for(int i=4;i<=n;i++){
        arr[i] = arr[i-1]%10007 + (2* arr[i-2])%10007;
    }
    cout<<arr[n]%10007;
}