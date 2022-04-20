
// 왜 내꺼는 틀리는데... 진짜..
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

bool visited[10001];
vector<pair<int,int>> graph[10001];
typedef pair<int, int> pair_ii;
priority_queue<pair_ii, vector<pair_ii> ,greater<pair_ii>> pq;

int V,E;
int A,B,C;
int ans;
int main(){
    cin>>V>>E;

	for (int i = 0; i < E; i++)
	{
		cin >> A >> B >> C;
		graph[A].push_back(make_pair(B, C));
		graph[B].push_back(make_pair(A, C));
	}

	pq.push(make_pair(0, 1));

	while (!pq.empty())
	{
		int now_weight = pq.top().first;
		int now_node = pq.top().second;
		pq.pop();

		if (visited[now_node]) continue;
		visited[now_node] = true;

		ans += now_weight;

		for (int i = 0; i < graph[now_node].size(); i++)
		{
			int next_node = graph[now_node][i].first;
			int next_weight = graph[now_node][i].second;

			pq.push(make_pair(next_weight, next_node));
		}
	}
	cout << ans << '\n';
}

// 진짜...
/*
#include<iostream>
#include<vector>

using namespace std;

bool visited[10001];
vector<pair<int,int>> W[10001];

int MST(int n){
    int dist[10001];
    int vnear;
    int result=0;
    for(int i=2;i<=n;i++){
        int founded=-1;
        for(int j=0;j<W[i].size();j++){
            if(W[i].at(j).first==1){
                founded=j;
            }
        }
        if(founded>=0)
            dist[i]=W[i].at(founded).second;
        else
            dist[i]=2000000;
    }
    visited[1]=true;

    for(int k=1;k<=n-1;k++){
        int MIN = 2000000;
        for(int i=2;i<=n;i++){
            if(dist[i]<MIN && visited[i]==false){
                MIN = dist[i];
                vnear=i;
            }
        }

        //cout<<vnear<<" : "<<dist[vnear]<<'\n';
        result+=dist[vnear];
        visited[vnear]=true;

        for(int i=2;i<=n;i++){
            int founded=-1;
            for(int j=0;j<W[i].size();j++){
                if(W[i].at(j).first==vnear){
                    founded=j;
                }
            }
            if(founded>=0){
                if(W[i].at(founded).second < dist[i]){
                    dist[i] = W[i].at(founded).second;
                }
            }
        }
    }
    cout<<result<<'\n';
    return result;
}

int main(){
    int V,E;
    cin>>V>>E;

    for(int i=0;i<E;i++){
        int a,b,c;
        cin>>a>>b>>c;
        W[a].push_back({b,c});
        W[b].push_back({a,c});
    }
    MST(V);
}
*/