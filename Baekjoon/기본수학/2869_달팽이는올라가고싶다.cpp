#include<iostream>
using namespace std;
int main(){
    int A,B,V;
    cin>>A>>B>>V;
    int dist = A-B;
    int calculatedV = V-A;
    if(calculatedV%dist==0){
        cout<<calculatedV/dist+1;
    }else{
        cout<<calculatedV/dist+2;
    }
}