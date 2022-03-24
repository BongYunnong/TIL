// https://www.acmicpc.net/problem/11022
// 두 정수 A와 B를 입력받은 후 A+B출력
#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    int t;
    cin >> t;

    int a,b;
    for(int i=0;i<t;i++){
        cin >> a >> b;
        cout<<"Case #"<<i+1<<": "<<a<<" + "<<b<<" = "<<a+b<<"\n";
    }
}