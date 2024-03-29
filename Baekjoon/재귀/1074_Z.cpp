// https://www.acmicpc.net/problem/1074

// 원하는 값(r,c)이 현재 위치(x1,y1)과 다를 때,
// 일단 원하는 값이 지정된 범위 내에 있으면 범위를 4등분하여 찾고
// 지정된 범위 밖에 있으면 함꼐 재귀호출된 영역만큼 counting한다.

#include<iostream>
#include<math.h>
using namespace std;

int count=0;
int N,r,c;
void Recursive(int x1, int y1, int N){
    if(x1==r && y1==c){
        cout<<count;
        return;
    }
    if(r<x1 + N && r>= x1 && c <y1 + N && c >=y1){
        Recursive(x1,y1, N/2);
        Recursive(x1,y1+N/2,N/2);
        Recursive(x1+N/2,y1,N/2);
        Recursive(x1+N/2,y1+N/2,N/2);
    }else{
        // 이렇게 답을 보면 대충 아, 범위를 벗어난것은 셀 필요가 없겠구나 싶긴한데,
        // 이걸 생각해내기 어려워서 실버 1이지않을까
        count+=pow(N,2);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>r>>c;
    Recursive(0,0,pow(2,N));
}

/* 답은 잘 나오는데, 시간초과 걸림
#include<iostream>
using namespace std;

int count=0;
int N,r,c;
void Recursive(int x1, int y1, int N){
    if(N==1){
        //cout<<x1<<','<<y1<<endl;
        count++;
        if(x1==c && y1==r){
            cout<<count-1;
            return;
        }
    }else{
        Recursive(x1,y1, N/2);
        Recursive(x1+N/2,y1,N/2);
        Recursive(x1,y1+N/2,N/2);
        Recursive(x1+N/2,y1+N/2,N/2);
    }
}

int main(){
    cin>>N>>r>>c;
    int Mul2=1;
    for(int i=0;i<N;i++){
        Mul2*=2;
    }
    Recursive(0,0,Mul2);
}
*/
