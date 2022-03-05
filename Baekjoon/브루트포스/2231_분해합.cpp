#include<iostream>
using namespace std;
int main(){
    long N;
    cin>>N;

    long results[1000001];
    for(int i=0;i<1000001;i++){
        results[i]=-1;
    }
    for(int i=1;i<=N;i++){
        int add=i;
        int curr=i;
        while(true){
            if(curr<10){
                add+=curr;
                break;
            }
            else{
                add += curr%10;
                curr/=10;
            }
        }
        
        if(add <= 1000000){
            if(results[add]==-1){
                results[add]=i;
            }
        }
    }

    
    if(results[N]==-1){
        cout<<0;
    }else{
        cout<<results[N];
    }
}