// https://www.acmicpc.net/problem/3036

// 또 최대공약수 문제.
// 첫번째 값과 다른 값의 최대공약수를 구해서 각각을 최대공약수로 나누어서 분자.분모에 배치


#include<iostream>
using namespace std;
int N;
int radiuses[101];

int gcd(int a, int b){
    int n;
    while (b!=0)
    {
        int n = a%b;
        a=b;
        b=n;
    }
    return a;
}

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>radiuses[i];
    }

    for(int i=1;i<N;i++){
        int currGCD = gcd(radiuses[0],radiuses[i]);
        cout<<radiuses[0]/currGCD<<"/"<<radiuses[i]/currGCD<<'\n';
    }
}