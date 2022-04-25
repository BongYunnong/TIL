#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 50

int N,M;
int result;
int grid[MAX][MAX];
vector<pair<int,int>> house,chicken;
bool visited[13];

int distance(pair<int,int> a, pair<int,int>b){
    return abs(a.first-b.first)+abs(a.second-b.second);
}

void dfs(int index, int selected){
    if(selected==M){
        int tmpResult=0;
        for(int i=0;i<house.size();i++){
            int dist = 987654321;
            for(int j=0;j<chicken.size();j++){
                if(visited[j]){
                    dist = min(dist,distance(house[i],chicken[j]));
                }
            }
            tmpResult+=dist;
        }
        result = min(result,tmpResult);
        return;
    }

    if(index==chicken.size())
        return;
    visited[index]=true;
    dfs(index+1,selected+1);
    visited[index]=false;
    dfs(index+1,selected);
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    cin>>N>>M;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>grid[i][j];
            if(grid[i][j]==1)
                house.push_back({i,j});
            else if(grid[i][j]==2)
                chicken.push_back({i,j});
        }
    }
    result=987654321;
    dfs(0,0);
    cout<<result;
}


/*
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int grid[51][51];   // i,j의정보
int Dist[51][51];

vector<int> chickenDist;

vector<pair<int,int>> houses;
vector<pair<int,int>> chickens;

int main(){
    int N,M;
    cin>>N>>M;

    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cin>>grid[i][j];
            if(grid[i][j]==1){
                houses.push_back({i,j});
            }else if(grid[i][j]==2){
                chickens.push_back({i,j});
            }
        }
    }

    for(int i=0;i<chickens.size();i++){
        int row = chickens[i].first;
        int col = chickens[i].second;

        int totalDist =0;
        for(int j=0;j<houses.size();j++){
            totalDist += abs(houses[j].first-row) + abs(houses[j].second-col);
        }
        chickenDist.push_back(totalDist);
    }
    sort(chickenDist.begin(),chickenDist.end());

    for(int i=0;i<chickenDist.size();i++)
    {
        cout<<chickenDist[i]<<' ';
    }
}
*/