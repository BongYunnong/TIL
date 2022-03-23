// https://www.acmicpc.net/problem/1932
// 크기(변 길이) N인 정수 삼각형
// 맨 위에서부터 시작해서 아래에 있는 수 중 하나를 선택해서 아래층으로 내려오는데, 대각선 왼쪽 혹은 오른쪽에 있는 것 중에서만 선택 가능
// 선택된 수의 합이 최대가 되는 경로를 구하자.

// 삼각형이라 어떻게 2차원 배열을 만들지 헷갈릴수도 있는데, 그냥 왼쪽으로 밀어보면 된다.
// 어차피 대각선 왼쪽 혹은 오른쪽에 있는 것만 선택 가능하기 때문에 괜찮다.
// F(N,M) = max(F(M-1,M-1),F(N-1,M))+arr[N,M]이다.
// M-1을 구해야하는데 M이 0일때는 M-1이 없으니 자동으로 F(N-1,M)+arr[N,M]이다.

#include<iostream>
#include <algorithm>
using namespace std;

int N;
int costs[501][501]; 

int floorCosts[501];

int main(){
    cin>>N;

    for(int i=0;i<N;i++){
        if(i==0){
            cin>>costs[0][0];
        }else{
            for(int j=0;j<=i;j++){
                cin>>floorCosts[j];
            }

            costs[0][i] = costs[0][i-1]+floorCosts[0];
            costs[i][i] = costs[i-1][i-1] + floorCosts[i];
            for(int j=1;j<i;j++){
                costs[j][i]=max(costs[j-1][i-1],costs[j][i-1])+floorCosts[j];
            }
        }
    }

    long long maxRes = -10000000;
    for(int i=0;i<N;i++){
        if(costs[i][N-1]>=maxRes)
            maxRes=costs[i][N-1];
    }

    cout<<maxRes;
}
