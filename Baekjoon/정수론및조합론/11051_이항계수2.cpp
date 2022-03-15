#include<iostream>
using namespace std;

// DP를 사용해야하는구나
// 근데 DP 사용한 뒤에도 많이 틀렸는데, 왜 틀렸는지 모르겠음
int combination[1001][1001];

int N,K;
int main(){
    cin>>N>>K;

    if(N==0){
        cout<<0<<endl;
        return 0;
    }


    for(int i=1;i<=N;i++){
        for(int j=0;j<=K;j++){
            if(j==0) combination[i][j]=1;
            else if(i==j) combination[i][j]=1;
            else combination[i][j] = combination[i-1][j]+combination[i-1][j-1];
            combination[i][j]%=10007;
        }
    }

    /*
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            cout<<combination[i][j]<<' ';
        }
        cout<<endl;
    } 
    */
    cout<<combination[N][K]%10007;
}

/* 런타임오류
long long N,K;

int gcd(int a,int b){
    int n;
    while(b!=0){
        n = a%b;
        a = b;
        b = n;
    }
    return a;
}

int main(){
    cin>>N>>K;

    long long fact1 = 1;
    long long fact2 = 1;

    int nIndex=N-K+1;
    int kIndex=2;
    
    while(true){
        if(nIndex<=N){
            fact1*=nIndex;
            nIndex++;
        }

        if(kIndex<=K){
            fact2*=kIndex;
            kIndex++;
        }

        int GCD = gcd(fact1,fact2);
        fact1/=GCD;
        fact2/=GCD;

        if(nIndex>N && kIndex>K){
            break;
        }
    }
    cout<<(fact1/fact2)%10007;
}
*/