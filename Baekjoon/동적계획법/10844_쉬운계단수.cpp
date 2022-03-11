#include<iostream>
using namespace std;
#define DIV 1000000000
int N;
long long results[101][11];
long long Result;
int main(){
    cin>>N;
    for(int i=1;i<=9;i++){
        results[1][i] = 1;
    }
    results[1][0]=0;


    for(int i=2;i<=N;i++){
        for(int j=0;j<=9;j++){
            if(j==0)
                results[i][j] = results[i-1][j+1]%DIV;
            else if(j==9)
                results[i][j] = results[i-1][j-1]%DIV;
            else
                results[i][j] = (results[i-1][j+1] + results[i-1][j-1])%DIV;
        }
    }

    Result=0;
    for(int i=0;i<10;i++){
        Result+= results[N][i];
    }
    cout<<Result%DIV;
}

/* 틀림
#define MAX 101
int N;
long long results[MAX];

long long ResCount=0;
int currNum;
void Recursive(int _index){
    if(_index==N){
        ResCount++; 
        return;
    }

    if(_index==0){
        for(int i=1;i<=9;i++){
            currNum=i;
            Recursive(_index+1);
        }
    }else{
        if(currNum>1){
            currNum--;
            Recursive(_index+1);
        }

        if(currNum<9){
            currNum++;
            Recursive(_index+1);
        }
    }
}

int main(){
    cin>>N;

    Recursive(0);
    cout<<(ResCount%1000000000);
}
*/