#include<iostream>
using namespace std;

int main(){
    int Na,Ma;
    cin>>Na>>Ma;

    int A[101][101];
    for(int i=0;i<Na;i++){
        for(int j=0;j<Ma;j++){
            cin>>A[i][j];
        }
    }

    int Mb,Kb;
    cin>>Mb>>Kb;
    int B[101][101];
    for(int i=0;i<Mb;i++){
        for(int j=0;j<Kb;j++){
            cin>>B[i][j];
        }
    }


    int Results[101][101];
    for(int i=0;i<Na;i++){
        for(int j=0;j<Kb;j++){
            int tmp=0;
            for(int t = 0; t<Ma;t++){
                tmp += A[i][t] * B[t][j];
            }
            Results[i][j] = tmp;
            cout<<tmp<<' ';
        }
        cout<<'\n';
    }
}