//https://www.acmicpc.net/problem/1904
// 타일은 0 또는 1이 쓰여있는 낱장의 타일들이다.
// 0이 쓰여진 낱장의 타일을 붙여서 00타일을 만들었다.
// 결국 1 타일과 00타일들만 남았다.
// N=1일때 1만 만들 수 있고, N=2일때는 00,11을 만들 수 있으며, N=4일때는 0011,0000,1001,1100,111 총 5개의 2진 수열을 만들 수 있다.
// N이 주어졌을 때 만들 수 있는 모든 가짓수는?

// 솔직히 왜인지는 모르겠는데, 공책에 써내려가보면
// N=1 : 1, N=2 : 2, N=3 : 3, N=4 : 5, N=5 : 8이라서
// F(N) = F(N-1)+F(N-2)가 된다.
// -> 구글링해보니 길이가 i인 수를 만든다면, 길이가 i-1인 것에 1 타일을 붙이거나 길이가 i-2인 것에 00타일을 붙이는 것이라고 한다.
    // 길이가 i-2인 경우에 11타일을 붙이는 것을 고려하지 않은 이유는 이미 i-1 타일에 1을 붙이는 것에 포함되어있기 때문이다.


#include<iostream>
using namespace std;

int N;
int* results;

int main(){
    cin>>N;
    results = new int[N+1];
    results[0]=0;
    results[1] = 1;
    results[2] = 2;
    results[3] =3;
    for(int i=4;i<=N;i++){
        results[i] = (results[i-1] + results[i-2])%15746;
    }
    cout<<results[N];
}

/* 시간초과
int result=0;
int N;
void Recursive(int index){
    if(index==N){
        result++;
        return;
    }

    for(int i=0;i<2;i++){
        if(i==0 && (index+2)<=N)
            Recursive(index+2);
        else if(i==1)
            Recursive(index+1);
    }
}


int main(){
    cin>>N;
    Recursive(0);
    cout<<(result%15746);
}
*/