// https://www.acmicpc.net/problem/11066
// 낱장으로 흩뿌려진 chapter를 효율적으로 정리하는 방법

#include<iostream>
using namespace std;
// dp[x][y]가 x~y까지 파일을 합쳤을 때의 최소 값이라고 했을 때,
// dp[x][y]는 x~mid + mid~y까지의 최소 값을 합친 것이다.

int dp[501][501];
int sum[501];
int cost[501];
int main(){
    int T;
    cin>>T;

    for(int i=0;i<T;i++){
        int K;
        cin>>K;
        for(int j=1;j<=K;j++){
            cin>>cost[j];
            sum[j] = sum[j-1]+cost[j];
        }

        for(int j=1;j<K;j++){
            // j는 합친 장의 크기
            for(int tx = 1;tx+j<=K;tx++){
                int ty = tx + j;
                // tx, ty는 어디서부터 어디까지 합친 것인지,
                dp[tx][ty] = 1000000007;
                for(int mid = tx;mid<ty;mid++){
                    // mid는 tx와 ty 사이의 값

                    // sum[ty]-sum[tx-1] 뜻은? ty까지 파일의 크기를 다 더한 것에서 tx-1까지 파일의 크기를 다 더한 것을 뺐으니, tx부터 ty까지의 파일의 크기 합 
                    // => dp[tx][mid],dp[mid+1][ty]는 두 덩어리를 만드는 데에 필요한 비용이므로, 합치는 비용을 추가해야함
                    //cout<<dp[tx][ty]<<", "<<dp[tx][mid]+dp[mid+1][ty]+sum[ty]-sum[tx-1]<<'\n';
                    dp[tx][ty] = min(dp[tx][ty],dp[tx][mid]+dp[mid+1][ty]+sum[ty]-sum[tx-1]);
                }
            }
        }
        cout<<dp[1][K]<<'\n';
    }
}

/* 시도한 것 - 틀림
// 나는 1차원 dp로도 가장 최소의 것을 구할 수 있을것이라 생각했는데, 아니었다.
// dp[n]은 n번째 장을 합칠 때 최소 비용이다. -> 순서대로 합쳐야한다.

int main(){
    int T;
    cin>>T;

    for(int i=0;i<T;i++){
        int K;
        cin>>K;
        int* cost = new int[K];
        for(int j=0;j<K;j++){
            cin>>cost[j];
        }
        int* dp = new int[K];

        dp[0] = cost[0];
        dp[1] = cost[0] + cost[1];

        for(int j=2;j<K;j++){
            dp[j] = min(2*(dp[j-1])+cost[j], 2*(dp[j-2]+cost[j]+cost[j-1]));
        }
        cout<<dp[K-1]<<'\n';
    }
}
*/