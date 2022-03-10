#include<iostream>
using namespace std;

int T;
long long* results;

int main(){
    cin>>T;
    results = new long long[101];
    results[0]=0;
    results[1]=1;
    results[2]=1;
    results[3]=1;
    
    for(int i=3;i<=101;i++){
        results[i] = results[i-2]+results[i-3];
        //cout<<"i : "<<i<<"_"<<results[i-2]<<"__"<<results[i-3]<<" = "<<results[i]<<'\n';
    }
    for(int i=0;i<T;i++){
        int tmp;
        cin>>tmp;

        cout<<results[tmp]<<'\n';
    }
}