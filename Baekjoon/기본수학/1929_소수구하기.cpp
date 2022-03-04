#include<iostream>
using namespace std;
int main(){
    long M,N;
    cin>>M>>N;


    int counting[1000001]={};
    for(int i=1;i<1000001;i++){
        int mul=1;
        while (i*mul <= 1000000)
        {
            counting[i*mul]++;
            mul++;
        }
    }

    for(int i=M;i<=N;i++){
        if(counting[i]==2){
            cout<<i<<'\n';
        }
    }

}