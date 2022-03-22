// https://www.acmicpc.net/problem/2581
// a층의 b호에 살려면 자신의 아래층(a-1)의 1호부터 b호까지 사람 수 합만큼 사람들을 데려와야한다.
// k층에 n호에는 몇 명이 살고있을까?
// 아파트는 0층부터 있고, 각 층은 1호부터 있으며 0층 i호에는 i명의 사람이 산다.

// 그림을 그려보면 더 간단하게 패턴을 알 수 있다.

#include<iostream>
using namespace std;

int getCount(int _k,int _n){
    // 0 층에는 호실 값 만큼의 사람 수
    if(_k==0)
        return _n;
    // 1호에 사는 사람은 모두 1명임 
    if(_n<=1)
        return 1;

    // 어떠한 층에 사는 사람 수 = 자신의 아래층에 사는 사람의 수 + 자신의 왼편이 사는 사람의 수([k-1,n-1]까지 사는 사람의 수를 다 더한 사람 수)
    return getCount(_k-1,_n) + getCount(_k,_n-1);
}
int main(){
    int T;
    cin>>T;
    int k,n;
    for(int i=0;i<T;i++){
        cin>>k>>n;
        cout<<getCount(k,n)<<endl;
    }
}