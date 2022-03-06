#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;

    int arr[1001];
    for(int i=0;i<1001;i++){
        arr[i] = -1;
    }

    int count=0;
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }

    int min = 2000;
    int index=-1;
    for(int i=0;i<N;i++){
        min = arr[i];
        index = -1;
        for(int j=i+1;j<N;j++){
            if(arr[j] < min){
                min = arr[j];
                index = j;
            }
        }
        if(index>=0){
            int tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
        }
    }

    for(int i=0;i<N;i++){
        cout<<arr[i]<<endl;
    }
}