// https://www.acmicpc.net/problem/9184

// a,b,c가 주어졌을 때, 아래 코드를 최적화하자.
// if a <= 0 or b <= 0 or c <= 0, then w(a, b, c) returns:
//    1
// if a > 20 or b > 20 or c > 20, then w(a, b, c) returns:
//    w(20, 20, 20)
// if a < b and b < c, then w(a, b, c) returns:
//    w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c)
// otherwise it returns:
//    w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1)


// 1. a,b,c중 하나라도 0 이하일때는 1
// 2. a,b,c중 하나라도 20 초과일때는 w(20,20,20)
// 3. a<b<c일 때, w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c)
// 4. 위의 것 중 하나도 아니면 w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1) - w(a-1,b-1,c-1)

// 이것은 다이나믹 프로그래밍인지는 잘 모르겠는데, 우선 3차원 배열을 준비하고, 계산된 값을 index에 맞춰서 저장한다.
// 만약 재귀함수를 돌다가 배열에 index값을 넣었더니 제대로된 값이 존재할 경우, 재귀함수를 돌지 않고 그 값을 반환한다.

#include <iostream>
using namespace std;

int result[101][101][101];

int Recursive(int a,int b,int c){
    if(a<=0 || b<=0 || c<=0){
        result[a+50][b+50][c+50] =1;
        return 1;
    }else{
        if(result[a+50][b+50][c+50]!=-1000000){
            return result[a+50][b+50][c+50];
        }else{
            if(a>20 || b>20 || c>20){
                return result[a+50][b+50][c+50]=Recursive(20,20,20);
            }else if(a<b && b<c){
                return result[a+50][b+50][c+50]=Recursive(a,b,c-1) + Recursive(a,b-1,c-1) - Recursive(a,b-1,c);
            }else{
                return result[a+50][b+50][c+50]=Recursive(a-1,b,c) + Recursive(a-1,b-1,c) + Recursive(a-1,b,c-1) - Recursive(a-1,b-1,c-1);
            }
        }
    }

}

int a,b,c;
int main(){
    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            for(int k=0;k<101;k++){
                result[i][j][k] = -1000000;
            }
        }
    }

    while(true){
        cin>>a>>b>>c;
        if(a==-1 && b==-1 && c==-1){
            break;
        }else{
            cout<<"w("<<a<<", "<<b<<", "<<c<<") = "<<Recursive(a,b,c)<<'\n';
        }
    }
}