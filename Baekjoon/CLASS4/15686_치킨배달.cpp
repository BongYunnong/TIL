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