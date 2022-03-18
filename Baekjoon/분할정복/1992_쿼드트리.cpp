#include<iostream>
#include<string>
using namespace std;

int arr[65][65];

void QuadTree(int _x, int _y, int _size){
    int white=arr[_x][_y];
    bool match=true;
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
        if(white==0){
            cout<<0;
        }else{
            cout<<1;
        }
    }else{
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