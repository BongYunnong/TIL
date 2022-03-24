// https://www.acmicpc.net/problem/10952
// 두 정수 A와 B를 입력받은 후 A+B 출력
#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    int a=-1,b=-1;

    while((a==0 && b==0)==false){
        cin>>a>>b;
        if((a==0 && b==0))
            break;
        cout<<a+b<<'\n';
    }
}