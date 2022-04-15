// https://www.acmicpc.net/problem/2447

// 간단한 재귀이다. 처음에 3의 거듭제곱이 주어지면, recursive를 통해 3씩 나누고, 총 9등분을 하자는 생각을 해야한다.
// 거기에서 중요한 것은 정 중앙은 그리지 않는 것이다.
// 간과할만한 것은, 별을 찍어내야하는데 한 줄씩 print하는 것이 아니라 정사각형 형태로 재귀가 들어가기때문에
// 그냥 recursive내에서 print를 하지 말고 배열을 만들어서 모든 점을 배열에 저장하고, 마지막에 한번에 별을 찍어내는 것이 좋다.

#include<iostream>
using namespace std;

char result[3000][3000];

void PrintStart(int N,int x, int y){
    if(N==1){
        result[x][y]='*';
        return;
    }
    int div = N/3;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==1 && j==1)
                continue;
            PrintStart(div,x+(div*i),y+(div*j));
        }
    }
}
int main(){
    int N;
    cin>>N;

    for(int i=0;i<3000;i++){
        for(int j=0;j<3000;j++){
            result[i][j]=' ';
        }
    }

    PrintStart(N,0,0);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<result[i][j];
        }
        cout<<'\n';
    }
}
