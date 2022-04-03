// https://www.acmicpc.net/problem/15652
// 자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성
// 1부터 N까지 자연수 중에서 M개를 고른 수열
// 같은 수를 여러 번 골라도 된다.
// 고른 수열은 비내림차순 (길이가 K인 수열 A가 A1 ≤ A2 ≤ ... ≤ AK-1 ≤ AK를 만족)

#include<iostream>
using namespace std;

int N,M;
int arr[10];
void dfs(int index,int num){
    if(index==M){
        for(int i=0;i<M;i++){
            cout<<arr[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=1;i<=N;i++){
        // 비내림차순이 되도록
        if(i>=num){
            arr[index]=i;
            dfs(index+1,i);
        }
    }
}

int main(){
    cin>>N>>M;
    dfs(0,1);
}