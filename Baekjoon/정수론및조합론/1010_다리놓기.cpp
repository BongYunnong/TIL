// https://www.acmicpc.net/problem/1010

// 다리를 겹치지 않게 잇는 문제

// 문제를 보면 알겠지만, M개중에서 N개를 중복 없이 고르면 된다.
// Combination[i][j] = Combination[i-1][j] + Combination[i-1][j-1]이라는 것을 제발 기억하자.
// 그냥 for문으로 Testcase마다 한번씩 다 계산을 해주면 아마 시간제한이 뜰 것이다.

// 그러니 이렇게 테스트케이스가 나뉘어져있으면 한번에 모든 값을 다 계산해두고 적절한 값을 찾는 방식을 생각해보자.

#include<iostream>
using namespace std;

int T, N,M;


long long combination[31][31];

int main(){
    cin>>T;

    for(int i=0;i<31;i++){
        for(int j=0;j<=i;j++){
            if(i==0) combination[i][j] =1;
            else if(i==j) combination[i][j]= 1;
            else combination[i][j] = combination[i-1][j] + combination[i-1][j-1];
            //cout<<combination[i][j]<<'\t';
        }
        //cout<<'\n';
    }

    for(int i=0;i<T;i++){
        cin>>N>>M;
        cout<<combination[M][N]<<'\n';
    }
}