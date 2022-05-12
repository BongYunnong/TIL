// https://www.acmicpc.net/problem/2908
// 두 수 A,B가 주어졌을 때, 각 숫자를 거꾸로 읽어서 큰 숫자를 출력

#include<iostream>
#include<string>
using namespace std;

string swap13(string _s){
    char tmp = _s[2];
    _s[2] =_s[0];
    _s[0]=tmp;
    return _s;
}
int main(){
    /* 무식한 방법 -> 3자리수이기에 가능함
    string a;
    string b;
    cin>>a>>b;

    if(a[2]>b[2]){
        cout<<a[2]<<a[1]<<a[0];
    }else if(a[2]==b[2] && a[1]>b[1]){
        cout<<a[2]<<a[1]<<a[0];
    }else if(a[2]==b[2] && a[1]==b[1] && a[0]>b[0]){
        cout<<a[2]<<a[1]<<a[0];
    }else{        
        cout<<b[2]<<b[1]<<b[0];
    }
    */

   string a;
   string b;
   cin>>a>>b;

    // 이것도 사실 3자릿수라서 가능했을듯?
   if(stoi(swap13(a))>stoi(swap13(b))){
       cout<<swap13(a);
   }else{
       cout<<swap13(b);
   }
}