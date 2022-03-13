#include<iostream>
using namespace std;


int N,K;
int values[1000001];
int main(){
    cin>>N>>K;

    for(int i=0;i<N;i++){
        cin>>values[i];
    }

    int count=0;
    for(int i=N-1;i>=0;i--){
        if(K/values[i] > 0){
            int mul = (K/values[i]);
            K -= mul * values[i];
            //cout<<"value:"<<values[i]<<endl;
            count+=mul;
        }
    }
    cout<<count;
}