#include<iostream>
using namespace std;

char GetDiff(char _input){
    if(_input=='B')
        _input='W';
    else
        _input = 'B';
    return _input;
}

int main(){
    int N,M;
    cin>>N>>M;

    char grid[51][51];

    char val;
    char diffVal;
    for(int x=0;x<N;x++){
        for(int y=0;y<M;y++){
            cin>>grid[x][y];
        }
    }
    int min=10000000;
    int count=0;
    int count2=0;
    for(int x=0;x<=N-8;x++){
        for(int y=0;y<=M-8;y++){
            count=0;
            count2=0;
            val = grid[x][y];
            diffVal = GetDiff(val);

            for(int i=x;i<x+8;i++){
                for(int j=y;j<y+8;j++){
                    if(val!=grid[i][j]){
                        count++;
                    }
                    if(diffVal!=grid[i][j]){
                        count2++;
                    }
                    
                    val =GetDiff(val);
                    diffVal =GetDiff(diffVal);
                }
                val =GetDiff(val);
                diffVal =GetDiff(diffVal);
            }
            if(min>count){
                min = count;
            }
            if(min>count2){
                min = count2;
            }
        }
    }
    cout<<min;
}