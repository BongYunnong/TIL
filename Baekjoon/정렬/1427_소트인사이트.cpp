// https://www.acmicpc.net/problem/1427

// 내림차순 정렬인데, 그냥 sort를 한 이유는
// 마지막에 출력할 때 반대로 출력하기 위함이다.

#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> arr;
    long long N;

    cin>>N;
    while(true){
        if(N<10){
            arr.push_back(N);
            break;
        }else{
            arr.push_back(N%10);
            N/=10;
        }
    }
    sort(arr.begin(),arr.end());
    for(int i=arr.size()-1;i>=0;i--){
        cout<<arr[i];
    }
}