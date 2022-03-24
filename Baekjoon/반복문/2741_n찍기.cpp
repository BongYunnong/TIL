// https://www.acmicpc.net/problem/2741
// N이 주어졌을 때, 1부터 N까지 한 줄에 하나씩 출력

#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    long n;
    cin >> n;
    for(int i=0;i<n;i++){
        cout << i+1<<'\n';
    }
}