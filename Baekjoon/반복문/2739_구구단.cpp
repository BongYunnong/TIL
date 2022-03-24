// https://www.acmicpc.net/problem/2739
// N을 입력받아서 구구단 N을 출력

#include <iostream>
using namespace std;
int main(){
    int n;
    cin >>n;

    for(int i=1;i<=9;i++){
        cout << n << " * "<< i << " = "<< n*i <<endl;
    }
}