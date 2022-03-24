// https://www.acmicpc.net/problem/10809
// 알파벳 소문자로만 이루어진 단어 S가 주어졌을 때, 각 알파벳에 대해서 단어에 포함되어있는 경우에는 처음 등장하는 위치를, 포함되어있지 않으면 -1출력
#include<iostream>
using namespace std;
int main(){
    char input[101];
    for(int i=0;i<101;i++){
        input[i] = ' ';
    }
    cin>>input;

    // 이렇게 문자를 int로 바꾸는 방법을 잘 생각해두자.
    for(int i=(int)'a'; i<=(int)'z';i++){
        int founded=-1;
        for(int j=0;j<101;j++){
            if((int)input[j]==i){
                founded=j;
                break;
            }
        }
        cout<<founded<<' ';
    }
}