// https://www.acmicpc.net/problem/2252
// 위상정렬을 배운 다음 처음 푼 문제
// 조금 애매해서 틀릴 줄 알았는데 바로 맞았다고 뜸

#include<iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int indegree[100001];
vector<int> G[100001];
int N,M;

void topologySort(){
    vector<int> result;
    queue<int> q;

    // degree가 0이라면 국부적으로 부모인 것들. 
    for(int i=1;i<=N;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }

    while(q.empty()==false){
        int x = q.front();
        q.pop();
        result.push_back(x);
        // 국부적 부모에서부터 아래에 있는 것들을 모두 체크
        for(int i=0;i<G[x].size();i++){
            indegree[G[x][i]]--;
            // 체크 되었다면 degree--
            if(indegree[G[x][i]]==0){
                // 이제 더이상 부모가 없으면 queue에 push
                q.push(G[x][i]);
            }
        }
    }
    for(int i=0;i<result.size();i++){
        cout<<result[i]<<' ';
    }
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cin>>N>>M;

    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        // 자식으로 들어가는 것은 degree ++
        indegree[b]++;
    }
    topologySort();

}
