#include<iostream>
using namespace std;

int N;
int* results;

int main(){
    cin>>N;
    results = new int[N+1];
    results[0]=0;
    results[1] = 1;
    results[2] = 2;
    results[3] =3;
    for(int i=4;i<=N;i++){
        results[i] = (results[i-1] + results[i-2])%15746;
    }
    cout<<results[N];
}

/* 시간초과
int result=0;
int N;
void Recursive(int index){
    if(index==N){
        result++;
        return;
    }

    for(int i=0;i<2;i++){
        if(i==0 && (index+2)<=N)
            Recursive(index+2);
        else if(i==1)
            Recursive(index+1);
    }
}


int main(){
    cin>>N;
    Recursive(0);
    cout<<(result%15746);
}
*/