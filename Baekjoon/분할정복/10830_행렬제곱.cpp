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
            MatrixMul(Results,A);
        }
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