// https://www.acmicpc.net/problem/3009
// 세 점이 주어졌을 때 축에 평행한 직사각형을 만들기 위해 필요한 네 번째 점의 좌표 구하기
// 직사각형이기때문에 네 번째 점의 좌표는 다른 두 점의 x, y와 똑같을 수밖에 없다.
#include<iostream>
using namespace std;
int main(){
    int aX,bX,cX;
    int aY,bY,cY;
    cin>>aX>>aY>>bX>>bY>>cX>>cY;


    int resultX;
    if(aX==bX){
        resultX=cX;
    }else if(bX==cX){
        resultX=aX;
    }else{
        resultX=bX;
    }
    int resultY;
    if(aY==bY){
        resultY=cY;
    }else if(bY==cY){
        resultY=aY;
    }else{
        resultY=bY;
    }
    cout<<resultX << " "<<resultY;

}