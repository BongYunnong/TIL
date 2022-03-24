// https://www.acmicpc.net/problem/10950
// 두 정수 A와 B를 입력받아서 A+B 출력
#include <iostream>
using namespace std;
int main(){
    int t;
    cin>>t;

    int a, b;
    for(int i=0 ; i< t; i++){
        cin >> a>> b;
        cout << a+b <<endl;
    }
}