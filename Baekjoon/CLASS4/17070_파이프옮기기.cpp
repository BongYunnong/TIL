#include<iostream>
#include<queue>
using namespace std;


int grid[17][17];
int N;

int ans;
void BFS(){
    queue<pair<int,pair<int,int>>> q;
    q.push({0,{0,1}});

    while(q.empty()==false){
        int angle = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;

        q.pop();

        if(row==N-1 && col==N-1){
            ans++;
            continue;
        }

        if(row+1<N && col+1 < N && 
           grid[row+1][col]==0 && grid[row+1][col+1]==0 && grid[row][col+1]==0)
        {
            q.push({45,{row+1,col+1}});
        }
        if(angle!=90){
            if(col+1<N && grid[row][col+1]==0){
                q.push({0,{row,col+1}});
            }
        }
        if(angle!=0){
            if(row+1<N && grid[row+1][col]==0){
                q.push({90,{row+1,col}});
            }
        }
    }
}


int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N;

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>grid[i][j];
        }
    }

    BFS();
    cout<<ans;
}