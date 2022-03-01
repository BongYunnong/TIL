#include <iostream>
using namespace std;
int main(){
    int a,b;

    while(true){
        cin>>a>>b;

        // EOF에 대해 기억해두자.
        if(cin.eof()==true)
            break;
        cout<<a+b<<'\n';
    }
}