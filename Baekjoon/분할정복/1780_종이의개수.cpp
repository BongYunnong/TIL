#include<iostream>
using namespace std;

//2187
int arr[2200][2200];

int result0;
int result1;
int result2;


void Origami(int _x,int _y,int _size){
    int originType = arr[_x][_y];
    bool match=true;
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
        if(originType==-1){
            result0++;
        }else if(originType==0){
            result1++;
        }else{
            result2++;
        }
    }else{
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