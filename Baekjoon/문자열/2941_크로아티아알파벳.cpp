#include <iostream>
#include <string>
using namespace std;
int main(){
    string s;
    cin>>s;

    int result=0;
    for(int i=0;i<s.length();i++){
        if(s.length() > i+1){
            if(s[i]=='c'){
                if(s[i+1]=='=' || s[i+1]=='-'){
                    i++;
                }
            }else if(s[i]=='d'){
                if(s[i+1]=='-'){
                    i++;
                }else if(s.length() > i+2){
                    if(s[i+1]=='z' && s[i+2]=='=')
                        i+=2;
                }
            }else if((s[i]=='l' || s[i]=='n')&&(s[i+1]=='j')){
                i++;
            }else if((s[i]=='s' || s[i]=='z')&&(s[i+1]=='='))
                i++;
        }
        result++;
    }
    cout<<result;
}