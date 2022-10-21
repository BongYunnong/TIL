// https://www.acmicpc.net/problem/1654

// 길이가 제각각인 K개의 랜선을 가지고있는데, 모두 N개의 같은 길이의 랜선으로 만들고싶다.
// 만들 수 있는 최대 랜선의 길이는?

// 정말로 "이분탐색"이라는 단어에 걸맞는 방법이다. 최소와 최대를 더한 후 2로 나눈 mid에서 조건들을 확인하고,
// 그 결과에 따라 최소~mid, mid+1~최대 둘 중 하나의 range를 선택해 반복한다.

#include<iostream>
#include<algorithm>
using namespace std;

int K;
int N;
long long* arr;

int SearchLength(long long element){
    int count =0;
    for(int i=0;i<K;i++){
        count += arr[i]/element;
    }
    return count;
}

int main(){
    cin>>K;
    cin>>N;

    arr = new long long[K];
    for(int i=0;i<K;i++){
        cin>>arr[i];    
    }
    sort(arr,arr+K);

    long long answer=0;
    long long low =1;
    long long high = arr[K-1];

    while(low<=high){
        long long mid = (low+high)/2;
        int result = SearchLength(mid);
        if(result<N){
            high=mid-1;
        }else{
            if(answer<mid){
                answer=mid;
            }
            low = mid+1;
        }
    }
    cout<<answer;
}