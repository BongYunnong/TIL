// https://www.acmicpc.net/problem/14888
#include <iostream>
using namespace std;

int N;

long long minResult=1000000001;
long long maxResult=-1000000001;

long long currResult=0;

int* arr;
int oper[4];
int* currOperator;

void dfs(int index){
    //cout<<"[dfs] : "<<index<<'\n';
    if(index== N-1){
        // 마지막 index에 도달했을 때, 한번에 계산하기
        currResult=arr[0];
        // 저장된 currOpeartor를 다 돌면서 계산
        for(int i=0;i<N-1;i++){
            //cout<<"currResult : "<<currResult<<'_'<<arr[i+1]<<'_'<<currOperator[i]<<'\n';
            switch (currOperator[i])
            {
            case 0:
                currResult+=arr[i+1];
                break;
            case 1:
                currResult-=arr[i+1];
                break;
            case 2:
                currResult*=arr[i+1];
                break;
            case 3:
                currResult/=arr[i+1];
                break;
            default:
                break;
            }
        }
        
        if(currResult <= minResult)
            minResult = currResult;
        if(currResult>=maxResult)
            maxResult = currResult;

        return;
    }
    
    for(int i=0;i<4;i++){
        // 사용 가능한 operator가 있으면 사용
        if(oper[i]>0){
            oper[i]--;
            // currOperator는 중간중간에 넣는 연산자임
            currOperator[index] = i;
            //cout<<"oper.. : "<<currOperator[index]<<'\n';
            dfs(index+1);

            // dfs를 한 후에는 초기화를 위해서 ++
            oper[i]++;
        }
    }
}


int main(){
    cin>>N;
    arr = new int[N];
    currOperator = new int[N-1];
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    for(int i=0;i<4;i++){
        cin>>oper[i];
    }
    dfs(0);

    cout<<maxResult<<'\n'<<minResult;
}