#include<iostream>
using namespace std;

int N;

int costs[10001];
int results[10001];

int main(){
    cin >> N;
    for(int i=1;i<=N;i++){
        cin>>costs[i];
    }


    results[1] = costs[1];
    results[2] = costs[1]+costs[2];
    for(int i=3;i<=N;i++){
        // results[i-3]+costs[i-2]+costs[i-1] 이걸 생각 못함
        // 계단의 경우에는 마지막 칸을 꼭  밟아야 하기에 이것이 없었나봄
        results[i] = max(results[i-1], max(results[i-3]+costs[i-1]+costs[i], results[i-2]+costs[i]));
    }

    cout<<results[N];
}