// https://www.acmicpc.net/problem/2004

// 이항계수 문제
// nCm의 끝자리0의 개수 출력

// nCr =  n!/ (r! * (n-r)!) = (n-r+1)부터 n까지 곱 / r!이다.
// 1676번 문제와 같이 2*5의 개수를 세주고 빼면 된다.

#include<iostream>
using namespace std;

// 팩토리얼이기때문에, 1부터 100까지라면, 2,4,6...100이고, 세어보면 50개임
// 4를 인수로 가지는 숫자는? 4,8,...,100 25개
// 8을 인수로..? 12개
// 16 -> 6
// 32 -> 3
// 64 -> 1
// count = 50 + 25 + 12 + 6 + 3 + 1 = 97
long long GetCount2(int num){
    long long count = 0;
    for(long long i=2;i<=num;i*=2){
        count+=num/i;
    }
    return count;
}
long long func(int n, int x)
{
	int num = 0;
 
	for (long long i = x; n / i >= 1; i *= x) {
		num += n / i;
	}
 
	return num;
}

long long GetCount5(int num){
    long long count = 0;
    for(long long i=5;i<=num;i*=5){
        count+=num/i;
    }
    return count;
}

int main(){
    long long N,M;
    cin>>N>>M;

    long long count2 = GetCount2(N);
    long long count5 = GetCount5(N);
    cout<<count2<<","<<count5<<endl;
    count2-= GetCount2(M) + GetCount2(N-M);
    count5-= GetCount5(M) + GetCount5(N-M);
    cout<<min(count2,count5);
}