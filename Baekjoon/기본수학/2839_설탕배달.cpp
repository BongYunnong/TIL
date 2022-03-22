//https://www.acmicpc.net/problem/2839

// N킬로그램을 배달해야하는데, 봉지는 3킬로그램과 5킬로그램이 있다.
// 최소의 봉지 개수는? (못 만든다면 -1)
#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;

    // i는 5킬로그램 봉지를 몇 개 사용할 것인가임.
    // 5킬로그램 봉지를 많이 쓰는 경우부터 계산
    for(int i=N/5;i>=0;i--){
        int remain = N-i*5;
        // 5킬로 봉지를 쓰고 남은 것이 3으로 나누어진다면? -> 5킬로그램 봉지를 먼저 사용했기에 무조건 최소의 값이 나온다.
        if(remain%3==0){
            cout<< i+remain/3;
            return 0;

        }
    }

    cout<<-1;
}