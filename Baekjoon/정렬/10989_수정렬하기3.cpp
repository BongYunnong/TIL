// https://www.acmicpc.net/problem/10989

// 오름차순으로 정렬

// 그냥 sort, merge sort 하면 시간초과, 메모리초과가 계속 뜬다.
// 반복하는 것이 많다면 그냥 counting을 해주는 것이 제일 좋은 방법인 듯 하다.

#include<iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;

    int* sorted = new int[10001];    
    for(int i=0;i<10001;i++){
        sorted[i]=0;
    }
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        sorted[tmp]++;
    }
    // 숫자를 세고, 그 수에 따라 반복 출력.
    for(int i=1;i<=10000;i++){
        while(sorted[i]>0){
            cout<<i<<'\n';
            sorted[i]--;
        }
    }
}