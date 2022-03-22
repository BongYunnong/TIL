// https://www.acmicpc.net/problem/1929
// M 이상 N 이하의 소수를 모두 출력하자.

// 1에서부터 최대값까지 모든 값을 곱해서 나온 수를 counting 배열의 인덱스로 하고 그 값을 증가시킨다.
#include<iostream>
using namespace std;
int main(){
    long M,N;
    cin>>M>>N;


    int counting[1000001]={};
    for(int i=1;i<1000001;i++){
        int mul=1;
        while (i*mul <= 1000000)
        {
            counting[i*mul]++;
            mul++;
        }
    }

    for(int i=M;i<=N;i++){
        // 약수가 자신과 1 두개뿐일 경우가 소수
        if(counting[i]==2){
            cout<<i<<'\n';
        }
    }

}