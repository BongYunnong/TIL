// https://www.acmicpc.net/problem/2565
// 전봇대 A와 B 사이에 하나 둘씩 전깃줄을 추가하다보니 교차하는 경우가 생긴다.
// 이 전깃줄들 중 몇 전깃줄을 없애서 전깃줄이 교차하지 않도록 해야한다.
// 교차하지 않도록 만드는 전깃줄의 최소 개수는?

// F(N) = N개까지 이었을 때 잘라야하는 최소 전깃줄 개수
// 만약 전깃줄이 지금까지의 전깃줄보다 second가 작다면, 교차되는 것이므로 해당 전깃줄을 잘라버려야한다.
// 순서대로 전깃줄을 잇기 위해서 전깃줄 first 기준으로 오름차순 정렬해야한다.

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int results[101];
int main(){
    int n;
    vector<pair<int,int>> lines;
    cin>>n;
    lines.push_back({0,0});
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        lines.push_back({a,b});
    }
    sort(lines.begin(),lines.end());
    results[1] = 1;
    int result=100;
    for(int i=2;i<=n;i++){
        // 이으려고 하는 전깃줄 이전의 전깃줄을 탐색
        for(int j=i-1;j>=0;j--){
            // 교차하지 않는데 results가 이전 것보다 작거나 같으면 results update
            // 교차하지 않는데 results가 이전 것보다 크다면, 그대로 가져가야함
            if(lines[i].second>lines[j].second){
                if(results[i]<=results[j]){
                    results[i] = results[j]+1;
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        // 이어진 것 빼고는 다 잘라내야하므로 n - resutls[i]
        result = min(result,n-results[i]);
    }
    cout<<result;
}


/* 틀림 - 왜 틀렸는지는 모름
int N;
vector<pair<int,int>> lines;
int results[101];

bool Compare(pair<int,int> a, pair<int,int> b){
    if(a.first==b.first){
        return a.second<b.second;
    }else{
        return a.first < b.first;
    }
}

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        int a;
        int b;
        cin>>a>>b;
        lines.push_back(make_pair(a,b));
    }
    sort(lines.begin(),lines.end(),Compare);

    int Result=0;
    for(int i=0;i<N;i++){
        results[i]=1;
        for(int j=i-1;j>=1;j--){
            if(lines[i].second > lines[j].second){
                results[i] = max(results[i],results[j]+1);
            }
        }
        Result = max(Result,results[i]);
    }
    cout<< N-Result;
}
*/

// line을 정렬하는 것과 N-count가 답이라는 것 까지 도출한 것은 좋은데
// 그 이후에 처리하는 방법이 잘못됨 -> 오른쪽 전봇대에서 '가장 긴 증가하는 부분수열'을 찾는 것이 목표임

/* 시간초과
int result;
int N;

vector<pair<int,int>> lines;

bool Compare(pair<int,int> a, pair<int,int> b){
    if(a.first==b.first){
        return a.second<b.second;
    }else{
        return a.first < b.first;
    }
}

void Recursive(int index,int yMax,int count){
    if(index>=N){
        if(count>result){
            result = count;
        }
        //cout<<endl;
        return;
    }

    if(index==0){
        Recursive(index+1,lines[0].second,1);
        Recursive(index+2,yMax,0);
    }else{
        if(lines[index+1].second > yMax){
            //cout<<(index+1)<<' ';
            Recursive(index+1,lines[index].second,count+1);
        }
        Recursive(index+2,yMax,count);
    }
}

int main(){
    cin>>N;

    for(int i=0;i<N;i++){
        int a;
        int b;
        cin>>a>>b;
        lines.push_back(make_pair(a,b));
    } 
    sort(lines.begin(),lines.end(),Compare);
    Recursive(0,0,0);
    //cout<<endl;
    cout<<(N+1)-result;
}
*/