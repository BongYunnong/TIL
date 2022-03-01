#include<iostream>
using namespace std;
int main(){
    int a, b, c;
    cin >> a>>b>>c;

    if(a==b && b==c){
        cout << 10000 + a*1000;
    }else if((a==b && b!=c) || (a==c && b!=c)){
        cout << 1000+a*100;
    }else if(b==c && a!=c){
        cout << 1000+b*100;
    }else if( a!=b && b!=c && a!=c){
        int max=-1;
        if(a>=b)
            max = a;
        else
            max = b;
        if(c >= max)
            max = c;
        cout << max*100;
    }
}