// https://www.acmicpc.net/problem/10872

// 이건 재귀라기보단... 그냥 팩토리얼 계산하면 된다.

#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;

    int result=1;
    for(int i=1;i<=N;i++){
        result*=i;
    }
    cout<<result;
}