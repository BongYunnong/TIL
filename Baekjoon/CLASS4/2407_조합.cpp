// https://www.acmicpc.net/problem/2407
// 파스칼의 법칙을 또 까먹었다.
//  nCm = n-1Cm-1 + n-1Cm (nCn = 1, nC0 = 1) 

// 원래는 unsigned long long으로 문제를 해결하려했지만, 그것을 아득히 초월한 값이 나올 수 있었기에, string으로 변환해서 풀어야했다.
// string의 덧셈은 10757 큰수A+B를 참고했다.

#include<iostream>
#include<string>
using namespace std;

string factorial[101][101];
    int n,m;

string ADD(string A, string B){
    int count = A.length();
    if(B.length()>count){
        count = B.length();
    }
    int x=0;
    int y=0;
    string C;
    int result=0;
    // 최대 자릿수가 될 때까지 각 자릿수+올림수를 더해서 C의 앞에 삽입하기
    for(int i=0;i<count;i++){
        if(A.length()<i+1){
            result = B[B.length()-1-i]-48+x;
        }
        else if(B.length()<i+1){
            result = A[A.length()-1-i]-48+x;
        }  
        else{
            int tmpA = A[A.length()-1-i]-48;
            int tmpB = B[B.length()-1-i]-48;         
            result = tmpA + tmpB+x;
        }
        x = result/10;  // x는 올림수
        y = result%10;  // y는 해당 자릿수
        C.insert(0,std::to_string(y));
    }
    if(x>0)
        C.insert(0,std::to_string(x));
    return C;
}

void combi(){
    factorial[0][0]="1";
    factorial[1][0]="1";
    factorial[1][1]="1";

    for(int i=2;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i==j || j==0){
                factorial[i][j]="1";
            }else{
                factorial[i][j]= ADD(factorial[i-1][j-1], factorial[i-1][j]);
            }
        }
    }
}

int main(){
    cin>>n>>m;

    combi();
    cout<<factorial[n][m];
}

/* 100, 50을 넣으면 unsigned long long으로도 표현하지 못하는 값이 나옴
#include<iostream>

using namespace std;

unsigned long long  gcd(unsigned long long  a, unsigned long long  b){
    unsigned long long  n;
    while(b!=0){
        n = a%b;
        a=b;
        b=n;
    }
    return a;
}

int main(){
    int n,m;
    cin>>n>>m;

    unsigned long long iresult=1;
    unsigned long long jResult=1;
    for(int i=1;i<=n;i++){
        if(i>=n-m+1){
            iresult*=i;
        }
        if(i<=m){
            jResult*=i;
        }

        unsigned long long  GCD = gcd(iresult,jResult);
        iresult/=GCD;
        jResult/=GCD;
    }
    cout<<iresult;
}
*/