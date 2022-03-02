#include<iostream>
#include<cstring>
using namespace std;

int main(){
    string s;
    cin>>s;

    int count[32];
    for(int i=0;i<32;i++){
        count[i] = 0;
    }

    for(int i=0;i<s.length();i++){
        if(s[i]>=97 && s[i] <= 122){
            count[s[i]-97]++;
        }else if(s[i]>=65 && s[i]<=90){
            count[s[i]-65]++;
        }
    }

    int max=-10;
    int index=-1;
    for(int i=0;i<32;i++){
        if(max < count[i]){
            max = count[i];
            index=i;
        }else if(max==count[i]){
            index=-1;
        }
    }

    if(index>=0)
        cout<<(char)(index+65);
    else 
        cout<<'?';
}