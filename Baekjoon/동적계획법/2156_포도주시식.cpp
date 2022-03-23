// https://www.acmicpc.net/problem/2156
// 포도주 시식회
// 1. 포도주 잔을 선택하면 그 잔에 있는 포도주는 모두 마셔야하고, 마신 후에는 원래 위치에 놓아야 한다.
// 2. 연속으로 놓여 있는 3잔을 모두 마실수는 없다.
// 가장 많은 포도주를 맛보려면 어떻게 포도주 잔을 선택해야할까?

// F(N) = max(F(N-1),F(N-2)+arr[N],F(N-3)+arr[N-1]+arr[N]))
// 연속으로 3잔을 마실 수는 없으니, 지금거를 안 먹거나, N-1을 안 먹거나, N-2를 안 먹거나 3중의 하나이다.

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
        // results[i-3]+costs[i-2]+costs[i-1] 이걸 생각 못함 == results[i-1]
        // 계단의 경우에는 마지막 칸을 꼭  밟아야 하기에 이것이 없었나봄
        results[i] = max(results[i-1], max(results[i-3]+costs[i-1]+costs[i], results[i-2]+costs[i]));
    }

    cout<<results[N];
}