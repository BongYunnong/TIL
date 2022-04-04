// https://www.acmicpc.net/problem/1992

// Quad Tree : 0과 1로만 이루어진 2차원 배열에서 같은 숫자의 점들이 한 곳에 많이 몰려있으면 압축

// 주어진 영상이 모두 0혹은 1로 되어있으면 결과는 각각 0,1이된다.
// 영상이 0과 1이 섞여 있으면 왼쪽 위, 오른쪽 위, 왼쪽 아래, 오른쪽 아래 4개의 영상으로 나누어 압축하게된다.

//8
//11110000
//11110000
//00011100
//00011100
//11110000
//11110000
//11110011
//11110011
//ex. ((110(0101))(0010)1(0001))


#include<iostream>
#include<string>
using namespace std;

int arr[65][65];

void QuadTree(int _x, int _y, int _size){
    int white=arr[_x][_y];
    bool match=true;
    // 현재 size중에 start point의 값과 다른 값이 있는지 체크
    for(int i=_x;i<_x+_size;i++){
        for(int j=_y;j<_y+_size;j++){
            if(white!=arr[i][j]){
                match =false;
                break;
            }
        }
        if(match==false)
            break;
    }

    if(match){
        // 모두 같은 값이라면 결과 출력
        if(white==0){
            cout<<0;
        }else{
            cout<<1;
        }
    }else{
        // 한 번에 압축되지 않는다면 괄호 안에 재귀로 네 구간으로 나누어 다시 체크
        cout<<'(';
        QuadTree(_x,_y,_size/2);
        QuadTree(_x,_y+_size/2,_size/2);
        QuadTree(_x+_size/2,_y,_size/2);
        QuadTree(_x+_size/2,_y+_size/2,_size/2);
        cout<<')';
    }
}

int main(){
    int N;
    cin>>N;
    string s;
    for(int i=0;i<N;i++){
        cin>>s;
        for(int j=0;j<s.length();j++){
            arr[i][j]=s[j]-'0';
        }
    }

    QuadTree(0,0,N);
}