#include<iostream>
#include<string>
using namespace std;
int main(){
    string A,B;
    cin>>A>>B;
    
    int x=0;
    int y=0;

    int count = A.length();
    if(B.length()>count){
        count = B.length();
    }
    string C;
    int result=0;
    for(int i=0;i<count;i++){
        if(A.length()<i+1){
            result = B[B.length()-1-i]-48+x;
        }
        else if(B.length()<i+1){
            result = A[A.length()-1-i]-48+x;
        }  
        else{
            int tmpA = A[A.length()-1-i]-48;
            int tmpB =B[B.length()-1-i]-48;         
            result = tmpA + tmpB+x;
        }
        x = result/10;
        y = result%10;
        C.insert(0,std::to_string(y));
    }
    if(x>0)
        C.insert(0,std::to_string(x));
    cout<<C;
}