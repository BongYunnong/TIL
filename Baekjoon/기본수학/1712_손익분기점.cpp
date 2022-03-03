#include<iostream>
using namespace std;
int main(){
    long long a,b,c;

    cin>>a>>b>>c;
    long long  count =0;

    if(c>b){
        cout<< a/(c-b)+1;
    }else{
        cout<<-1;
    }
}