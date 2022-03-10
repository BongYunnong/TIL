#include<iostream>
#include <algorithm>
using namespace std;

int N;
int costs[1001][3]; 

int main(){
    cin>>N;

    costs[0][0]=0;
    costs[0][1]=0;
    costs[0][2]=0;

    for(int i=1;i<=N;i++){
        int red, green, blue;
        cin>>red>>green>>blue;
        costs[i][0] = min(costs[i-1][1],costs[i-1][2])+ red;
        costs[i][1] = min(costs[i-1][0],costs[i-1][2])+ green;
        costs[i][2] = min(costs[i-1][0],costs[i-1][1])+ blue;
    }

    cout<<min(costs[N][2],min(costs[N][0],costs[N][1]));
}

/* 시간초과
int N;
tuple<int,int,int> costs[1001]; 

long long minRes=100000000;
int results=0;

int* tmpResutls;

int* colored;
void recursive(int index){
    if(index==N){
        results=0;
        for(int i=0;i<N;i++){
            int color = colored[i];
            int tmpVal=0;
            switch (color)
            {
            case 0 :
                tmpVal= get<0>(costs[i]);
                break;
            case 1 :
                tmpVal= get<1>(costs[i]);
                break;
            case 2 :
                tmpVal= get<2>(costs[i]);
                break;
            default:
                break;
            }
            cout<<"+ "<<tmpVal;
            results += tmpVal;
        }
        cout<<"="<<results<<'\n';
        if(results<=minRes){
            minRes = results;
        }
        return;
    }

    for(int i=0;i<3;i++){
        if(index==0){
            colored[index]=i;
            recursive(index+1);
            colored[index]=-1;
        }else if(colored[index-1]!=i){
            colored[index]=i;
            recursive(index+1);
            colored[index]=-1;
        }
    }
}



int main(){
    cin>>N;

    colored = new int[N+1];
    tmpResutls = new int[N+1];
    for(int i=0;i<N;i++){
        int red, green, blue;
        cin>>red>>green>>blue;
        costs[i] = make_tuple(red,green,blue);
        tmpResutls[i]=-1;
    }

    recursive(0);
    cout<<minRes;
}
*/