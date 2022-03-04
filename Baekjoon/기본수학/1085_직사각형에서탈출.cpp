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