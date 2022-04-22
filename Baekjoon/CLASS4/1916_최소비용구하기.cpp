
// 일단 아래 것이 없어서 시간 초과가 나왔다.
// if(dist[currPos]<currWeight)continue;

// 아, INFINITY가 부족했구나
// 987654321


#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dist[1001];
int tmp,_end;
int N,M;
vector<pair<int,int>> buses[1001];
void SearchPath(){
    priority_queue<pair<int,int>> pq;
    pq.push({-0,tmp});
    for(int i=1;i<=N;i++){
        dist[i]=987654321;
    }
    dist[tmp]=0;

    while(pq.empty()==false){
        int currWeight = -pq.top().first;
        int currPos = pq.top().second;
        pq.pop();

        if(dist[currPos]<currWeight)
            continue;

        for(int i=0;i<buses[currPos].size();i++){
            int nextWeight = buses[currPos].at(i).second + currWeight;
            int nextPos = buses[currPos].at(i).first;
            if(dist[nextPos] > nextWeight){
                dist[nextPos] = nextWeight;
                pq.push({-nextWeight,nextPos});
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0;i<M;i++){
        int a,b,c;
        cin>>a>>b>>c;
        buses[a].push_back({b,c});
    }
    cin>>tmp>>_end;
    SearchPath();

    cout<<dist[_end];
}