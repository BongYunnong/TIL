// https://www.acmicpc.net/problem/1065

// 양의 정수 X의 각 자리가 등차수열을 이루면 그 수는 '한수'이다.
// N이 주어졌을 때, 1보다 크거나 같고, N보다 작거나 같은 한수의 개수를 출력

#include <iostream>
using namespace std;

bool func(int n){
    int dst;


    // 각 자리수가 등차수열이 되는지를 보기 위해서는 일단 세자리를 넘겨야한다.
    if(n<=99){
        return true;
    }else{
        dst = n%10 - ((int)(n/10))%10;
    }

    while(n>=100){
        n/=10;
        if(n%10 - ((int)(n/10))%10 != dst)
            return false;
    }
    return true;
}

int main(){
    int n;
    cin >> n;

    int count=0;
    for(int i=1;i<=n;i++){
        if(func(i))
            count++;
    }
    cout<<count;
}