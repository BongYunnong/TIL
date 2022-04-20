// https://www.acmicpc.net/problem/3273

// 처음에는 투포인터로 풀려고했는데, 잘 안돼서 계속 해보니 이건 투포인터라기보다는 그냥 이중for문 쓴 느낌이다.
// 그래도 맞긴 맞았으니, 차라리 투 포인터로밖에 풀 수 없는 문제에서 공부를 하는 것이 좋겠다.

#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N,X;
    cin>>N;
    int* inputs = new int[N];
    for(int i=0;i<N;i++){
        cin>>inputs[i];
    }
    sort(inputs,inputs+N);

    cin>>X;
    int start=0;
    int end=1;
    int counting=0;
    for(start =0 ; start<N ; start++){
        end = start+1;
        while(inputs[start]+inputs[end] < X && end < N){
            end++;
        }
        if(end >= N){
            continue;
        }

        if(inputs[start]+inputs[end]== X){
            counting++;
        } 
    }
    cout<<counting;
}