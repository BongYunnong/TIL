#include<iostream>
#include <cstring>
using namespace std;
int main(){
    string S;
    int t,r;
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>r;
        cin>>S;
        for(int j=0;j<S.length();j++){
            for(int k=0;k<r;k++){
                cout<<S[j];
            }
        }
        cout<<'\n';
    }
}