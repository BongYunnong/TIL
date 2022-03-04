#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;

    int result=1;
    for(int i=1;i<=N;i++){
        result*=i;
    }
    cout<<result;
}