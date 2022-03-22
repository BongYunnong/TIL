// https://www.acmicpc.net/problem/2292
// 중앙의 방 1부터 시작해서 이웃하는 방에 돌아가면서 주소 매기기
// N번째의 방까지 최소 개수의 방을 지나서 간다 했을 때, 몇 개의 방을 지나는가?(시작과 끝 포함)
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
    범위는 6의 배수만큼 증가하는구나

    -2
    -1      0
    0~5     0   
    6~17    1~2   
    18~35   3~5
    36~59   6~9
    60~89   10~14
*/

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
            // 범위가 6의 배수만큼 증가하므로, n이 어디 사이에 있는지 확인
            if(count<=n && n<(count+6*result)){
                break;
            }
            else{
                count+=6*result;
                result++;
            }
        }
        // n의 위치한 범위를 찾았으면 거기에 + 1을 한다.
        cout<<result+1;
    }
}
