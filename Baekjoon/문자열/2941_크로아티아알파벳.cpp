// https://www.acmicpc.net/problem/2941
//č 	c=
//ć	    c-
//dž	dz=
//đ	    d-
//lj	lj
//nj	nj
//š	    s=
//ž	    z=
// 단어가 주어졌을 때 위와같은 크로아티아 알파벳 몇개로 이루어져있는지 출력

#include <iostream>
#include <string>
using namespace std;
int main(){
    string s;
    cin>>s;

    int result=0;
    for(int i=0;i<s.length();i++){
        // 다 2개 이상의 알파벳 합으로 이루어져있기에 체크
        // 조건에 맞으면 index인 i를 증가시키는 방법으로 반복
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