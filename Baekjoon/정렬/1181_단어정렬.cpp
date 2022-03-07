#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

bool Compare(string a, string b){
    if(a.length()==b.length()){
        for(int i=0;i<a.length();i++){
            if(a[i]!=b[i]){
                return a[i]<b[i];
            }
        }
    }
    return a.length()<b.length();
}

int main(){
    int N;
    cin>>N;
    string* arr=new string[N];
    
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    sort(arr,arr+N,Compare);

    for(int i=0;i<N;i++){
        if(i>0){
            if(arr[i-1]!=arr[i]){
                cout<<arr[i]<<'\n';
            }
        }else
            cout<<arr[0]<<'\n';
    }
}