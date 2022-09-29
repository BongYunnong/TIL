// https://www.acmicpc.net/problem/2110

// N개의 집에 C개의 공유기를, 최소 거리가 최대가 되도록 하는 방법

// 특정 간격을 기준으로 가능한 위치에 공유기를 설치
// 설치한 후에 공유기를 더 설치해야하면 간격을 줄이고, 공유기 수를 줄여야하면 간격을 늘린다.

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
    // left, right가 시작점이 아닌 공유기를 놓는 최소, 최대 거리임
    long minDist = 1;  // 가능한 최소 거리
    long maxDist = arr[N-1]-arr[0];  // 가능한 최대 거리
    int answer=-1;
    while(minDist<=maxDist){
        long mid = (minDist+maxDist)/2;
        int lastLaunchedIndex= 0;
        int launchCount=1;
        for(int i=1;i<N;i++){
            // 간격을 기준으로 공유기를 설치해봄 -> launchCount는 공유기를 설치할 수 있는 누적 개수
            if(arr[i]-arr[lastLaunchedIndex] >= mid){
                lastLaunchedIndex=i;
                launchCount++;
            }
        }

        if(launchCount>=C){
            // 간격을 넓히자.
            minDist = mid+1;
            
            if(answer<=mid)
                answer=mid;
        }else{
            // 간격을 줄이자
            maxDist = mid-1;
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