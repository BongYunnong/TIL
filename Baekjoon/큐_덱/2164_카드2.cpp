// https://www.acmicpc.net/problem/2164

// 1번 카드가 제일 위에, N번 카드가 제일 아래인 상태로 순서대로 카드가 놓여 있다.
// 다음과 같은 동작을 카드가 한 장 남을 때까지 반복하게 된다.
// 우선, 제일 위에 있는 카드를 바닥에 버린다.
// 그 다음, 제일 위에 있는 카드를 제일 아래에 있는 카드 밑으로 옮긴다.

// N이 주어졌을 때, 제일 마지막에 남게 되는 카드를 구하는 프로그램을 작성하시오.

// 그냥 요구하는대로 구현해주면 된다.

#include<iostream>
#include<queue>

using namespace std;

int main(){
    int N;
    cin>>N;

    queue<int> q;
    for(int i=1;i<=N;i++){
        q.push(i);
    }
    while (q.size()>1)
    {
        q.pop();
        if(q.size()>1){
            int val = q.front();
            q.push(val);
            q.pop();
        }
    }
    cout<<q.front();
}