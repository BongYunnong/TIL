#include <iostream>
using namespace std;

int result[101][101][101];

int Recursive(int a,int b,int c){
    if(a<=0 || b<=0 || c<=0){
        result[a+50][b+50][c+50] =1;
        return 1;
    }else{
        if(result[a+50][b+50][c+50]!=-1000000){
            return result[a+50][b+50][c+50];
        }else{
            if(a>20 || b>20 || c>20){
                result[a+50][b+50][c+50] =Recursive(20,20,20);
                return result[a+50][b+50][c+50];
            }else if(a<b && b<c){
                result[a+50][b+50][c+50] =Recursive(a,b,c-1) + Recursive(a,b-1,c-1) - Recursive(a,b-1,c);
                return result[a+50][b+50][c+50];
            }else{
                result[a+50][b+50][c+50] =Recursive(a-1,b,c) + Recursive(a-1,b-1,c) + Recursive(a-1,b,c-1) - Recursive(a-1,b-1,c-1);
                return result[a+50][b+50][c+50];
            }
        }
    }

}

int a,b,c;
int main(){
    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            for(int k=0;k<101;k++){
                result[i][j][k] = -1000000;
            }
        }
    }

    while(true){
        cin>>a>>b>>c;
        if(a==-1 && b==-1 && c==-1){
            break;
        }else{
            cout<<"w("<<a<<", "<<b<<", "<<c<<") = "<<Recursive(a,b,c)<<'\n';
        }
    }
}