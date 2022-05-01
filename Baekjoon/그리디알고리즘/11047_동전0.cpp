//https://www.acmicpc.net/problem/11047
// 동전 개수 최소로 만들기

// 이게 그리디에서 가능한 이유는 (1 ≤ Ai ≤ 1,000,000, A1 = 1, i ≥ 2인 경우에 Ai는 Ai-1의 배수) 이러한 조건이 만족하기 떄문이다.
// 큰 숫자가 다른 숫자들 모두의 배수이기에 가능

#include<iostream>
using namespace std;


int N,K;
int values[1000001];
int main(){
    cin>>N>>K;

    for(int i=0;i<N;i++){
        cin>>values[i];
    }

    int count=0;

    // 무조건 동전 값이 큰 것부터 사용하면 된다.
    for(int i=N-1;i>=0;i--){
        if(K/values[i] > 0){
            int mul = (K/values[i]);
            K -= mul * values[i];
            //cout<<"value:"<<values[i]<<endl;
            count+=mul;
        }
    }
    cout<<count;
}