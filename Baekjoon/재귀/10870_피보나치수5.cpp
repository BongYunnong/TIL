#include<iostream>
using namespace std;
int F(int _n){
    if(_n<=1)
        return _n;
    else{
        return F(_n-1)+F(_n-2);
    }
}
int main(){
    int n;
    cin>>n;
    cout<<F(n);
}
