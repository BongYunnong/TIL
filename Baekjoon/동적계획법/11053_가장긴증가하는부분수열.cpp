#include<iostream>
using namespace std;

int N;
int arr[1001];
int results[1001];

int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>arr[i];
    }

    int Result=0;
    for(int i=1;i<=N;i++){
        results[i]=1;
        for(int j=i-1;j>=1;j--){
            if(arr[i]>arr[j]){
                results[i] = max(results[i],results[j]+1);
            }
        }
        Result = max(results[i],Result);
    }
    cout<<Result;
}

/* 이론상 진짜 맞는거같은데 왜 틀린지 모르겠음
int N;
int results[1001][1001];
int arr[1001];
int main(){
    cin>>N;

    for(int i=1;i<=N;i++){
        cin>>arr[i];
    }
    
    for(int i=1;i<=N;i++){
        results[i][i]=1;
        int currMax = arr[i];
        for(int j=i+1;j<=N;j++){
            if(currMax<arr[j]){
                results[i][j] = results[i][j-1]+1;
                currMax=arr[j]; 
            }else{
                results[i][j] = results[i][j-1]; 
            }
        }
    }

    int Result=-1;
    for(int i=1;i<=N;i++){
        if(Result<=results[i][N])
            Result=results[i][N];
    }
    cout<<Result;
}
*/