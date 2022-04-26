// https://www.acmicpc.net/problem/11725

// 루트 없는 트리에서 트리의 루트를 1이라 정했을 때 각 노드의 부모는?
// 1에서부터 시작해서 자식들을 돌아다니며 그 자식의 부모를 이전 노드로 만들어주면 된다.


#include<iostream>
#include<vector>

using namespace std;

int N;
int arr[100001];
bool visited[100001];
vector<int> v[100001];

void GetParent(int _start){
    visited[_start]=true;
    for(int i=0;i<v[_start].size();i++){
        int next = v[_start][i];
        if(visited[next]==false){
            arr[next] = _start;
            GetParent(next);
        }
    }
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    cin>>N;
    for(int i=0;i<N-1;i++){
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    GetParent(1);
    for(int i=2;i<=N;i++){
        cout<<arr[i]<<'\n';
    }
}

/* 그냥 배열로 했을 경우... 틀림
#include<iostream>
using namespace std;
int arr[100001];
bool visited[100001];
int N;
int GetParent(int _x){
    for(int i=1;i<=N;i++){
        visited[i]=false;
    }
    while(true){
        visited[_x]=true;
        if(arr[_x]==200000){
            // 다음 부모가 없을 경우 마지막 부모 리턴
            return _x;
        }else if(arr[_x]==1){
            // 다음 부모가 1이라면 1 리턴
            return 1;
        }else if(visited[arr[_x]]==true){
            return _x;
        }
        _x = arr[_x];
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    cin>>N;
    for(int i=0;i<=N;i++)
        arr[i]=200000;
    arr[1] = 1;
    for(int i=1;i<N;i++){
        int num1,num2;
        cin>>num1>>num2;

        if(GetParent(num1)==1){
            arr[num2]=num1;
        }else if(GetParent(num2)==1){
            arr[num1]=num2;
        }else{
            arr[num2]=num1;
            arr[num1]=num2;
        }
    }

    for(int i=2;i<=N;i++){
        cout<<arr[i]<<'\n';
    }
}
*/