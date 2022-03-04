#include<iostream>
using namespace std;

// f(n) = 1 + f(n-1)
// n개의 탑을 a에서 c로 옮기려면
//  n-1개의 탑을 a에서 b로 올기고
//  1개의 탑을 a에서 c로 옮기고
//  n-1개의 탑을 b에서 c로 옮긴다.


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