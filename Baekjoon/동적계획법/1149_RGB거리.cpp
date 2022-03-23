//https://www.acmicpc.net/problem/1149
//빨,초,파로 N개의 집을 칠해야한다.
// 1번 집의 색은 2번 집의 색과 같지 않다.
// N번 집의 색은 N-1번 집의 색과 같지 않다.
// i(2<=i<=N-1)번 집의 색은 i-1번, i+1번 집의 색과 같지 않아야 한다.

// 색을 칠하는 방법은 3가지이므로, 열을 3으로 하고, N개의 집을 칠해야 하니 행을 N으로 한다.
// costs[x][y]는 x번째 집을 y의 색을 사용해 칠할 때 최소값이 되어야한다.
// 그러기 위해서는 그 전 집을 칠한 색이 y가 아니어야 하고, 그 중 최소값에 y를 이용해 칠할 때 필요한 cost를 더해주면 된다.


#include<iostream>
#include <algorithm>
using namespace std;

int N;
int costs[1001][3]; 

int main(){
    cin>>N;

    costs[0][0]=0;
    costs[0][1]=0;
    costs[0][2]=0;

    for(int i=1;i<=N;i++){
        int red, green, blue;
        cin>>red>>green>>blue;
        costs[i][0] = min(costs[i-1][1],costs[i-1][2])+ red;
        costs[i][1] = min(costs[i-1][0],costs[i-1][2])+ green;
        costs[i][2] = min(costs[i-1][0],costs[i-1][1])+ blue;
    }

    cout<<min(costs[N][2],min(costs[N][0],costs[N][1]));
}


// 아래는 재귀를 사용해서 하나씩 다 해보는 방법이다.
// colored에 칠한 색을 다 저장해놓고, 어떤 색을 칠할때 colored를 설정 한 후에 다음 집을 칠하도록 재귀함수를 호출하고,
// 재귀함수가 끝나면 colored를 초기화하는 방법이다.
// 동적 계획법 문제에서는 재귀를 하면 하나같이 다 시간초과가 걸린다.
/* 시간초과
int N;
tuple<int,int,int> costs[1001]; 

long long minRes=100000000;
int results=0;

int* tmpResutls;

int* colored;
void recursive(int index){
    if(index==N){
        results=0;
        for(int i=0;i<N;i++){
            int color = colored[i];
            int tmpVal=0;
            switch (color)
            {
            case 0 :
                tmpVal= get<0>(costs[i]);
                break;
            case 1 :
                tmpVal= get<1>(costs[i]);
                break;
            case 2 :
                tmpVal= get<2>(costs[i]);
                break;
            default:
                break;
            }
            cout<<"+ "<<tmpVal;
            results += tmpVal;
        }
        cout<<"="<<results<<'\n';
        if(results<=minRes){
            minRes = results;
        }
        return;
    }

    for(int i=0;i<3;i++){
        if(index==0){
            colored[index]=i;
            recursive(index+1);
            colored[index]=-1;
        }else if(colored[index-1]!=i){
            colored[index]=i;
            recursive(index+1);
            colored[index]=-1;
        }
    }
}



int main(){
    cin>>N;

    colored = new int[N+1];
    tmpResutls = new int[N+1];
    for(int i=0;i<N;i++){
        int red, green, blue;
        cin>>red>>green>>blue;
        costs[i] = make_tuple(red,green,blue);
        tmpResutls[i]=-1;
    }

    recursive(0);
    cout<<minRes;
}
*/