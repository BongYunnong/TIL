#include<iostream>
using namespace std;

int arr[129][129];

int whiteCount=0;
int blueCount=0;

void Origami(int _x,int _y, int size){
    int white= arr[_x][_y];
    int result = 0;
    for(int i=_x;i<_x+size;i++){
        for(int j=_y;j<_y+size;j++){
            if(white != arr[i][j]){
                result=-1;
                break;
            }
        }
        if(result==-1){
            break;
        }
    }

    if(result==-1){
        Origami(_x,_y,size/2);
        Origami(_x+size/2,_y,size/2);
        Origami(_x,_y+size/2,size/2);
        Origami(_x+size/2,_y+size/2,size/2);
    }else{
        if(white==0){
            //cout<<_x<<","<<_y<<" : "<<size <<" = white\n";
            whiteCount++;
        }else{
            //cout<<_x<<","<<_y<<" : "<<size <<" = blue\n";
            blueCount++;
        }
    }
}


int N;
int main(){
    cin>>N;
    //arr = new int[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>arr[i][j];
        }
    }

    Origami(0,0,N);

    cout<<whiteCount<<'\n'<<blueCount;
}