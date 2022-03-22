// https://www.acmicpc.net/problem/2581
// M이상 N 이하의 자연수 중 소수인 것을 골라 이들 소수의 합과 최솟값을 찾자.
// 1929번 처럼 소수를 구한 후
// 그 소수들의 합, 최솟값 계산

#include<iostream>
using namespace std;
int main(){
    int M,N;
    cin>>M>>N;

    int counting[10001]={};
    for(int i=1;i<10001;i++){
        int mul=1;
        while (i*mul <= 10000)
        {
            counting[i*mul]++;
            mul++;
        }
    }

    int min = 100000;
    int calc = 0;
    for(int i=M;i<=N;i++){
        if(counting[i]==2){
            calc+=i;
            if(min>=i){
                min = i;
            }
        }
    }

    if(calc==0){
        cout<<-1;
    }else{
        cout<<calc<<'\n'<<min;
    }
}