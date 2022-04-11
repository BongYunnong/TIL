// https://www.acmicpc.net/problem/11660
// 누적합을 저장하고, 큰 사각형에서 작은 사각형 2개를 뺀 후 겹친 사각형을 더하는 방식

#include<iostream>
using namespace std;

int N,M;
int grid[1025][1025];
int sum[1025][1025];
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;

    for(int i=1;i<=N;i++){
        int rowSum=0;
        for(int j=1;j<=N;j++){
            cin>>grid[i][j];
            rowSum += grid[i][j];
            if(i==1 && j==1){
                sum[i][j]=grid[i][j];
            }else if(i==1){
                sum[i][j] = sum[i][j-1]+grid[i][j];
            }else if(j==1){
                sum[i][j] = sum[i-1][j]+grid[i][j];
            }else{
                sum[i][j] = sum[i-1][j] +rowSum;
            }
        }
    }



    for(int i=0;i<M;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        x1--;
        y1--;
        int result= sum[x2][y2]-sum[x2][y1]-sum[x1][y2]+sum[x1][y1];
        cout<<result<<'\n';
        
    }
}