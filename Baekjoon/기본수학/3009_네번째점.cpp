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