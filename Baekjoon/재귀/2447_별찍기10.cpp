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
