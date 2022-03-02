#include <iostream>
using namespace std;
int main(){
    int n;
    char a[101];

    cin>>n;
    for(int i=0;i<n;i++){
        a[i] = 0;
    }

    int result=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        result += a[i]-48;
    }
    cout<<result;
    
}