// https://www.acmicpc.net/problem/10870

// DP를 써도 된다. 하지만 별 차이는 없는 듯 하다.
#include<iostream>
using namespace std;
int* dp;
int main(){
    int N;
    cin>>N;
    dp = new int[N+1];
    dp[0]=0;
    dp[1]=1;
    for(int i=2;i<=N;i++){
        dp[i] = dp[i-1]+dp[i-2];
    }
    cout<<dp[N];
}

/*
// 재귀함수
#include<iostream>
using namespace std;
int F(int _n){
    if(_n<=1)
        return _n;
    else{
        return F(_n-1)+F(_n-2);
    }
}
int main(){
    int n;
    cin>>n;
    cout<<F(n);
}
*/