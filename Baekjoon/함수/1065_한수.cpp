#include <iostream>
using namespace std;

bool func(int n){
    int dst;

    if(n<=99){
        return true;
    }else{
        dst = n%10 - ((int)(n/10))%10;
    }

    while(n>=100){
        n/=10;
        if(n%10 - ((int)(n/10))%10 != dst)
            return false;
    }
    return true;
}

int main(){
    int n;
    cin >> n;

    int count=0;
    for(int i=1;i<=n;i++){
        if(func(i))
            count++;
    }
    cout<<count;
}