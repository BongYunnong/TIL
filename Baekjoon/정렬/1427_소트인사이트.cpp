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