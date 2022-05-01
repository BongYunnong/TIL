// https://www.acmicpc.net/problem/12865
// N개의 물건이 있고 무게 W와 가치 V를 가진다.
// K만큼의 무게만 넣을 수 있는 배낭만 들고다닐 수 있을때, 가져갈 수 있는 물건 가치의 최댓값

// F(N,K)는 N개의 물건이 있고 K만큼 들 수 있을 때 들 수 있는  물건들의 최대 가치
// 2차원 배열을 두고, 열을 N, 행을 K로 하면 됨
// F(N,K)는 K가 stuff[N]의 무게를 들 수 있을 때까지는 계속 0임
// 만약 K가 stuff[N]의 무게보다 커지면, 들 수 있는 것이니 stuff[i].second를 더할텐데, N을 선택하는 순서로 생각하면, N번째 물건을 선택하려면 N-1번째 물건을 선택한 후 선택해야한다.
// 이 때, N-1번 물건을 들 지 말 지 선택하고나서 N번째 물건을 들려면 stuff[i].weight만큼을 들 수 있는 여유가 있어야 한다. (N-1번을 선택한 후, weight만큼의 공간이 남았을때를 찾아내자.)
// 즉, F(N,K)는 F(N-1,K-stuffs[N].weight)+stuffs[N].value가 된다. 그러나 만약 못 드는 경우도 있을 수 있으니, 그 때는 아무것도 안 한다는 뜻으로 F(N-1,K)를 그대로  가져온다.
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
            // i-1번째 것을 선택한 후, i번째 것을 들 지 말 지 선택하는 과정 -> 들 수 있다고 한다면, i-1번째 것에서 무게 stuff[i].first를 뺀 상태에서 stuff[i]를 추가해야함
            // 만약 그만큼의 공간이 없거나, stuff[i]번째 것을 추가해도 추가 안 한 것보다 못하면 추가하지 않음 (i-1번째 것에 stuff[i]를 추가하는 것이기에, 추가를 하는 것이 별로일 수 있다.)
            if(j>=stuffs[i].first)
                DP[i][j] = max(DP[i-1][j],DP[i-1][j-stuffs[i].first]+stuffs[i].second); 
            else
                DP[i][j] = DP[i-1][j];
        }
    }

    cout<<DP[n][k];
}