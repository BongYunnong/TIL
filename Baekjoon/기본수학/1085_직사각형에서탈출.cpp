//https://www.acmicpc.net/problem/1085
// x,y에 있는 점이 w,h 크기의 직사각형의 경계선으로 가는 최소 값
#include<iostream>
using namespace std;
int main(){
    int x,y;
    int w,h;
    cin>>x>>y>>w>>h;

    int min=x;
    if(y<=min)
        min =y;
    if(abs(w-x)<min)
        min = abs(w-x); 
    if(abs(h-y)<min)
        min = abs(h-y);

    cout<<min; 
}