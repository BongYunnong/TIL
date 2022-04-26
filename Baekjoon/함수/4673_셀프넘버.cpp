// https://www.acmicpc.net/problem/4673


#include <iostream>
using namespace std;

int func(int n){
    int result=n;
    while(n>=10){
        result += n%10;
        n/=10;
        if(n<10)
            break;
    }
    result+=n;
    return result;
}

int main(){
    int count[10001];
    for(int i=0;i<sizeof(count)/sizeof(int);i++){
        count[i]=0;
    }
    for(int i=1;i<10000;i++){
        int tmp = func(i);
        if(tmp<=10000 && i!=tmp)
            count[tmp] ++;
    }

    for(int i=1;i<10000;i++){
        if(count[i]==0)
            cout<<i<<'\n';
    }
}