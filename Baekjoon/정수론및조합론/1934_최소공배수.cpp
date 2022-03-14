// https://www.acmicpc.net/problem/1934
#include<iostream>
using namespace std;

int gcd(int a,int b){
    int n;
    while(b!=0){
        n = a%b;
        a=b;
        b=n;
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