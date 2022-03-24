// https://www.acmicpc.net/problem/1157
// 알파벳 대소문자로 이루어진 단어가 주어지면 가장 많이 사용된 알파벳 알아내기

#include<iostream>
#include<cstring>
using namespace std;

int main(){
    string s;
    cin>>s;

    // 알파벳 숫자만큼의 크기를 가진 배열
    int count[32];
    for(int i=0;i<32;i++){
        count[i] = 0;
    }

    for(int i=0;i<s.length();i++){
        if(s[i]>=97 && s[i] <= 122){        // a~z
            count[s[i]-97]++;
        }else if(s[i]>=65 && s[i]<=90){     // A~Z
            count[s[i]-65]++;
        }
    }

    int max=-10;
    int index=-1;
    for(int i=0;i<32;i++){
        if(max < count[i]){
            max = count[i];
            index=i;
        }else if(max==count[i]){
            index=-1;
        }
    }

    if(index>=0)
        cout<<(char)(index+65);
    else 
        cout<<'?';
}