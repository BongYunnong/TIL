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
        for(int j=i-1;j>=0;j--){
            // 나의 것이 내 앞에 있는 것들보다 큰데 results가 작게 되어있으면 results update
            if(lines[i].second>lines[j].second){
                if(results[i]<=results[j]){
                    results[i] = results[j]+1;
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
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