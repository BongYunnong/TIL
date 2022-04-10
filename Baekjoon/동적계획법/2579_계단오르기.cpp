// https://www.acmicpc.net/problem/2579
// 계단 아래에서부터 시작해서 계단 꼭대기에 위치한 도착점까지 가는 게임
// 1. 계단은 한번에 한 계단씩 혹은 두 계단씩 오를 수 있다.
// 2. 연속된 세 개의 계단을 모두 밟아서는 안 된다. 단, 시작점은 계단에 포함되지 않는다.
// 3. 마지막 도착 계단은 반드시 밟아야 한다.

// 마지막 계단을 꼭 밟아야하므로 F(N)은 N을 밟았을 때 얻을 수 있는 점수의 최댓값이다.
// F(N) = max(F(N-3)+arr[N-1]+arr[N], F(N-3)+arr[N-2]+arr[N])인데, F(N-3)+arr[N-2]는 F(N-2)이므로
// F(N) =  max(F(N-3)+arr[N-1]+arr[N], F(N-2)+arr[N])이다.
// 만약 마지막 계단을 안 밟아도 된다고 하면 F(N) = max(F(N-3)+arr[N-1]+arr[N], max(F(N-2)+arr[N], F(N-1)))이다.

#include <iostream>
using namespace std;

int N;
int results[301];
int costs[301];

int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>costs[i];
    }

    results[1]=costs[1];
    results[2] = costs[1]+costs[2];
    results[3] = max(costs[1]+costs[3], costs[2]+costs[3]);
    for(int i=4;i<=N;i++){
        results[i] = max(results[i-2]+costs[i], results[i-3]+costs[i-1]+costs[i]);
    }
    cout<<results[N];
}

/* 시간초과
int N;
int costs[301];

int result=0;

bool visited[301];

void Recursive(int _index){
    if(_index>N){
        //cout<<"WRONG";
        return;
    }
    
    if(_index==N){
        if(_index>=3 && visited[_index-1] && visited[_index-2])
            return;
        visited[_index]=true;
        int tmpResult=0;
        for(int i=1;i<=N;i++){
            if(visited[i]){
                tmpResult+= costs[i];
                //cout<<"+"<<costs[i];
            }
        }
        //cout<<'\n';

        if(tmpResult>= result)
            result=tmpResult;
        return;
    }

    if(_index>=3){
        //cout<<"index:"<<_index<<'\n';
        if(visited[_index-1]){
            visited[_index]=false;
            Recursive(_index+1);
            if(visited[_index-2]==false){
                visited[_index]=true;
                Recursive(_index+1);
            }
        }else{
            visited[_index]=true;
            Recursive(_index+1);
        }
    }else if(_index>=2){
        if(visited[_index-1]==false){
            visited[_index]=true;
            Recursive(_index+1);
        }else{
            visited[_index]=true;
            Recursive(_index+1);
            visited[_index]=false;
            Recursive(_index+1);
        }
    }else{
        visited[_index]=true;
        Recursive(_index+1);
        visited[_index]=false;
        Recursive(_index+1);
    }

}


int main(){
    cin>>N;

    for(int i=1;i<=N;i++){
        cin>>costs[i];
    }

    Recursive(1);

    cout<<result;
}
*/