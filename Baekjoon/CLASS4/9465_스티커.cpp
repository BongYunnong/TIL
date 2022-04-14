// 접근법은 맞았는데, max부분에서 틀렸나보다.
// grid[0][k]+ max(result[0][k-2]+grid[1][k-1] ,result[1][k-2]); 이것이 내가 한 것이고
// grid[0][k]+ max(result[1][k-1] ,result[1][k-2]); 이것이 답인데,
// result[0][k-2]+grid[1][k-1]이 result[1][k-1]로 축약이 되었는가 아닌가의 차이다.
// 나는 k가 2부터 시작하니까 당연히 예외없이 작동할 것이라 생각했는데, 내 예상으로는 result[1][k-1]에 result[0][k-2]+grid[1][k-1] 이것 이외에도 다른 값도 이미 계산되어있을 수 있겠다는 생각이 든다.
//예를 들면 result[0][k-3]에서 바로 왔다거나...

// 뭐, 그래도 답을 도출하는 것에는 문제가 없었다고 생각해서 나는 만족한다.

#include<iostream>
using namespace std;

int grid[2][100001];
int result[2][100001];
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N;
        cin>>N;
        for(int j=0;j<N;j++){
            cin>>grid[0][j];
        }
        for(int j=0;j<N;j++){
            cin>>grid[1][j];
        }

        result[0][0] = grid[0][0];
        result[1][0] = grid[1][0];
        result[0][1] = result[1][0]+grid[0][1];
        result[1][1] = result[0][0]+grid[1][1];

        for(int k=2;k<N;k++){
                for(int j=0;j<2;j++){
                //cout<<"j"<<j<<" k"<<k<<' ';
                if(j==0){
                    result[0][k] = grid[0][k]+ max(result[1][k-1] ,result[1][k-2]);
                    //cout<<result[0][k]<<'\n';
                }else{
                    result[1][k] = grid[1][k] + max(result[0][k-1], result[0][k-2]);
                    //cout<<result[1][k]<<'\n';
                }
            }
        }
        int answer = max(result[0][N-1],result[1][N-1]);
        cout<<answer<<'\n';
    }
}