#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;

    int a =-1;
    int b=n;


    int count=0;
    while(n!=a){
        a= b;
        b = (int)(b/10) + b%10;
        a = (a%10)*10 + b%10;
        b= a;
        count++;
    }
    cout<<count;
}