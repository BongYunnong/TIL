// https://www.acmicpc.net/problem/2751

// Quick Sort도 시간초과가 뜸 -> merge sort

#include <iostream>
using namespace std;

int arr[1000001];
int tmpData[1000001];

void Merge(int m, int middle, int n){
    int i=m;
    int j=middle+1;
    int k=m;

    while(i<=middle && j<=n){
        if(tmpData[i] <= tmpData[j]){
            arr[k] = tmpData[i];
            i++;
        }else{
            arr[k] = tmpData[j];
            j++;
        }
        k++;    
    }

    if(i>middle){
        for(int t=j; t<=n;t++){
            arr[k] = tmpData[t];
            k++;
        }
    }else{
        for(int t=i;t<=middle;t++){
            arr[k] = tmpData[t];
            k++;
        }
    }
    for(int t=m;t<=n;t++){
        tmpData[t] = arr[t];
    }
}

void MergeSort(int low, int high){
    if(high>low){
        int mid = (low+high)/2;
        MergeSort(low,mid);
        MergeSort(mid+1,high);
        Merge(low,mid,high);
    }
}

int main(){
    int N;
    cin>>N;

    for(int i=0;i<N;i++){
        cin>>tmpData[i];
    }
    MergeSort(0,N-1);
    for(int i=0;i<N;i++){
        cout<<tmpData[i]<<'\n';
    }
}