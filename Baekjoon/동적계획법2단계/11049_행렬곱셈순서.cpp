// https://www.acmicpc.net/problem/11049

// N×M인 행렬 A와 M×K인 B를 곱할 때 필요한 곱셈 연산의 수
// 이 문제를 풀기 전에 11066 행렬 곱셈 문제를 풀어서 겨우 풀었음

#include<iostream>
using namespace std;

int dp[501][501];
pair<int,int> cost[501];
int main(){
    int K;
    cin>>K;
    for(int j=1;j<=K;j++){
        int x;
        int y;
        cin>>x>>y;
        cost[j]={x,y};
    }

    for(int j=1;j<K;j++){
        for(int tx = 1;tx+j<=K;tx++){
            int ty = tx + j;
            dp[tx][ty] = 1000000007;
            for(int mid = tx;mid<ty;mid++){
                int sumCost = cost[tx].first * cost[mid].second * cost[ty].second;
                dp[tx][ty] = min(dp[tx][ty],dp[tx][mid]+dp[mid+1][ty]+sumCost);
            }
        }
    }
    cout<<dp[1][K]<<'\n';
}