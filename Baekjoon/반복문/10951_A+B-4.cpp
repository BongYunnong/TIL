// https://www.acmicpc.net/problem/10951
// 두 정수 A와 B를 입력받은 다음 A+B 출력
#include <iostream>
using namespace std;
int main(){
    int a,b;

    while(true){
        cin>>a>>b;

        // EOF에 대해 기억해두자.
        if(cin.eof()==true)
            break;
        cout<<a+b<<'\n';
    }
}