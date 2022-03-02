#include<iostream>
using namespace std;
int main(){
    char input[101];
    for(int i=0;i<101;i++){
        input[i] = ' ';
    }
    cin>>input;
    for(int i=(int)'a'; i<=(int)'z';i++){
        int founded=-1;
        for(int j=0;j<101;j++){
            if((int)input[j]==i){
                founded=j;
                break;
            }
        }
        cout<<founded<<' ';
    }
}