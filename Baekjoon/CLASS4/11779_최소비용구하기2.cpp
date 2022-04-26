// https://www.acmicpc.net/problem/11779

// 다익스트라는 priority queue 잘 써서 구현을 했는데, 경로를 추적하는 방법을 몰랐다.
// 예상한대로, 그냥 배열을 하나 더 만들어서 부모를 찾아나가듯이 하면 된다.

// 여기서 가장 큰 문제는 에제 출력이 1 3 5라고 잘못 나왔다는 것이었다. 원래는 1 4 5여야한다. -> 둘 다 정답이라고한다.

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<pair<int,int>> buses[1001];
int n,m;
int startPos,endPos;

int dist[1001];
int route[1001];
void SearchPath(){
    priority_queue<pair<int,int>> pq;
    pq.push({0,startPos});
    dist[startPos]=0;
    
    while(pq.empty()==false){
        int weight = -pq.top().first;
        int curr = pq.top().second;
        pq.pop();
        if(curr==endPos)
            break;

        for(int i=0;i<buses[curr].size();i++){
            int next = buses[curr].at(i).first;
            int nextWeight = buses[curr].at(i).second;
            if(dist[next] > dist[curr]+nextWeight){
                dist[next] = dist[curr]+nextWeight;
                pq.push({-dist[next],next});
                route[next]=curr;
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>n>>m;

    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        buses[a].push_back({b,c});
    }
    cin>>startPos>>endPos;
    fill(dist,dist+n+1,987654321);
    SearchPath();
    cout<<dist[endPos]<<'\n';
    
    vector<int> path;
    int index=endPos;
    while(index !=startPos){
        path.push_back(index);
        index=route[index];
    }
    path.push_back(startPos);

    cout<<path.size()<<'\n';
    for(int i=path.size()-1;i>=0;i--){
        cout<<path[i]<<' ';
    }
}