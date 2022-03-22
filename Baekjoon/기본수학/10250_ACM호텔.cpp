//https://www.acmicpc.net/problem/10250
// 호텔 정문으로부터 걷는 거리가 가장 짧도록 방을 배정하자.

// W개의 방이 있는 H층 건물. 엘레베이터는 가장 왼쪽에 있음. 
// N번째 도착한 손님의 호실 번호 출력

#include<iostream>
using namespace std;
int main(){
    int T;
    cin>>T;
    int H,W,N;
    for(int i=0;i<T;i++){
        cin>>H>>W>>N;
        
        int a = N/H+1;  // 층 내의 호실 번호
        int b = N%H;    // 층 
        // 엘레베이터에서 가장 가까운 방을 선호하므로, 손님 번호 N을 층수로 나눠야함
        // 사실상 W는 필요가 없다.
        if(b==0)
            cout<< H*100+a-1<<'\n'; // 나머지를 계산했기에 나머지가 0이라면 맨 끝 층인 H가 되어야 한다.
        else
            cout<< b*100+a<<'\n';
    }
}