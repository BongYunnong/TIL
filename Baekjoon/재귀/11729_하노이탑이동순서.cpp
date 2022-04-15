// https://www.acmicpc.net/problem/11729

// 또또또또 까먹을뻔했다.
// 하지만 그 개념을 이해하면 쉽다.
// 아래에 쓴 것처럼, F(N) = 2F(n-1) +1이다.
// 왜냐하면 3개의 지점이 있고, 한 지점에서 다른 지점으로 물건을 옮기려면,
// 1개라면 그냥 옮길 수 있지만 2개부터는 먼저 맨 아래것을 목표 지점으로 이동시키기 위해서 그 위의 모든 짐을 목표 지점 이외의 곳으로 옮겨야하기떄문이다.
// 어떻게보면 지점이 3개인것은 축복일 수 있다.
// 어쨋든, 과정은 이렇다.

// f(n) = 1 + 2 * f(n-1)
// n개의 탑을 a에서 c로 옮기려면
//  n-1개의 탑을 a에서 b로 올기고
//  1개의 탑을 a에서 c로 옮기고
//  n-1개의 탑을 b에서 c로 옮긴다.

// 이제 몇 번 옮겨야하는지는 쉽게 알 수 있지만, 원하는 것은 추가로 옮기는 순서를 알아내야한다.
// 이것도 개념을 제대로 알면 간단한데, 시작지점, 경유지점, 목표지점이 있으면
// count가 1일때는 그냥 시작 -> 목표로 가지만, 그렇지 않으면
// 시작->경유 (count-1)
// 시작->목표 (1 <맨 끝 팥>)
// 경유->목표 (count-1)이다.
// 이것을 재귀함수로 변형하면 된다.


#include<iostream>
using namespace std;


void hanoi(int n,int a,int b, int c){
	if(n==1){
		cout<<a<<' '<<c<<'\n';
	}else{
		hanoi(n-1,a,c,b);
		cout<<a<<' '<<c<<'\n';
		hanoi(n-1,b,a,c);
	}
}
int main(){
    int n;
    cin>>n;
	int result=1;
	for(int i=0;i<n;i++){
		result*=2;
	}
	result-=1;
	cout<<result<<'\n';
    hanoi(n,1,2,3);
    
}