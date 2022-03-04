#include<iostream>
using namespace std;
int main(){
    long M;

    int counting[500001]={};
    for(int i=1;i<500001;i++){
        int mul=1;
        while (i*mul <= 500000)
        {
            counting[i*mul]++;
            mul++;
        }
    }

    while(true){
        cin>>M;
        if(M==0)
            return 0;

        int result=0;
        for(int i=M+1;i<=2*M;i++){
            if(counting[i]==2){
                result++;
            }
        }
        cout<<result<<'\n';
    }
}