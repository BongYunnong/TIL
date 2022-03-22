// https://www.acmicpc.net/problem/10757
// A와 B를 입력받아서 A+B를 출력하자.
// 근데 A,B는 10^(10000)보다 작은 수이다.


#include<iostream>
#include<string>
using namespace std;
int main(){
    // longlong으로도 불가능하니 string으로 읽어오기
    string A,B;
    cin>>A>>B;
    
    int x=0;
    int y=0;

    // A와 B중 긴 길이를 계산
    int count = A.length();
    if(B.length()>count){
        count = B.length();
    }

    string C;   // 결과
    int result=0;
    // 최대 자릿수가 될 때까지 각 자릿수+올림수를 더해서 C의 앞에 삽입하기
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
        x = result/10;  // x는 올림수
        y = result%10;  // y는 해당 자릿수
        C.insert(0,std::to_string(y));
    }
    if(x>0)
        C.insert(0,std::to_string(x));
    cout<<C;
}