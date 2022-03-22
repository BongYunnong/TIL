//https://www.acmicpc.net/problem/13305

// 주유소에서 기름 값을 지불하고 다음 도시까지 가야하는데
// 제일 왼쪽 도시에서 제일 오른쪽 도시까지 가는데에 필요한 최소비용

#include<iostream>
using namespace std;

int N;

int* dists;
int* gasValues;

int remainGas=0;
long minGasValue=1000000000;
int main(){
    cin>>N;

    dists = new int[N-1];
    gasValues = new int[N];
    for(int i=0;i<N-1;i++){
        cin>>dists[i];
    }
    for(int i=0;i<N;i++){
        cin>>gasValues[i];
    }

    long costs=0;
    for(int i=0;i<N-1;i++){
        // 지금까지의 기름 값 중에서 가장 싼 기름 값을 업데이트한다.
        if(minGasValue > gasValues[i]){
            minGasValue= gasValues[i];
        }
        // 지금 도시에서 다음 도시로 넘어가는 dists[i]만큼 가장 싼 기름 값으로 사놓는다.
        costs += minGasValue*dists[i];

    }
    cout<<costs;
}