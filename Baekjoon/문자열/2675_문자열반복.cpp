// https://www.acmicpc.net/problem/2675
// 문자열 S를 입력받고 각 문자를 R번 반복하여 새 문자열 P를 만든 후 출력
#include<iostream>
#include <cstring>
using namespace std;
int main(){
    string S;
    int t,r;
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>r;
        cin>>S;
        for(int j=0;j<S.length();j++){
            for(int k=0;k<r;k++){
                cout<<S[j];
            }
        }
        cout<<'\n';
    }
}