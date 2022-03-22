// https://www.acmicpc.net/problem/4948
// 자연수 n에 대해 n보다 크고, 2n보다 작거나 같은 소수는 하나 존재한다.
// n보다 크고 2n보다 작거나 같은 소수의 개수를 구하자.


#include<iostream>
using namespace std;
int main(){
    long M;

    // 원래 소수 찾던 방식대로 소수 찾기
    int counting[500001]={};
    for(int i=1;i<500001;i++){
        int mul=1;
        while (i*mul <= 500000)
        {
            counting[i*mul]++;
            mul++;
        }
    }

    while(true){
        cin>>M;
        if(M==0)
            return 0;

        int result=0;

        // n보다 크고, 2n보다 작거나 같은 수 중에서 소수 판별하기
        for(int i=M+1;i<=2*M;i++){
            if(counting[i]==2){
                result++;
            }
        }
        cout<<result<<'\n';
    }
}