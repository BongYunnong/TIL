// https://www.acmicpc.net/problem/2231

// N의 분해합은 N과 N을 이루는 자리수의 합.
// M의 분해합이 N일 경우, M은 N의 생성자이다.

// 어떤 자연수 N이 주어졌을 때, N의 가장 작은 생성자는?
// 가장 작은 생성자니까, i가 1부터 시작해서 N까지 생성자인지를 체크
// i + i의 각 자리수의 합 == N이라면, break;

#include<iostream>
using namespace std;
int main(){
    long N;
    cin>>N;

    for(int i=1;i<=N;i++){
        int add=i;
        int curr=i;
        while(true){
            if(curr<10){
                add+=curr;
                break;
            }
            else{
                add += curr%10;
                curr/=10;
            }
        }
        if(add==N){
        	cout<<i;
        	return 0;
        }
    }
    cout<<0;
}

/* 이것은 테스트케이스가 여러개일 때 유용하게 쓸 듯. 하지만 그냥 1개라면, 위의 것이 더 빠르다.
#include<iostream>
using namespace std;
int main(){
    long N;
    cin>>N;

    long results[1000001];
    for(int i=0;i<1000001;i++){
        results[i]=-1;
    }
    for(int i=1;i<=N;i++){
        int add=i;
        int curr=i;
        while(true){
            if(curr<10){
                add+=curr;
                break;
            }
            else{
                add += curr%10;
                curr/=10;
            }
        }
        
        if(add <= 1000000){
            if(results[add]==-1){
                results[add]=i;
            }
        }
    }

    
    if(results[N]==-1){
        cout<<0;
    }else{
        cout<<results[N];
    }
}
*/