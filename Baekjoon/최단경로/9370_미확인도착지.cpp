// https://www.acmicpc.net/problem/9370

// 아마도 검색을 해서 문제를 이해한 듯 하다.

// 다익스트라 자체는 크게 어렵지 않다.
// 핵심은 목적지 후보를 가려내는 것인데, 목적지 후보가 진짜 목적지인지 판단하는 방법은,
// start부터 목적지까지의 최단거리가 g,h를 지나서 목적지까지 가는 최단거리와 같은지를 판단하는 것이다.

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define INF 20000000

int T;
int n,m,t;
int s,g,h;
int a,b,d;
int x;
vector<pair<int,int>> vertex[2001]; // 어떠한 vertex에서 다른 vertex까지의 weight, 다음 vertex index 
int SearchPath(int start,int end){
    priority_queue<pair<int,int>> pq;   // weight, 다음 index
    
    int cost[2001];    // start에서부터 i번째로 가는 최소 거리
    for(int i=1;i<=n;i++){
        cost[i]= INF;
    }
    cost[start]=0;
    pq.push({-0,start});

    while(pq.empty()==false){
        int currWeight = -pq.top().first;
        int currDest = pq.top().second;
        pq.pop();
        if(currDest==end){
            return cost[end];
        }
        for(int i =0 ;i<vertex[currDest].size();i++){
            int nextDest = vertex[currDest][i].first;
            int nextWeight = vertex[currDest][i].second+currWeight;
            if(cost[nextDest] > nextWeight){
                cost[nextDest] = nextWeight;
                pq.push({-nextWeight,nextDest});
            }
        }
    }
    return 0;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>T;
    for(int i=0;i<T;i++){
        cin>>n>>m>>t;

        cin>>s>>g>>h; // s에서 시작해서 g,h를 통과하여 목적지 후보까지 도착

        for(int j=0;j<2001;j++){
            vertex[j].clear();
        }
        for(int j=0;j<m;j++){
            cin>>a>>b>>d;

            vertex[a].push_back({b,d});
            vertex[b].push_back({a,d});
        }

        vector<int> answer;
        for(int j=0;j<t;j++){
            cin>>x;

            int sTox = SearchPath(s,x);
            int answer1 = SearchPath(s,g)+SearchPath(g,h)+SearchPath(h,x);
            int answer2 = SearchPath(s,h)+SearchPath(h,g)+SearchPath(g,x);
            if(sTox==answer1|| sTox==answer2){
                answer.push_back(x);
            }
        }
        sort(answer.begin(),answer.end());
        
        for(int j=0;j<answer.size();j++){
            cout<<answer[j]<<' ';
        }
        cout<<'\n';
    }
}