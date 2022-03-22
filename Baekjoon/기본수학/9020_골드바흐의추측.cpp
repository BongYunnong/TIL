// https://www.acmicpc.net/problem/9020
// 골드바흐의 추측 : 2보다 큰 모든 짝수는 두 소수의 합으로 나타낼 수 있다. 이러한 수는 골드바흐 수라고 한다.
// 짝수를 두 소수의 합으로 나타내는 표현을 그 수의 골드바흐 파티션이라 한다.
// 10000보다 작거나 같은 모든 짝수 n에 대한 골드바흐 파티션은 존재한다.

// 2보다 큰 짝수 n이 주어졌을 때 n의 골드바흐 파티션 출력하기

#include<iostream>
using namespace std;
int main(){
    int T;
    cin>>T;

    // 일단 소수 찾기
    int counting[10001]={};
    for(int i=1;i<10001;i++){
        int mul=1;
        while (i*mul <= 10000)
        {
            counting[i*mul]++;
            mul++;
        }
    }

    int n;
    for(int i=0;i<T;i++){
        cin>>n;

        // n은 짝수이므로, 딱 중간에서부터 같은 거리에 있는 값이 둘 다 소수라면 OK
        for(int j=n/2;j>1;j--){
            if(counting[j]==2){
                if(counting[n-j]==2){
                    cout<<j << " "<<n-j<<'\n';
                    break;
                }
            }
        }
    }   
}