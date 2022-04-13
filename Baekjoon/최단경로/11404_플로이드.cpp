// https://www.acmicpc.net/problem/11404

// 플로이드 알고리즘
// 다익스트라는 한 점에서부터 다른 모든 점까지를 구하지만,
// 플로이드 알고리즘은 모든 점에서 모든 점까지를 구한다.

#include<iostream>
#include<vector>
using namespace std;
#define MAX 100000000

int result[101][101];
int main(){
    int n;
    cin>>n;

    int m;
    cin>>m;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            result[i][j]=MAX;
            if(i==j){
                result[i][j]=0;
            }
        }
    }

    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        result[a-1][b-1]=min(result[a-1][b-1],c);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // 모든 도시에 대해서
            for(int k=0;k<n;k++){
                // 다른 모든 도시까지
                result[j][k] = min(result[j][k],result[j][i]+result[i][k]);
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(result[i][j]==MAX){
                cout<<0<<' ';
            }else{
                cout<<result[i][j]<<' ';
            }
        }
        cout<<'\n';
    }
}