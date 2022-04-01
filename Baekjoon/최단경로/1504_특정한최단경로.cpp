// pass가 아니라 result<INF를 쓰면 92퍼에서 틀림..
// INF를 2000, VMAX를 정의하지 않고 801로 쓰면 틀림..?
// INF를 2000으로 쓴 것이 문제인듯..
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define INF 2100000000

vector<pair<int,int>> arr[801];
int N,E;
int v1,v2;
bool pass =true;

int SearchPath(int _start,int _end){
    priority_queue<pair<int,int>> pq;
    int dist[801];

    for(int i=1;i<801;i++){
        dist[i]=INF;
    }
    dist[_start]=0;
    pq.push({-0,_start});

    while(pq.empty()==false){
        int next = pq.top().second;
        int weight = -pq.top().first;

        pq.pop();
        if(next==_end)
            return weight;
        
        for(int i=0; i<arr[next].size();i++){
            int y = arr[next][i].first;
            int weightY = arr[next][i].second;

            if(dist[y] > dist[next]+weightY){
                dist[y] = dist[next]+weightY;
                pq.push({-dist[y],y});
            }
        }
    }
    pass=false;
    return 0;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>E;
    for(int i=0;i<E;i++){
        int a,b,c;
        cin>>a>>b>>c;

        arr[a].push_back({b,c});
        arr[b].push_back({a,c});
    }
    cin>>v1>>v2;

    int result1 = SearchPath(1,v1)+SearchPath(v1,v2)+SearchPath(v2,N);
    int result2 = SearchPath(1,v2)+SearchPath(v2,v1)+SearchPath(v1,N);
    int answer = min(result1,result2);
    if(pass){
        cout<<answer;
    }else{
        cout<<"-1";
    }
}

/* 맞는답..
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define VMAX 801
#define INF 2100000000
 
using namespace std;
 
vector<pair<int,int>> a[VMAX];
bool pass = true;
 
int dijkstras(int start, int end){
  priority_queue<pair<int,int>> pq;
  int dist[VMAX];
  for(int i=1; i<VMAX; i++) 
    dist[i] = INF;
  dist[start]=0;
  pq.push({-0, start});
  while(!pq.empty()){
    int x = pq.top().second;
    int wx = -pq.top().first;
    pq.pop();
    if(x==end) return wx;
 
    for(int i=0; i<a[x].size(); i++){
      int y = a[x][i].first;
      int wy = a[x][i].second;
      if(dist[y] > dist[x] + wy){
        dist[y] = dist[x] + wy;
        pq.push({-dist[y], y});
      }
    }
  }
  pass = false;
  return 0;
}
 
int main(){
  int n,e; cin >> n >> e;
  int v1, v2;
  for(int x,y,w,i=0; i<e; i++){
    scanf("%d %d %d", &x, &y, &w);
    a[x].push_back({y,w});
    a[y].push_back({x,w});
  }
  cin >> v1 >> v2;
  int num1 = dijkstras(1, v1) + dijkstras(v1, v2) + dijkstras(v2, n);
  int num2 = dijkstras(1, v2) + dijkstras(v2, v1) + dijkstras(v1, n);
  int result = min(num1, num2);
  if(pass)
    printf("%d\n", result);
  else
    printf("-1\n");
}
*/

// double free라는 에러..
/*
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define INF 2000

vector<pair<int,int>> arr[801];
int N,E;
int v1,v2;

int SearchPath(int _start,int _end){
    priority_queue<pair<int,int>> pq;
    int dist[801];

    for(int i=1;i<=800;i++){
        dist[i]=INF;
    }
    dist[_start]=0;
    pq.push({0,_start});

    while(pq.empty()==false){
        int next = pq.top().second;
        int weight = -pq.top().first;

        pq.pop();
        if(next==_end)
            return weight;
        
        for(int i=0; i<arr[next].size();i++){
            int y = arr[next][i].first;
            int weightY = arr[next][i].second;

            if(dist[y] > dist[next]+weightY){
                dist[y] = dist[next]+weightY;
                pq.push({-dist[y],y});
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>E;
    for(int i=0;i<E;i++){
        int a,b,c;
        cin>>a>>b>>c;

        arr[a].push_back({b,c});
        arr[b].push_back({a,c});
    }
    cin>>v1>>v2;

    int result1 = SearchPath(1,v1)+SearchPath(v1,v2)+SearchPath(v2,N);
    int result2 = SearchPath(1,v2)+SearchPath(v2,v1)+SearchPath(v1,N);
    int aswer = min(result1,result2);
    if(aswer>=INF){
        cout<<"-1";
    }else{
        cout<<aswer;
    }
}
*/

/* 69퍼에서 틀림
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define INF 2000

vector<pair<int,int>> arr[801];
int dist[801];
int N,E;
int v1,v2;

void SearchPath(int _start){
    priority_queue<pair<int,int>> pq;
    for(int i=1;i<=800;i++){
        dist[i]=INF;
    }
    dist[_start]=0;
    pq.push({0,_start});

    while(pq.empty()==false){
        int next = pq.top().second;
        int weight = -pq.top().first;

        pq.pop();

        for(int i=0; i<arr[next].size();i++){
            int y = arr[next][i].first;
            int weightY = arr[next][i].second;

            if(dist[y] > weight+weightY){
                dist[y] = weight+weightY;
                pq.push({-dist[y],y});
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>E;
    for(int i=0;i<E;i++){
        int a,b,c;
        cin>>a>>b>>c;

        arr[a].push_back({b,c});
        arr[b].push_back({a,c});
    }
    cin>>v1>>v2;

    SearchPath(1);
    int sv1 = dist[v1];
    int sv2 = dist[v2];

    SearchPath(v1);
    int v1v2 = dist[v2];
    int v1n = dist[N];

    SearchPath(v2);
    int v2n = dist[N];

    int result1 = sv1+v1v2+v2n;
    int result2 = sv2+v1v2+v1n;
    int aswer = min(result1,result2);
    if(aswer>=INF){
        cout<<"-1";
    }else{
        cout<<aswer;
    }
}
*/

/* 7%에서 틀림
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define INF 2000

int weights[801][801];
int cost[801][801];
int N,E;
int v1,v2;

void SearchPath(){
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cost[i][j]=INF;
        }
        cost[i][i]=0;
    }

    for(int k=1;k<=N;k++){
        for(int j=1;j<=N;j++){
            for(int i=1;i<=N;i++){
                if(cost[k][j] > cost[k][i] +  weights[i][j]){
                    cost[k][j] = cost[k][i] +  weights[i][j];
                }
            }
        }
    }

    int result = min(cost[1][v1]+cost[v1][v2]+cost[v2][N], cost[1][v2]+cost[v2][v1]+cost[v1][N]);

    if(result>=INF){
        cout<<"-1";
    }else{
        cout<<result;
    }

}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>E;
    for(int i=0;i<E;i++){
        int a,b,c;
        cin>>a>>b>>c;

        weights[a][b]=c;
        weights[b][a]=c;
    }
    cin>>v1>>v2;

    SearchPath();
}
*/