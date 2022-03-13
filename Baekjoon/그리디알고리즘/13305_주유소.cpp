//https://www.acmicpc.net/problem/13305
#include<iostream>
using namespace std;

int N;

int* dists;
int* gasValues;

int remainGas=0;
long minGasValue=1000000000;
int main(){
    cin>>N;

    dists = new int[N-1];
    gasValues = new int[N];
    for(int i=0;i<N-1;i++){
        cin>>dists[i];
    }
    for(int i=0;i<N;i++){
        cin>>gasValues[i];
    }
    long costs=0;
    for(int i=0;i<N-1;i++){
        if(minGasValue > gasValues[i]){
            minGasValue= gasValues[i];
        }

        costs += minGasValue*dists[i];

    }
    cout<<costs;
}