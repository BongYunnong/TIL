// https://www.acmicpc.net/problem/9461
// 삼각형이 나선 모양으로 놓아져있다.
// 첫 삼각형의 정삼각형 변의 길이는 1
// 가장 긴 변의 길이를 k라 했을 때, 그 변에 길이가 k인 정삼각형 추가
// 파도반 수열 P(N) : 나선에 있는 정삼각형 변의 길이 
// ex. 1, 1, 1, 2, 2, 3, 4, 5, 7, 9

// 직접 써보면 패턴을 파악할 수 있다. 
// 1. F(N) = F(N-2) + F(N-3)
// 2. F(N) = F(N-1) + F(N-5)

#include<iostream>
using namespace std;

int T;
long long* results;

int main(){
    cin>>T;
    results = new long long[101];
    results[0]=0;
    results[1]=1;
    results[2]=1;
    results[3]=1;
    results[4]=2;
    results[5]=2;
    
    for(int i=6;i<=101;i++){
        results[i] = results[i-1]+results[i-5];
    }
    for(int i=0;i<T;i++){
        int tmp;
        cin>>tmp;

        cout<<results[tmp]<<'\n';
    }
}

/* 맞은 코드 2
int T;
long long* results;

int main(){
    cin>>T;
    results = new long long[101];
    results[0]=0;
    results[1]=1;
    results[2]=1;
    results[3]=1;
    
    for(int i=3;i<=101;i++){
        results[i] = results[i-2]+results[i-3];
        //cout<<"i : "<<i<<"_"<<results[i-2]<<"__"<<results[i-3]<<" = "<<results[i]<<'\n';
    }
    for(int i=0;i<T;i++){
        int tmp;
        cin>>tmp;

        cout<<results[tmp]<<'\n';
    }
}
*/