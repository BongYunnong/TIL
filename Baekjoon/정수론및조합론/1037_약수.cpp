//https://www.acmicpc.net/problem/1037
#include<iostream>
#include<algorithm>
using namespace std;

int countInput;
int factors[51];
int main(){
    cin>>countInput;
    for(int i=0;i<countInput;i++){
        cin>>factors[i];
    }
    sort(factors,factors+countInput);
    cout<<factors[0]*factors[countInput-1];
}