// https://www.acmicpc.net/problem/1717

// 합집합 연산과 두 원소가 같은 집합에 포함되어있는지 확인하는 연산이 주어짐

// 시간초과가 뜬 이유
// 1. union을 할 때, 자식의 값으로 넣어줌
// 2. GetParent를 할 때 parent[source]에 대입을 하지 않음..?


#include<iostream>
using namespace std;

int parent[1000001];

int GetParent(int source){
    if(parent[source]==source){
        return source;
    }else{
        return parent[source] = GetParent(parent[source]);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int n,m;
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        parent[i]=i;
    }
    for(int i=0;i<m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        if(x==0){
            int parent1=GetParent(y);
            int parent2=GetParent(z);
            if(parent1>parent2){
                parent[parent1]=parent2;
            }else{
                parent[parent2]=parent1;
            }
        }else if(x==1){
            int p1 = GetParent(y);
            int p2 = GetParent(z);
            if(p1==p2){
                cout<<"YES\n";
            }else{
                cout<<"NO\n";
            }
        }
    }
}


/* 시간초과 2
#include<iostream>
using namespace std;

int parent[1000001];

int GetParent(int source){
    int tmp = parent[source];
    if(tmp==-1){
        return source;
    }else{
        return GetParent(tmp);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int n,m;
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        parent[i]=-1;
    }
    for(int i=0;i<m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        if(x==0){
            int parent1=GetParent(y);
            int parent2=GetParent(z);
            if(parent1==parent2){
                continue;
            }
            if(parent1<parent2){
                parent[parent2]=y;
            }else{
                parent[parent1]=z;
            }
        }else if(x==1){
            int p1 = GetParent(y);
            int p2 = GetParent(z);
            if(p1==p2){
                cout<<"YES\n";
            }else{
                cout<<"NO\n";
            }
        }
    }
}
*/