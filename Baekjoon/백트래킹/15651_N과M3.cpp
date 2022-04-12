// https://www.acmicpc.net/problem/15651
// 자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성
// 1부터 N까지 자연수 중에서 M개를 고른 수열
// 같은 수를 여러 번 골라도 된다.

// 이전의 N과 M 문제와 다르게, visited를 사용하지 않는다.(중복 허용이기때문)

#include<iostream>
using namespace std;

int arr[10];
int N,M;

void dfs(int count){
    if(count==M){
        for(int i=0;i<M;i++){
            cout<<arr[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=1;i<=N;i++){
        arr[count]=i;
        dfs(count+1);
    }
}

int main(){
    cin>>N>>M;
    dfs(0);
}