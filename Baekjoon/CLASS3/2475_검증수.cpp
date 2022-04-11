// https://www.acmicpc.net/problem/1259
// 문제만 따라가면 맞춤
#include<iostream>
using namespace std;

int main(){
    int result=0;
    for(int i=0;i<5;i++){
        int tmp;
        cin>>tmp;

        result+= tmp*tmp;
    }

    cout<<result%10;
}