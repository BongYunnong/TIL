//https://www.acmicpc.net/problem/2609
#include<iostream>
using namespace std;


// 유클리드 호제법
int gcd(int a, int b){
    int n;
    while(b!=0){
        n = a%b;
        a=b;
        b=n;
    }
    return a;
}
int main(){
    int a,b;
    cin>>a>>b;
    cout<<gcd(a,b)<<"\n"<<a*b/gcd(a,b)<<"\n";
}

/* 틀린 풀이
int a,b;

int aFactors[10001];
int bFactors[10001];
int main(){
    cin>>a>>b;

    int aIndex=0;
    int tmpA=a;
    for(int i=2;i<a;i++){
        while (tmpA%i==0)
        {
            tmpA/=i;
            aFactors[aIndex] = i;
            //cout<<aFactors[aIndex]<<' ';
            aIndex++;
        }
    }
    //cout<<'\n';
    int bIndex=0;
    int tmpB=b;
    for(int i=2;i<b;i++){
        while(tmpB%i==0){
            tmpB/=i;
            bFactors[bIndex] = i;
            //cout<<bFactors[bIndex]<<' ';
            bIndex++;
        }
    }
    //cout<<'\n';

    int Result1=1;
    int Result2=a*b;
    
    int indexing=0;
    for(int i=0;i<aIndex;i++){
        for(int j=indexing;j<bIndex;j++){
            if(aFactors[i]==bFactors[j]){
                Result1*=aFactors[i];
                indexing++;
                break;
            }
        }
    }

    cout<<Result1<<endl;
    cout<<Result2/Result1;
}
*/
