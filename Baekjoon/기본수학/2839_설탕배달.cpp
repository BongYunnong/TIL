#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;
    for(int i=N/5;i>=0;i--){
        int remain = N-i*5;
        if(remain%3==0){
            cout<< i+remain/3;
            return 0;

        }
    }

    cout<<-1;
}