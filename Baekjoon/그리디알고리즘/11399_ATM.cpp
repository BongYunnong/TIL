// https://www.acmicpc.net/problem/11399
// ATM에서 각 사람이 돈을 인출하는데 필요한 시간의 합의 최소값

// 가장 빨리 돈을 인출하는 사람이 먼저 돈을 인출하면 된다.
#include <iostream>
#include <algorithm>
using namespace std;

int N;
int* times;
int main(){
    cin>>N;
    times = new int[N+1];
    for(int i=0;i<N;i++){
        cin>>times[i];
    }

    // 걸리는 시간을 오름차순으로 정렬
    sort(times,times+N);

    int answer=times[0];
    for(int i=1;i<N;i++){
        // 다음 사람이 돈을 인출하는데에 걸리는 시간은 지금까지 걸린 시간 + 자신이 돈을 인출하는데에 걸리는 시간이다.
        times[i] = times[i-1]+times[i];
        answer+=times[i];
    }
    cout<<answer;
}