#include<iostream>
using namespace std;

int T, N,M;


long long combination[31][31];

int main(){
    cin>>T;

    for(int i=0;i<31;i++){
        for(int j=0;j<=i;j++){
            if(i==0) combination[i][j] =1;
            else if(i==j) combination[i][j]= 1;
            else combination[i][j] = combination[i-1][j] + combination[i-1][j-1];
            //cout<<combination[i][j]<<'\t';
        }
        //cout<<'\n';
    }

    for(int i=0;i<T;i++){
        cin>>N>>M;
        cout<<combination[M][N]<<'\n';
    }
}