#include<vector>
#include<queue>
using namespace std;

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

bool visited[101][101];

void bfs(pair<int,int> start){
    queue<pair<int,int>> q;
    q.push(start);
    visited[start.first][start.second]=true;
    
    while(q.empty()==false){
        pair<int,int> curr = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int nx = curr.first+dx[i];
            int ny = curr.second+dy[i];
            if(nx>=0 && ny>=0 && nx<=101 && ny<=101){
                if(visited[nx][ny]==false){
                    visited[nx][ny]=true;
                    q.push(make_pair(nx,ny));
                }
            }
        }
    }
}

int solution(vector<vector<int> > maps)
{
    int answer = 0;
    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            visited[i][j]=false;
        }
    }
    bfs({0,0});
    
    return answer;
}

void main(){
    maps.push_back()
    solution();
}
