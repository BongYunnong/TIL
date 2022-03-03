#include<iostream>
using namespace std;
int main(){
    int T;
    cin>>T;
    int H,W,N;
    for(int i=0;i<T;i++){
        cin>>H>>W>>N;
        
        int a = N/H+1;
        int b = N%H;

        if(b==0)
            cout<< H*100+a-1<<'\n';
        else
            cout<< b*100+a<<'\n';
    }
}