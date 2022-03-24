// https://www.acmicpc.net/problem/10871
// 정수 N 개로 이루어진 수열 A와 X가 주어졌을 때 A에서 X보다 작은 수를 모두 출력하는 프로그램

#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    int n;
    cin >> n;
    int x;
    cin >> x;

    int element;
    for(int i=0;i<n;i++){
        cin >> element;
        if(element < x){
            cout<<element<<" ";
        }
    }
}