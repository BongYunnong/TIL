// https://www.acmicpc.net/problem/11722
// 다른 가장 긴 부분수열 문제와 마찬가지로 11055번을 제대로 풀 수만 있으면 쉽게 풀 수 있다.
// 이 형식을 기억하는 것이 좋겠다. A로 input을 받고, DP로 i번째 값을 사용했을때의 구하려는 값을 동적계획하면 된다.
#include<iostream>
using namespace std;

int A[1001];
int DP[1001];   // DP[i]는, i번째 값을 사용했을 때 길이의 최댓값
int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>A[i];
        DP[i]=1;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<i;j++){
            if(A[i]<A[j]){
                // i값이 앞의 j값보다 더 작은 경우에 한해서,

                DP[i]=max(DP[i],DP[j]+1);
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