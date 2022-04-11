// https://www.acmicpc.net/problem/18111

// 그냥 간단하게 생각해도 시간초과가 안 난다.(0~256 이렇게 반복해도 성공이 뜨나보다)
// 틀린 이유는 result.first를 1000000으로 했었는데, 0x7f7f7f7f로 했어야되었나보다.

#include<iostream>
using namespace std;

int N,M,B;
int height[501][501];
int MIN=512,MAX=-1;

pair<int,int> result;

void SearchAnswer(int _h){
    if(_h>MAX){
        return;    
    }

    int shouldAdd=0;
    int shouldRemove=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(height[i][j]>_h){
                shouldRemove += height[i][j]-_h;
            }else if(height[i][j]<_h){
                shouldAdd +=_h - height[i][j];
            }
        }
    }

    if(shouldAdd>shouldRemove+B){
        // 못 채움
    }else{
        int currResult = shouldAdd + shouldRemove*2;
        if(result.first>=currResult){
            result.first = currResult;
            result.second = _h;
        }
    }

    SearchAnswer(_h+1);
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M>>B;
    result.first=0x7f7f7f7f;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>height[i][j];
            if(height[i][j]<MIN){
                MIN = height[i][j];
            }
            if(height[i][j]>MAX){
                MAX = height[i][j];
            }
        }
    }
    SearchAnswer(MIN);
    cout<<result.first<<" "<<result.second;
}