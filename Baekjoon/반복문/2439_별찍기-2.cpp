// https://www.acmicpc.net/problem/2439
// 별 N개를 찍되, 오른쪽 기준으로 정렬하기

//    *
//   **
//  ***
// ****
//*****

// N-i만큼 공백을 주면 됨
#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    int t;
    cin >> t;

    for(int i=1;i<=t;i++){
        for(int j=t-1;j>=0;j--){
            if(j<i)
                cout<<'*';
            else
                cout<<' ';
        }
        cout<<'\n';
    }
}