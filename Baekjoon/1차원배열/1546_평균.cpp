#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;

    int max = -1000;
    float scores[1001];
    for(int i=0;i<n;i++){
        cin>> scores[i];
        if(scores[i]>=max){
            max = scores[i];
        }
    }

    float avg =0;
    for(int i=0;i<n;i++){
        avg += (scores[i]/max)*100;
    }
    cout<<avg/n;
}