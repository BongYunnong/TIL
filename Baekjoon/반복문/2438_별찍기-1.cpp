// https://www.acmicpc.net/problem/2438
// N번째 줄에 별 N개 찍기

//*
//**
//***
//****
//*****

#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    int t;
    cin >> t;

    for(int i=1;i<=t;i++){
        for(int j=0;j<i;j++){
            cout<<'*';
        }
        cout<<'\n';
    }
}