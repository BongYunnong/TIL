// https://www.acmicpc.net/problem/2580
// 원래는 queue에 좌표를 두고, 그 좌표와 연결된 행,열, 사각형 중 그 좌표만 비어져있을 때까지 계속 추가하는 방식
// 시도는 좋았는데, 반례가 있는 듯 하다.(ex. 아무것도 채워지지 않은 input)

// 문제를 푸는 방법은 이렇다.
// vector<pair<int,int>>로 points에 채워야하는 좌표를 추가한다.
// 그리고 그 points에 대해서 1부터 9까지 하나씩 값을 넣어보고, 그것이 옳은 값인지 check한다.
// 만약 모든 값을 넣어보았는데도 채울 수 없다면, 그 값은 나중을 위해 비워둔다.
// 값을 넣어보는 함수가 재귀적으로 호출되므로, 안쪽 point를 다 돌아본 다음에 채워지므로 괜찮다.
// check에서는 행, 열, 사각형을 차례로 검사한다.

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
        // 같은 행에 있는 값들에 대해 체크
        if(board[p.first][i] == board[p.first][p.second] && i != p.second){
            return false;
        }
        // 같은 열에 있는 값들에 대해 체크
        if(board[i][p.second] == board[p.first][p.second] && i!=p.first){
            return false;
        }
    }
    // square에 있는 값들에 대해 체크
    for(int i=3*square_x;i<3*square_x+3;i++){
        for(int j=3*square_y;j<3*square_y+3;j++){
            // 이미 다른 값이 있다면 false
            if(board[i][j] == board[p.first][p.second]){
                if(i!=p.first && j!=p.second){
                    return false;
                }
            }
        }
    }
    // 행,열,square를 다 체크해보았다면 true
    return true;
}
void sudoku(int N){
    // 다 찾았으면 결과 return
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

        // 만약 넣어본 숫자가 올바르다면, 다음 point를 찾음
        if(check(points[N]))
            sudoku(N+1);
        if(found){
            return;
        }
    }
    // 최적의 값을 못 찾았을 경우 값 비워주기 -> 백트래킹
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