#include<iostream>
#include<vector>
using namespace std;

int board[9][9];
vector<pair<int,int>> points;
int cnt=0;
bool found=false;
bool check(pair<int,int> p){
    int square_x = p.first/3;
    int square_y = p.second/3;

    for(int i=0;i<9;i++){
        if(board[p.first][i] == board[p.first][p.second] && i != p.second){
            return false;
        }
        if(board[i][p.second] == board[p.first][p.second] && i!=p.first){
            return false;
        }
    }
    for(int i=3*square_x;i<3*square_x+3;i++){
        for(int j=3*square_y;j<3*square_y+3;j++){
            if(board[i][j] == board[p.first][p.second]){
                if(i!=p.first && j!=p.second){
                    return false;
                }
            }
        }
    }
    return true;
}
void sudoku(int N){
    if(N==cnt){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cout<<board[i][j]<<' ';
            }
            cout<<'\n';
        }
        found=true;
        return;
    }
    for(int j=1;j<=9;j++){
        //1부터 9까지의 숫자를 넣어봄
        board[points[N].first][points[N].second]=j;
        if(check(points[N]))
            sudoku(N+1);
        if(found){
            return;
        }
    }
    // 최적의 값을 못 찾았을 경우 값 비워주기
    board[points[N].first][points[N].second]=0;
    return;
}
int main(){
    pair<int,int> point;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin>>board[i][j];
            if(board[i][j]==0){
                cnt++;
                point.first=i;
                point.second=j;
                points.push_back(point);
            }
        }
    }
    sudoku(0);
}


/* 내가 힘들게 풀었는데 틀린 것
int grid[10][10];
vector<pair<int,int>> queue;

bool isInQueue(int x,int y){
    bool found=false;
    for(int i=0;i<queue.size();i++){
        if(queue[i].first==x && queue[i].second==y){
            found=true;
            break;
        }
    }
    return found;
}

void dfs(int x,int y){
    int count = 0;
    int counting=0;
    if(grid[x][y]==0){
        queue.push_back(make_pair(x,y));

        int xMul = (x-1)/3;
        int yMul = (y-1)/3;

        for(int i=xMul*3+1;i<xMul*3+4;i++){
            for(int j=yMul*3+1;j<yMul*3+4;j++){
                if(grid[i][j]==0 && i!=x && j!=y && !isInQueue(x,y)){
                    dfs(i,j);
                }
                count+=grid[i][j];
                if(grid[i][j]!=0)
                    counting++;
            }
        }
        if(45-count<10&& counting==8){
            grid[x][y] = 45-count;
            return;
        }

        count=0;
        counting=0;
        for(int i=1;i<=9;i++){]
            if(grid[i][y]==0 && i!=x && !isInQueue(i,y)){
                dfs(i,y);
            }
            count+=grid[i][y];
            if(grid[i][y]!=0)
                counting++;
        }
        if(45-count<10 && counting==8){
            grid[x][y] = 45-count;
            return;
        }

        count=0;
        counting=0;
        for(int j=1;j<=9;j++){
            if(grid[x][j]==0 && j!=y&& !isInQueue(x,j)){
                dfs(x,j);
            }
            count+=grid[x][j];
            if(grid[x][j]!=0)
                counting++;
        }
        if(45-count<10&& counting==8){
            grid[x][y] = 45-count;
            return;
        }

    }
}

int main(){
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            cin>>grid[i][j];
        }
    }

    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(grid[i][j]==0){
                queue.clear();
                dfs(i,j);
            }
        }
    }
    



    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            cout<<grid[i][j]<<' ';
        }
        cout<<'\n';
    }
}
*/