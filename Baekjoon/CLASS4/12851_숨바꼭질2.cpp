// Visited를 어디에다가 놓는지가 관건
// 처음에 2개 메모리초과 된 것은 visited[val-1]== true이렇게 했기 때문...

// 추가적으로 counting>minimumAnswer, visited[val]=true;가 필요했다.

#include<iostream>
#include<queue>
using namespace std;

int N,K;

int minimumAnswer=100001;
int combo=0;

bool visited[100001];

void BFS(){
    queue<pair<int,int>> q;
    q.push({N,0});
    while(q.empty()==false){
        int val = q.front().first;
        int counting = q.front().second;
        q.pop();

        if(counting>minimumAnswer) continue;
        visited[val] = true;

        if(val==K){
            if(minimumAnswer>counting){
                minimumAnswer=counting;
                combo=1;
            }else if(minimumAnswer==counting){
                combo++;
            }
        }else if(counting< minimumAnswer){
            if(val-1>=0){
                if(visited[val-1]==false){
                    q.push({val-1,counting+1});
                }
            }
            if(val+1<=100000){
                if(visited[val+1]==false){
                    q.push({val+1,counting+1});
                }
            }
            if(val*2<=100000){
                if(visited[val*2]==false){
                    q.push({val*2,counting+1});
                }
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>K;
    BFS();
    cout<<minimumAnswer<<'\n'<<combo;
}