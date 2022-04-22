#include<iostream>
#include<vector>
using namespace std;

bool grid[51][51];
bool detective[51];

vector<int> party[51];
int main(){
    int N,M;
    cin>>N>>M;
    int tc;
    cin>>tc;
    for(int i=0;i<tc;i++){
        int tmp;
        cin>>tmp;
        detective[tmp]=true;
    }

    for(int i=0;i<M;i++){
        int c;
        cin>>c;

        bool detect=false;
        for(int j=0;j<c;j++){
            int tmp;
            cin>>tmp;
            party[i].push_back(tmp);
        }

        for(int j=0;j<party[i].size();j++){
            for(int k=0;k<party[i].size();k++){
                grid[players[j]][players[k]]=true;
                grid[players[k]][players[j]]=true;
            }
        }
    }
}