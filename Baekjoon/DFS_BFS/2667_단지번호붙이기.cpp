// https://www.acmicpc.net/problem/2667
// 1은 집이 있는 곳을 0은 집이 없는 곳을 나타낸다.
// 단지는 대각선이 아닌 상하좌우로만 연결되어있을때, 단지의 수를 구하시오


// 오름차순인것을 까먹어서 틀림

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

vector<pair<int,int>> inputs;
int grid[26][26];
int N;
vector<int> houseCount;
void DFS(int _x,int _y){
    if(grid[_x][_y]!=1){
        return;
    }

    houseCount.at(houseCount.size()-1)++;
    grid[_x][_y]=2;

    if(0<= _x-1){
        DFS(_x-1,_y);
    }
    if(_x+1<N){
        DFS(_x+1,_y);
    }
    if(0<=_y-1){
        DFS(_x,_y-1);
    }
    if(_y+1<N){
        DFS(_x,_y+1);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;

    for(int i=0;i<N;i++){
        string input;
        cin>>input;

        for(int j=0;j<input.size();j++){
            grid[i][j] = input.at(j)-'0';

            if(grid[i][j]==1){
                inputs.push_back({i,j});
            }
        }
    }

    for(int i=0;i<inputs.size();i++){
        if(grid[inputs[i].first][inputs[i].second]==1){
            houseCount.push_back(0);
            DFS(inputs[i].first,inputs[i].second);
        }
    }

    sort(houseCount.begin(),houseCount.end());
    cout<<houseCount.size()<<'\n';
    for(int i=0;i<houseCount.size();i++){
        cout<<houseCount[i]<<'\n';
    }
}