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
        currResult=arr[0];
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
        if(oper[i]>0){
            oper[i]--;
            currOperator[index] = i;
            //cout<<"oper.. : "<<currOperator[index]<<'\n';
            dfs(index+1);
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