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