#include<iostream>
using namespace std;
int N;
int radiuses[101];

int gcd(int a, int b){
    int n;
    while (b!=0)
    {
        int n = a%b;
        a=b;
        b=n;
    }
    return a;
}

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>radiuses[i];
    }

    for(int i=1;i<N;i++){
        int currGCD = gcd(radiuses[0],radiuses[i]);
        cout<<radiuses[0]/currGCD<<"/"<<radiuses[i]/currGCD<<'\n';
    }
}