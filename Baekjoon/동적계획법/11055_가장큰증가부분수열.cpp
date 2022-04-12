//https://www.acmicpc.net/problem/11055
// 가장 긴 증가하는 부분수열을 공부하면 쉽게 풀 수 있다.
// 중요한 것은 그것에 익숙해지는 것이다.

#include<iostream>
using namespace std;

int A[1001];
int DP[1001]; // index번을 사용했을 때의 최댓값
int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>A[i];
        DP[i]=A[i];
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<i;j++){
            if(A[i]>A[j]){
                // 앞에 것 들 중에서 현재(i) 값보다 작은 값들에 대해서

                // 현재 값과 J까지 사용한 후에 i를 사용한 값 중 더 큰 값을 저장
                DP[i] = max(DP[i],DP[j]+A[i]);
            }
        }
    }

    int result=0;
    for(int i=0;i<N;i++){
        //cout<<DP[i]<<' ';
        result = max(result,DP[i]);
    }
    cout<<result;
}