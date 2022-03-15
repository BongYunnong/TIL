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