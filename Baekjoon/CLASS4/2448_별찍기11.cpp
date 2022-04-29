// https://www.acmicpc.net/problem/2448

// grid column수를 잘못 생각해서 한 번 틀림

#include<iostream>
using namespace std;

char grid[3100][7000];


void DrawStar(int _row, int _col, int count){
    if(count==3){
        grid[_row][_col+2]='*';
        grid[_row+1][_col+1]='*';
        grid[_row+1][_col+3]='*';
        grid[_row+2][_col+0]='*';
        grid[_row+2][_col+1]='*';
        grid[_row+2][_col+2]='*';
        grid[_row+2][_col+3]='*';
        grid[_row+2][_col+4]='*';
        return;
    }

    DrawStar(_row           ,_col+count/2   ,count/2);
    DrawStar(_row+count/2   ,_col           ,count/2);
    DrawStar(_row+count/2   ,_col+count     ,count/2);
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;
    int tmp =1 ;
    int k=0;
    while (true)
    {
        if(tmp==N/3){
            break;
        }
        tmp*=2;
        k++;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<2*N-1;j++){
            grid[i][j]=' ';
        }
    }

    DrawStar(0,0,N);


    
    for(int i=0;i<N;i++){
        for(int j=0;j<2*N-1;j++){
            cout<<grid[i][j];
        }
        cout<<'\n';
    }

}