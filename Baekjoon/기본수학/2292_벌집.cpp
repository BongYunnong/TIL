#include <iostream>

using namespace std;
int main(){

    long n;
    cin>>n;

    int count=2;
    int result=1;

    if(n==1){
        cout<<1;
    }else{
        while(true){
            if(count<=n && n<(count+6*result)){
                break;
            }
            else{
                count+=6*result;
                result++;
            }
        }
        cout<<result+1;
    }
}

/*
    1 = 1           
    2~7 = 2         
    8~19=3
    20~37 = 4
    38~61 = 5
    62~91

    1
    6
    12
    18
    24

    -2
    -1      0
    0~5     0   
    6~17    1~2   
    18~35   3~5
    36~59   6~9
    60~89   10~14
    */