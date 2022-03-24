// https://www.acmicpc.net/problem/5622
// 다이얼을 걸기 위해서 필요한 최소 시간

// 처음에 이 문제를 못 풀었던거같음 각 숫자가 3개씩인 줄 알았기 때문임
// 사실은 3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,8,9,9,9,10,10,10,10 이렇게 4개씩 있는 값도 있음

#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;
    cin>>s;
    int result=0;
    int score[26]={3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,8,9,9,9,10,10,10,10};

    for(int i=0;i<s.length();i++){
        result += score[s[i]-65];
    }
    cout<<result;
}