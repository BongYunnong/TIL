#include<iostream>

using namespace std;

int GCD(int a,int b){
    int n;
    while(b!=0){
        n = a%b;
        a=b;
        b=n;
    }
    return a;
}

int Div(int _N, int _K){
    if(_N==0 || _K==0 || _N==_K){
        return 1;
    }else{
        int a =  Div(_N-1,_K-1);
        int b =   Div(_N-1,_K);
        //cout<<_N-1<<","<<_K-1<<" = "<<a<<endl;
        //cout<<_N-1<<","<<_K<<" = "<<b<<endl;
        return a + b;
    }
}

int main(){
    int N,K;
    cin>>N>>K;

    long long tmp=1;
    for(int i=N-K+1;i<=N;i++){
        int gcd=1;
        if(K!=1){
            gcd = GCD(i,K);
            K/=gcd;
        }
        tmp*=(i/gcd)%1000000007;
        cout<<i<<", GCD:"<<gcd<<" TMP : "<<tmp<<endl;
    }
    cout<<tmp%1000000007;
}