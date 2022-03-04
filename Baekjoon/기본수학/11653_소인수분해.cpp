#include<iostream>
using namespace std;
int main(){
    long N;
    cin>>N;

    int mul=2;
    while(N!=1){
        if(N%mul==0){
            cout<<mul<<'\n';
            N/=mul;
        }else{
            mul++;
        }
    }

}