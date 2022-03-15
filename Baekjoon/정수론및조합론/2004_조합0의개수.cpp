#include<iostream>
using namespace std;

long long GetCount2(int num){
    long long count = 0;
    for(long long i=2;i<=num;i*=2){
        count+=num/i;
    }
    return count;
}

long long GetCount5(int num){
    long long count = 0;
    for(long long i=5;i<=num;i*=5){
        count+=num/i;
    }
    return count;
}

int main(){
    long long N,M;
    cin>>N>>M;
    
    long long count2 = GetCount2(N);
    long long count5 = GetCount5(N);
    count2-= GetCount2(M) + GetCount2(N-M);
    count5-= GetCount5(M) + GetCount5(N-M);
    cout<<min(count2,count5);
}