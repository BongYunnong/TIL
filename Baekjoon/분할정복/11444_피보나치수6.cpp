#include<iostream>

using namespace std;


//n은 1,000,000,000,000,000,000보다 작거나 같은 자연수이다.
// long long 9,223,372,036,854,775,807

#include<vector>

typedef vector<vector<long long>> matrix;
const long long mod = 1000000007LL;
matrix operator*(const matrix &a, const matrix &b){
    int n = a.size();
    matrix c(n,vector<long long>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                c[i][j] += a[i][k]*b[k][j];
            }
            c[i][j] %=mod;
        }
    }
    return c;
}

int main(){
    long long n;
    cin>>n;

    if(n<=1){
        cout<<n;
    }else{
        matrix answer = {{1,0},{0,1}};
        matrix a = {{1,1},{1,0}};

        while(n>0){
            if(n%2==1){
                answer = answer*a;
            }
            a = a*a;
            n/=2;
        }
        cout << answer[0][1];
    }
}



// 피보나치 규칙1
// 피사노 주기
// 피보나치수를 K로 나눈 나머지는 항상 주기를 갖는다.
// 주기의 길이가 P이면, N번째 피보나치 수를 M으로 나눈 나머지는 N%P번째 피보나치수를 M으로 나눈 나머지와 같다.
// 추가 지식 : M=10^k라면, 주기는 항상 15*10^(k-1)이다.
// 위의 지식을 모른다 하더라도 주기를 구하는 코드를 이용해서 문제를 풀어내야한다.

// 피보나치 규칙2
// 행렬 이용
// [[1,1][1,0]]의 행렬과 [[F(n+1)][Fn]]을 곱하면 [[F(n+2)][F(n+1)]]이 된다.



/* 메모리 초과
#include<map>

long long mod = 1000000007;
map<long long, long long> d;

long long fibo(long long n){
    if(n<=0){
        return 0;
    }else if(n==1){
        return 1;
    }else if(n==2){
        return 1;
    }else if(d.count(n)>0){
        return d[n];
    }else{
        d[n] = (fibo(n-1)%mod+fibo(n-2)%mod)%mod;
        return d[n];
    }
}

int main(){
    long long n;
    cin>>n;
    cout<<fibo(n);
}
*/


/* 시간초과1
int Fibo(int n){
    if(n==0){
        return 0;
    }else if(n==1){
        return 1;
    }else{
        return ((Fibo(n-1)%mod) + (Fibo(n-2)%mod))%mod;
    }
}

*/

/* 시간초과 2

long long FiboResults[4];

int main(){
    long long n;
    cin>>n;
    //cout<<Fibo(n);
    long long result;
    FiboResults[0]=0;
    FiboResults[1] =1;
    FiboResults[2] =1;
    FiboResults[3] =2;
    for(int i=4;i<=n;i+=4){
        int a = FiboResults[0];
        int b = FiboResults[1];
        FiboResults[0] = ((FiboResults[2]%mod)+(FiboResults[3]%mod))%mod;
        FiboResults[1] = ((FiboResults[3]%mod)+(FiboResults[0]%mod))%mod;
        FiboResults[2] = ((FiboResults[0]%mod)+(FiboResults[1]%mod))%mod;
        FiboResults[3] = ((FiboResults[1]%mod)+(FiboResults[2]%mod))%mod;
        cout<<FiboResults[0]<<','<<FiboResults[1]<<','<<FiboResults[2]<<','<<FiboResults[3]<<'\n';
    }
    cout<<FiboResults[n%4];
}

*/