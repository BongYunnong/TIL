// https://www.acmicpc.net/problem/10830

// 크기가 N*N인 행렬 A
// A의 B제곱을 구하는 프로그램
// 수가 매우 커질 수 있으니, A^B의 각 원소를 1,000으로 나눈 나머지를 출력

// 지수법칙과 모듈러 법칙을 생각하자.

#include<iostream>
using namespace std;

long long N,B;
int A[5][5];
int Results[5][5];
int tmp[5][5];

void MatrixMul(int a[5][5], int b[5][5]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            tmp[i][j]=0;
            for(int k=0;k<N;k++){
                tmp[i][j] += a[i][k]*b[k][j];
            }
            tmp[i][j]%=1000;
        }
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            a[i][j] = tmp[i][j];
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N>>B;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>A[i][j];
        }
        Results[i][i]=1;
    }

    while(B!=0){
        if(B%2==1){
            // 2로나눈 나머지가 1일 경우, 지금까지 계산된 A를 Result에 미리 곱해둠
            // 2로 계속 나누면 나머지가 1일테니(ex. 8->4->2-1) 자동으로 계산이 됨
            MatrixMul(Results,A);
        }
        // A에 A*A 결과 넣기
        MatrixMul(A,A);
        B/=2;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<Results[i][j]<<' ';
        }
        cout<<'\n';
    }

}