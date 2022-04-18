// https://www.acmicpc.net/problem/11050

// 최대공약수를 써도 맞긴 하지만....
// 애초에 그냥 구해질거면 이렇게 안 했지...

// 엇 또까먹었네, 이거 dp 쓰는거

#include<iostream>
using namespace std;

int GCD(int a,int b){
    int n;
    while(b!=0){
        n = a%b;
        a = b;
        b = n;
    }
    return a;
}

int N,K;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>K;
    int fact1 =1;
    int fact2 =1;
    for(int i=2;i<=N;i++){
        if(i>=N-K+1 && i<=K){
        }else if(i>=N-K+1){
            fact1*=i;
        }else if(i<=K){
            fact2*=i;
        }

        int gcd = GCD(fact1,fact2);
        fact1/=gcd;
        fact2/=gcd;
    }

    cout<<fact1/fact2;
}
/*
#include<iostream>
using namespace std;

int N,K;

int main(){
    cin>>N>>K;

    int fact1 = 1;
    for(int i=N-K+1;i<=N;i++){
        fact1*=i;
    }

    int fact2 = 1;
    for(int i=2;i<=K;i++){
        fact2*=i;
    }

    cout<<fact1/fact2;
}
*/