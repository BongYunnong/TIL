// https://www.acmicpc.net/problem/11401

// 자연수 N과 정수 K가 주어졌을 때 이항 계수 (N,K)를 1,000,000,007로 나눈 나머지
// 22-04-04 아직 이해 못함

// 페르마 소정리
// p가 소수이고 a가 p의 배수가 아니면, a^(p-1) = 1(mod p)이다.
// 즉, a^(p-1)을 p로 나눈 나머지는 1이다.
// a^(p-1) = 1(mod P)
// a*a^(p-2) = 1(mod P)
// a^(p-2) = a^(-1)(mod P)

// a*b^(-1)%P = a*b^(P-2)%P = (a%P)(b^(P-2)%P)%P 

#include<iostream>
using namespace std;


long long N,K,A,B,half;
long long mod = 1000000007;
long long solve(int x){
    if(x==0)
        return 1;
    else if(x%2==1){
        return B*solve(x-1)%mod;
    }else{
        half = solve(x/2);
        return half*half%mod;
    }
}

int main(){
    cin>>N>>K;
    A=1;
    // A는 N~ (N-K+1)까지 곱한 것 
    for(int i=N;i>=N-K+1;i--)
        A = (A*i)%mod;
    
    // B는 K!
    B=1;
    for(int i=1;i<=K;i++)
        B = (B*i)%mod;

    // B = (K!)^(P-2)
    B = solve(mod-2);

    // 구하고자 하는 것 : a*b^(-1)%P  무조건 A는 B로 나누어지게 되어있음. 그것을 P로 나눈 나머지
    // 페르마 소정리에 의해 아래 공식이 성립하므로, A를 구한 뒤 나머지를 구하고,
    // B를 구한 뒤  P-2승을 한 뒤 P로 나눈 나머지를 구하여서 두개를 곱하고 다시 나머지를 구하면 된다.
    // a*b^(-1)%P = A*B^(P-2)%P = (A%P)(B^(P-2)%P)%P 
    cout<<A*B%mod;
}


/* 틀림
int GCD(int a,int b){
    int n;
    while(b!=0){
        n = a%b;
        a=b;
        b=n;
    }
    return a;
}
int main(){
    long long N,K;
    cin>>N>>K;

    long long originK = K-1;
    long long tmp=1;
    for(int i=N-K+1;i<=N;i++){
        tmp *= i;
        int gcd=GCD(tmp,K);
        while (gcd==1 && originK !=1)
        {
            K = K* originK;
            originK--;
            gcd = GCD(tmp,K);
        }
        K/=gcd;
        tmp = (tmp/gcd)%1000000007;
        //cout<<i<<", GCD:"<<gcd<<" TMP : "<<tmp<<endl;
    }
    cout<<tmp%1000000007;
}
*/