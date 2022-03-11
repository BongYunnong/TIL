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