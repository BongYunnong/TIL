// https://www.acmicpc.net/problem/2742
// N부터 1까지 한 줄에 하나씩 출력

#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    long n;
    cin >> n;
    for(int i=n;i>0;i--){
        cout << i<<"\n";
    }
}