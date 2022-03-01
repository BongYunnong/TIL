#include <iostream>
using namespace std;
int main(){
    int a,b,c;

    int count[10]={0,};

    cin>>a>>b>>c;

    long tmp = a*b*c;

    while(tmp>0){
        count[tmp%10]++;
        tmp/=10;

        if(tmp<10){
            count[tmp]++;
            break;
        }
    }

    for(int i=0; i< sizeof(count)/sizeof(int);i++){
        cout<<count[i]<<'\n';
    }
}