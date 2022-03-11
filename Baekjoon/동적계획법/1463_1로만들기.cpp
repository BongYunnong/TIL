#include <iostream>
using namespace std;
# define MAX 1000001
long N;

int results[MAX];
int main(){
    cin>>N;

    results[1]=0;
    results[2]=1;
    results[3]=1;
    results[4]=2;

    for(int i=4;i<=N;i++){
        int oper1 = MAX;
        int oper2 = MAX;
        int oper3 = results[i-1];
        if(i%3==0)
            oper1 = results[i/3];
        if(i%2==0)
            oper2 = results[i/2];
        
        results[i] = min(min(oper1, oper2) , oper3)+1;
    }
    cout<<results[N];
}