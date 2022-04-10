// https://www.acmicpc.net/problem/10844

// 45656은 계단수이다. 인접한 모든 자리의 차이가 1이기 때문이다.
// N이 주어질 때, 길이가 N인 계단 수가 총 몇 개 있는가?
// 0으로 시작하느 수는 계단수가 아니다.

// 구글링으로 이해함..
// F(i,j) = i의 길이를 가지고 j로 끝나는 수의 가짓수
// F(i,j) = F(i-1,j-1) + F(i-1,j+1)
// 해석해보면, i보다 길이가 1 작고, j보다 1 작거나 1이 커야 다음에 j가 될 수 있으니, 그 두 가짓수를 더하겠다는 것이다.
// 이때 j-1, j+1이 0에서 9까지의 값이어야 하니, j가 0이라면 F(i-1,j+1)이 값이 되고, j가 9라면 F(i-1,j-1)이 답이 된다.
// 마지막에는 모든 수를 다 써놓으면 된다.

#include<iostream>
using namespace std;
#define DIV 1000000000
int N;
long long results[101][11];
long long Result;
int main(){
    cin>>N;
    for(int i=1;i<=9;i++){
        results[1][i] = 1;
    }
    // 0으로 시작하는 값은 없음
    results[1][0]=0;


    for(int i=2;i<=N;i++){
        for(int j=0;j<=9;j++){
            if(j==0)
                results[i][j] = results[i-1][j+1]%DIV;
            else if(j==9)
                results[i][j] = results[i-1][j-1]%DIV;
            else
                results[i][j] = (results[i-1][j+1] + results[i-1][j-1])%DIV;
        }
    }

    Result=0;
    for(int i=0;i<10;i++){
        Result+= results[N][i];
    }
    cout<<Result%DIV;
}

/* 틀림
#define MAX 101
int N;
long long results[MAX];

long long ResCount=0;
int currNum;
void Recursive(int _index){
    if(_index==N){
        ResCount++; 
        return;
    }

    if(_index==0){
        for(int i=1;i<=9;i++){
            currNum=i;
            Recursive(_index+1);
        }
    }else{
        if(currNum>1){
            currNum--;
            Recursive(_index+1);
        }

        if(currNum<9){
            currNum++;
            Recursive(_index+1);
        }
    }
}

int main(){
    cin>>N;

    Recursive(0);
    cout<<(ResCount%1000000000);
}
*/