#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int N,C;
    cin>>N>>C;
    long* arr = new long[N];
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }

    sort(arr,arr+N);

    // 이거를 arr[0]으로 했더니 틀렸음 -> 아마 arr[0]이 1이 아니라면 mid의 범위가 넘어갈 수 있으니까 그런 것이 아닐까 생각함
    long left = 1;
    long right = arr[N-1];
    int answer=-1;
    while(left<=right){
        long mid = (left+right)/2;
        int lastLaunchedIndex= 0;
        int launchCount=1;
        for(int i=1;i<N;i++){
            if(arr[i]-arr[lastLaunchedIndex] >= mid){
                lastLaunchedIndex=i;
                launchCount++;
            }
        }

        if(launchCount>=C){
            left = mid+1;
            
            if(answer<=mid)
                answer=mid;
        }else{
            right = mid-1;
        }
    }
    cout<<answer;
}

/* 시간초과
int main(){
    int N;
    int C;
    cin>>N>>C;

    int* arr = new int[N];
    int* maxDist = new int[N];
    int* minDist = new int[N];
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }

    sort(arr,arr+N);
    maxDist[N-1]=arr[N-1]-arr[0];
    minDist[0]=0;
    minDist[N-1]=0;
    for(int i=1;i<N-1;i++){
        minDist[i] = min(abs(arr[0]-arr[i]),abs(arr[N-1]-arr[i]));
    }
    int count=2;
    while(count<C){
        int maxmaxDist=0;
        int index=0;
        for(int i=0;i<N;i++){
            if(maxmaxDist <= minDist[i]){
                maxmaxDist = minDist[i];
                index = i;
            }
        }

        minDist[index]=0;
        count++;
        //cout<<count<<" Launched : "<<arr[index]<<'\n';

        for(int i=0;i<N;i++){
            minDist[i] = min(minDist[i],abs(arr[index]-arr[i]));
        }
    }
    int answer = arr[N-1]-arr[0];
    for(int i=0;i<N;i++){
        if(minDist[i]==0){
            for(int j=i+1;j<N;j++){
                if(minDist[j]==0){
                    answer = min(answer, abs(arr[i]- arr[j]));
                    break;
                }
            }
        }
    }

    cout<<answer;

}
*/