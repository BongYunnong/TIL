// https://www.acmicpc.net/problem/1978
// 1929번 처럼 최댓값까지 모든 값을 다 곱해서 나온 수를 counting한다.
// 그리고 input을 입력받으면서 해당 index의 counting이 2일 경우 소수이므로 result를 증가시킨다.
#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;


    int counting[1001]={};
    for(int i=1;i<=1000;i++){
        int mul =1;
        while (mul*i <= 1000)
        {
            counting[mul*i]++;
            mul++;
        }
    }

    int input=0;
    int result=0;
    for(int i=0;i<N;i++){
        cin>>input;
        if(counting[input] == 2){
            result++;
        }
    }
    cout<<result;
}