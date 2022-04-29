// https://www.acmicpc.net/problem/2096

// DP를 사용하면 쉽게 풀 수 있다.

#include<iostream>
using namespace std;

int N;

int grid[100001][3];
int result[2][3];
int minResult[2][3];

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;
    for(int i=0;i<N;i++){
        int a,b,c;
        cin>>a>>b>>c;
        grid[i][0]=a;
        grid[i][1]=b;
        grid[i][2]=c;

        if(i==0){
            result[i][0]=a;
            result[i][1]=b;
            result[i][2]=c;
            minResult[i][0]=a;
            minResult[i][1]=b;
            minResult[i][2]=c;
        }
    }

    for(int i=1;i<N;i++){
        result[1][0]= max(result[0][0],result[0][1])+grid[i][0];
        result[1][1]= max(result[0][0],max(result[0][1],result[0][2]))+grid[i][1];
        result[1][2]= max(result[0][1],result[0][2])+grid[i][2];

        minResult[1][0]= min(minResult[0][0],minResult[0][1])+grid[i][0];
        minResult[1][1]= min(minResult[0][0],min(minResult[0][1],minResult[0][2]))+grid[i][1];
        minResult[1][2]= min(minResult[0][1],minResult[0][2])+grid[i][2];

        result[0][0] = result[1][0];
        result[0][1] = result[1][1];
        result[0][2] = result[1][2];
        minResult[0][0] = minResult[1][0];
        minResult[0][1] = minResult[1][1];
        minResult[0][2] = minResult[1][2];
    }
    cout<< max(result[0][0],max(result[0][1],result[0][2]));
    cout<<' ';
    cout<< min(minResult[0][0],min(minResult[0][1],minResult[0][2]));
}