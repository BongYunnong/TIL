#include <iostream>
using namespace std;
int main(){
    int count[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    int result=0;

    for(int i=0;i<10;i++){
        cin>>count[i];
        count[i] = count[i]%42;

        int founded=-1;
        for(int j=0;j<10;j++){
            if(count[j]==count[i] && i!=j){
                founded=j;
                break;
            }
        }
        if(founded==-1){
            result++;
        }
    }
    cout<<result;
}