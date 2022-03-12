#include<iostream>
#include<vector>
using namespace std;

vector<pair<int,int>> stuffs;
int DP[101][100001];
int main(){
    int n,k;
    cin>>n>>k;

    stuffs.push_back({0,0});
    for(int i=0;i<n;i++){
        int tmp1,tmp2;
        cin>>tmp1>>tmp2;
        stuffs.push_back({tmp1,tmp2});
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(j>=stuffs[i].first)
                DP[i][j] = max(DP[i-1][j],DP[i-1][j-stuffs[i].first]+stuffs[i].second);
            else
                DP[i][j] = DP[i-1][j];
        }
    }

    cout<<DP[n][k];
}