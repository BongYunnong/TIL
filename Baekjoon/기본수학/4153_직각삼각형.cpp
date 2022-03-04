#include<iostream>
using namespace std;
int main(){
    int a,b,c;
    while(true){
        cin>>a>>b>>c;
        if(a==b&&b==c&&c==0){
            break;
        }

        if(a*a+b*b==c*c || b*b+c*c==a*a || a*a+c*c==b*b)
            cout<<"right"<<'\n';
        else
            cout<<"wrong"<<'\n';
    }
}