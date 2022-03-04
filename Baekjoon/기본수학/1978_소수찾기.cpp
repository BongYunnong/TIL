#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;


    int counting[1001]={};
    for(int i=1;i<=1000;i++){
        int mul =1;
        while (mul*i <= 1000)
        {
            counting[mul*i]++;
            mul++;
        }
    }

    int input=0;
    int result=0;
    for(int i=0;i<N;i++){
        cin>>input;
        if(counting[input] == 2){
            result++;
        }
    }
    cout<<result;
}