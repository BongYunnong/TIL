// https://www.acmicpc.net/problem/1976
// Union Find 알고리즘을 안 상태에서 도전했는데
// 계속 틀린 문제

// 아직도 왜 틀린지는 모르겠음 -> 아무래도 Union쪽이 의심스러움  -> i와 j의 index를 0으로 시작해서 틀린듯..? dest는 1,2,3 이렇게 가기 떄문

#include<iostream>
using namespace std;

int parent[201];
int GetParent(int source){
    if(parent[source]==source){
        return source;
    }else{
        return parent[source] = GetParent(parent[source]);
    }
}


int main(){
    int N;
    cin>>N;
    int M;
    cin>>M;
    for(int i=0;i<201;i++){
        parent[i]=i;
    }

    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            int tmp;
            cin>>tmp;
            if(tmp==1){
                int Pi = GetParent(i);
                int Pj = GetParent(j);
                if(Pi!=Pj){
                    parent[Pi]=Pj;
                    GetParent(Pi);
                }
            }
        }
    }

    int currParent=-1;
    for(int i=0;i<M;i++){
        int dest;
        cin>>dest;
        if(currParent==-1)
            currParent = GetParent(dest);
        else{
            if(GetParent(dest)!=currParent){
                cout<<"NO";
                return 0;
            }
        }
    }
    cout<<"YES";
}

/* 28퍼 틀림
#include<iostream>
using namespace std;

int parent[201];
int GetParent(int source){
    if(parent[source]==source){
        return source;
    }else{
        return parent[source] = GetParent(parent[source]);
    }
}

int main(){
    int N;
    cin>>N;
    int M;
    cin>>M;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int tmp;
            cin>>tmp;
            if(tmp==1){
                int Pi = GetParent(i);
                int Pj = GetParent(j);
                if(Pi<Pj){
                    parent[j]=Pi;
                }else{
                    parent[i]=Pj;
                }
            }
        }
    }

    int currParent=-1;
    for(int i=0;i<M;i++){
        int dest;
        cin>>dest;
        if(currParent==-1)
            currParent = parent[dest];
        else{
            if(parent[dest]!=currParent){
                cout<<"NO";
                return 0;
            }
        }
    }
    cout<<"YES";
}
*/