#include<iostream>
using namespace std;

int getCount(int _k,int _n){
    if(_k==0)
        return _n;
    if(_n<=1)
        return 1;
    return getCount(_k-1,_n) + getCount(_k,_n-1);
}
int main(){
    int T;
    cin>>T;
    int k,n;
    for(int i=0;i<T;i++){
        cin>>k>>n;
        cout<<getCount(k,n)<<endl;
    }
}