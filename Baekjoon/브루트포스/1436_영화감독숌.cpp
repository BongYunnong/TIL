// https://www.acmicpc.net/problem/1436

// 브루트포스 문제인만큼, 666부터 시작해서 1씩 더해가며 하나씩 체크해보면 된다.
// 어떤 값이 조건에 만족하는지는 10으로 나눠주면서 그 나머지가 6인지, 6이 몇개나 연속으로 나왔는지를 체크하고, 그것이 3번 연속 이상일 경우에는 프로그램 숫자를 증가시켜주면된다.
// 이 프로그램 숫자가 목표 시리즈 넘버가 되면 프로그램 종료이다.

#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;

    int combo=0;
    int maxCombo=0;
    int index=666;

    int resultCount=0;
    
    while(resultCount<N){
        while(true){
            int curr = index;
            combo=0;
            maxCombo=0;
            while(true){
                if(curr<10){
                    if(curr==6)
                        combo++;
                    else
                        combo=0;
                    if(maxCombo<combo)
                        maxCombo=combo;
                    break;
                }else{
                    if(curr%10==6){
                        combo++;
                    }else{
                        combo=0;
                    }
                    curr/=10;
                    if(maxCombo<combo)
                        maxCombo=combo;
                }
            }
            if(maxCombo>=3){
                resultCount++;
                index++;
                break;
            }
            index++;
        }
    }
    cout<<index-1;
}