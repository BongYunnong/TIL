#include<iostream>
using namespace std;
int main(){
    int T;
    cin>>T;

    int counting[10001]={};
    for(int i=1;i<10001;i++){
        int mul=1;
        while (i*mul <= 10000)
        {
            counting[i*mul]++;
            mul++;
        }
    }

    int n;
    for(int i=0;i<T;i++){
        cin>>n;

        for(int j=n/2;j>1;j--){
            if(counting[j]==2){
                if(counting[n-j]==2){
                    cout<<j << " "<<n-j<<'\n';
                    break;
                }
            }
        }
    }   
}