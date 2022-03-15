#include<iostream>
using namespace std;

int main(){
    int N;
    cin>>N;
    
    int count2 = 0;
    int count5 = 0;
    for(int i=2;i<=N;i++){
        int tmp = i;
        while(tmp%2==0){
            count2++;
            tmp/=2;
        }
        while(tmp%5==0){
            count5++;
            tmp/=5;
        }
    }
    cout<<min(count2,count5);
}