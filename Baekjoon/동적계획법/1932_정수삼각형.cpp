#include<iostream>
#include <algorithm>
using namespace std;

int N;
int costs[501][501]; 

int floorCosts[501];

int main(){
    cin>>N;

    for(int i=0;i<N;i++){
        if(i==0){
            cin>>costs[0][0];
        }else{
            for(int j=0;j<=i;j++){
                cin>>floorCosts[j];
            }

            costs[0][i] = costs[0][i-1]+floorCosts[0];
            costs[i][i] = costs[i-1][i-1] + floorCosts[i];
            for(int j=1;j<i;j++){
                costs[j][i]=max(costs[j-1][i-1],costs[j][i-1])+floorCosts[j];
            }
        }
    }

    long long maxRes = -10000000;
    for(int i=0;i<N;i++){
        if(costs[i][N-1]>=maxRes)
            maxRes=costs[i][N-1];
    }

    cout<<maxRes;
}
