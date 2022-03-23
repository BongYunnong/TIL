//https://www.acmicpc.net/problem/1463
// 1.x가 3으로 나누어떨어지면 3으로 나눔
// 2.x가 2로 나누어떨어지면 2로 나눔
// 3.1을 뺌
// 위 3가지 연산을 활용해서 정수 N을 1로 만들기.

// N이 뭐가 올 지 모르니 2로 나누고 3으로 나누는 연산으로 표를 만들기는 어렵다.
// 그렇다면, F(N)이 뭐일지를 생각해보자.
// N이 3으로 나누어진다면, F(3n) = F(n)+1일테고,
// N이 2로 나누어진다면, F(2n) = F(n)+1일테며,
// 어떤 경우에는 F(N) = F(N-1)+1일 것이다.
// 동적 계획법이기 떄문에, 우리는 이 3가지의 값의 최소만을 Result 배열에 넣어주면 된다.
// 미리 계산할 수 있는 정도는 써놓고, 그 이후부터는 for문을 돌면서 최소가 되도록 계산을 해준다.


#include <iostream>
using namespace std;
# define MAX 1000001
long N;

int results[MAX];
int main(){
    cin>>N;

    results[1]=0;
    results[2]=1;
    results[3]=1;
    results[4]=2;

    for(int i=4;i<=N;i++){
        int oper1 = MAX;
        int oper2 = MAX;
        int oper3 = results[i-1];
        if(i%3==0)
            oper1 = results[i/3];
        if(i%2==0)
            oper2 = results[i/2];
        
        results[i] = min(min(oper1, oper2) , oper3)+1;
    }
    cout<<results[N];
}