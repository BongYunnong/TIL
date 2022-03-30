#include<iostream>
#include<queue>
#include<vector>

#define MAX 20010
#define INF 987654321
using namespace std;

int V,E;
int startNode;
int cost[MAX];
vector<pair<int,int>> vertex[MAX];


void SearchPath(){
    priority_queue<pair<int,int>> pq;
    pq.push({0,startNode});
    cost[startNode]=0;
    
    // 모든 점에 대해서
    while (pq.empty()==false)
    {
        int Cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for(int i=0;i<vertex[cur].size();i++){
            int next = vertex[cur][i].first;
            int nCost = vertex[cur][i].second;

            if(cost[next] > Cost+nCost){
                cost[next] = Cost+nCost;
                pq.push({-cost[next],next});
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>V>>E;

    cin>>startNode;

    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        vertex[u].push_back({v,w});
    }
    for(int i=1;i<=V;i++){
        cost[i]=INF;
    }


    SearchPath();
    for(int i=1;i<=V;i++){
        if(cost[i]==INF)
            cout<<"INF\n";
        else
            cout<<cost[i]<<'\n';
    }
}

/* 왜 답이 안 나오는지 모르겠음 -> 그런데 잘 풀어도 메모리초과가 뜬다 함
#include<iostream>
#include<queue>
using namespace std;

int V,E;
int startNode;
bool touched[20001];
int cost[20001];
int Weight[20001][20001];


void SearchPath(){
    // 모든 점에 대해서 startNode와 연결해봄
    for(int i=1;i<=V;i++){
        cost[i] = Weight[startNode][i];
    }
    cost[startNode]=0;
    touched[startNode]=true;

    // 모든 점에 대해서
    for(int j=0;j<V-1;j++){
        int min = 2000;
        int shortestIndex=-1;
        for(int i=1;i<=V;i++){
            // 현재 갈 수 있는 가장 작은 edge를 찾아서 저장
            if(touched[i]==true) continue;
            if(cost[i] < min){
                min = cost[i];
                shortestIndex=i;
            }
        }

        // 가장 짧은 edge를 통해서 가는 것이 더 빠르다면 업데이트
        touched[shortestIndex] = true;
        for(int i=1;i<=V;i++){
            if(touched[i]==true) continue;
            if(cost[i] > cost[shortestIndex]+Weight[shortestIndex][i]){
                cost[i] = cost[shortestIndex]+Weight[shortestIndex][i];
            }
        }
    }
}

int main(){
    cin>>V>>E;

    cin>>startNode;

    for(int i=1;i<=V;i++){
        cost[i]=2000;
        for(int j=1;j<=V;j++){
            if(i==j)
                Weight[i][i]=0;
            else
                Weight[i][j]=2000;
        }
    }

    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Weight[u][v] = w;
    }


    SearchPath();
    for(int i=1;i<=V;i++){
        if(cost[i]==2000)
            cout<<"INF\n";
        else
            cout<<cost[i]<<'\n';
    }
}
*/