// https://www.acmicpc.net/problem/1934

// A와 B의 최소공배수 구하기

#include<iostream>
using namespace std;

int gcd(int a, int b)
{
    while (b > 0)
    {
        int tmp = a;
        a = b;
        b = tmp%b;
    }
    return a;
}
int main(){
    int T;
    cin>>T;

    for(int i=0;i<T;i++){
        int a, b;
        cin>>a>>b;

        cout<<a*b/gcd(a,b)<<'\n';
    }
}