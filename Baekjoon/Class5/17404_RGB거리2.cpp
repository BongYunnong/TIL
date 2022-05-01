// 사실 색을 하나씩 다 써보는 것도 생각해보지 못했을 뿐더러 가로채는 것을 생각지 못했다. 

#include<iostream>
using namespace std;

int d[1001][3];
int grid[1001][3];
int main(){
    int N;
    cin>>N;

    for(int i=1;i<=N;i++){
        for(int j=0;j<3;j++){
            cin>>grid[i][j];
        }
    }
    int ans = 987654321;

    for(int k=0;k<3;k++){
        for(int i=0;i<3;i++){
            if(i==k)
                d[1][i]=grid[1][i];
            else
                d[1][i]=987654321;
        }

        for(int i=2;i<=N;i++){
            d[i][0] = min(d[i-1][1],d[i-1][2])+grid[i][0];
            d[i][1] = min(d[i-1][0],d[i-1][2])+grid[i][1];
            d[i][2] = min(d[i-1][0],d[i-1][1])+grid[i][2];
        }

        for(int i=0;i<3;i++){
            if(i==k)
                continue;
            ans = min(ans,d[N][i]);
        }
    }
    cout<<ans<<"\n";
}