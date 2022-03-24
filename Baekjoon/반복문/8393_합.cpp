// https://www.acmicpc.net/problem/8393
// n이 주어졌을 때 1부터 n까지의 합 구하기

#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;

    int result=0;
    for(int i=0;i<n;i++){
        result += i+1;
    }
    cout << result;

}