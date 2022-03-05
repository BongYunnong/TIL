#include<iostream>

using namespace std;
int main(){
    int N;
    cin>>N;

    int xs[51];
    int ys[51];

    int x,y;
    for(int i=0;i<N;i++){
        cin>>x>>y;

        xs[i]=x;
        ys[i]=y;
    }

    for(int i=0;i<N;i++){
        int count=0;
        for(int j=0;j<N;j++){
            if(i==j || (xs[i]<xs[j] && ys[i]<ys[j])){
                count++;
            }
        }
        cout<<count <<' ';
    }
}