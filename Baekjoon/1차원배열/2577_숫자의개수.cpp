#include <iostream>
using namespace std;
int main(){
    int a,b,c;

    int count[10]={0,};

    cin>>a>>b>>c;

    long tmp = a*b*c;

    // 각 자리의 숫자를 구하기 위해서 10으로 나눈 나머지와 몫을 활용한다.
    while(tmp>0){
        count[tmp%10]++;
        tmp/=10;

        if(tmp<10){
            count[tmp]++;
            break;
        }
    }

    for(int i=0; i< sizeof(count)/sizeof(int);i++){
        cout<<count[i]<<'\n';
    }
}