#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    long long N;
    long long M;
    cin>>N>>M;
    long long* arr = new long long[N];

    for(long long i=0;i<N;i++){
        cin>>arr[i];
    }
    sort(arr,arr+N);

    long long low = 0;
    long long high = arr[N-1];
    long long answer=0;
    while(low<=high){
        long long count=0;
        long long mid = (low+high)/2;
        //cout<<"New\n";
        for(long long i=0;i<N;i++){
            if(arr[i]>mid){
                //cout<<",,"<<arr[i]<<","<<mid<<'\n';
                count += arr[i]-mid;
            }
        }

        if (count>=M){
            // 원하는 길이 M보다 가져갈 길이 count가 더 크거나 같다면,
            // 절단기의 높이를 높여본다.
            low = mid+1;
            
            if(answer<mid){
                // 지금까지 잘라왔던 길이보다 더 긴 길이를 가져가게 된다면 업데이트.
                answer = mid;
            }
        }else{
            // 원하는 길이 M보다 가져갈 길이 count가 더 적다면,
            // 절단기의 높이를 줄여본다. 
            high = mid-1;
        }
    }
    cout<<answer;
}