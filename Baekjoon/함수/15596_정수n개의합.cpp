// https://www.acmicpc.net/problem/15596

// 정수 n개가 주어졌을 때 n개의 합 구하기

#include <iostream>
#include <vector>
using namespace std;

long long sum(std::vector<int> &a){
    long long result=0;
    for(int i=0;i<a.size();i++){
        // a.at(i)로 해도 됨.
        result+=a[i];
    }    
    return result;
}