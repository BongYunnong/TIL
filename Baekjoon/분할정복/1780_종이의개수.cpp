// https://www.acmicpc.net/problem/1780

// N X N 크기의 종이에 -1,0,1 중 하나가 저장되어있다.
// 1. 만약 종이가 모두 같은 수로 되어있으면 이 종이를 그대로 사용
// 2. (1)이 아닌 경우에는 종이를 같은 크기의 종이 9개로 자르고, 각각의 잘린 종이에 대해서 (1)의 과정을 반복한다.

#include<iostream>
using namespace std;

// 3^7 = 2187
int arr[2200][2200];

int result0;
int result1;
int result2;


void Origami(int _x,int _y,int _size){
    int originType = arr[_x][_y];
    bool match=true;
    // 탐색하려는 size 만큼의 2차원 배열에 start좌표에 저장된 값과 다른 값이 있는지 체크
    for(int i=_x;i<_x+_size;i++){
        for(int j=_y;j<_y+_size;j++){
            if(originType!=arr[i][j]){
                match=false;
                break;
            }
        }
        if(match==false){
            break;
        }
    }

    if(match){
        // size 내 모든 값이 동일하다면 그에 맞게 result ++
        if(originType==-1){
            result0++;
        }else if(originType==0){
            result1++;
        }else{
            result2++;
        }
    }else{
        // 하나라도 값이 다른 것이 있다면
        // 같은 크기의 종이 9개로 자른다.
        Origami(_x,_y,_size/3);
        Origami(_x+_size/3,_y,_size/3);
        Origami(_x+(2*_size)/3,_y,_size/3);
        Origami(_x,_y+_size/3,_size/3);
        Origami(_x+_size/3,_y+_size/3,_size/3);
        Origami(_x+(2*_size)/3,_y+_size/3,_size/3);
        Origami(_x,_y+(2*_size)/3,_size/3);
        Origami(_x+_size/3,_y+(2*_size)/3,_size/3);
        Origami(_x+(2*_size)/3,_y+(2*_size)/3,_size/3);
    }
}

int main(){
    int N;
    cin>>N;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>arr[i][j];
        }
    }

    Origami(0,0,N);

    cout<<result0<<'\n'<<result1<<'\n'<<result2;
}