// https://www.acmicpc.net/problem/1152
// 영어 대소문자와 공백으로 이루어진 문자열이 주어졌을 때, 이 문자열에 몇 개의 단어가 있을까?
// 한 단어가 여러번 등장하면 등장한 횟수만큼 모두 세어야한다.



#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;
    // getLine 사용법을 잘 알아두자.
    getline(cin,s);
    int count=1;

    // 아무것도 없을 때
    if(s.length()<=0){
        cout<<0;
        return 0;
    }

    // 공백의 개수를 셈
    for(int i=0;i<s.length();i++){
        if(s[i]==' ')
            count++;
    }

    // 처음, 끝에 공백이 있으면 하나씩 제외
    if(s[0]==' ')
        count--;
    if(s[s.length()-1]==' ')
        count--;
    cout<<count;
}