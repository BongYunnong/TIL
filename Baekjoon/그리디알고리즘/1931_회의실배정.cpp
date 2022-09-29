// https://www.acmicpc.net/problem/1931
// 최대한 많은 회의를 진행할 수 있도록 배치하는 방법

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 일단 회의가 끝나는 시간이 빠른 순으로 정렬
// 만약 회의 끝나는 시간이 같다면? 회의가 시작하는 시간이 빠른 순으로 정렬
// a.first>b.first로 하면 틀림
bool Compare(pair<int,int> a, pair<int,int> b){
    if(a.second==b.second)
        return a.first<b.first;
    return a.second<b.second;
}
int N;
vector<pair<int,int>> values;

int main(){
    cin>>N;

    for(int i=0;i<N;i++){
        int a,b;
        cin>>a>>b;
        values.push_back({a,b});
    }
    sort(values.begin(),values.end(),Compare);

    int current = -1;
    int count=0;
    for(int i=0;i<N;i++){
        // 회의 시작 시간이 현재 시간보다 더 이후라면 그 회의 시작
        // 회의를 끝내는 시간이 빠른 순으로 정렬을 했기에 이 연산을 마친 후에 최대 회의실 이용 시간을 보장할 수 있음 
        if(values[i].first >= current){
            current = values[i].second;
            count++;
        }
    }
    cout<<count;
}

/* 틀림
int N;
bool* reserved;
vector<pair<int,int>> values;

bool Compare(pair<int,int> a, pair<int,int> b){
    return a.second-a.first < b.second-b.first;
}

int main(){
    cin>>N;
    reserved = new bool[N+1];
    for(int i=0;i<N;i++){
        int a,b;
        cin>>a>>b;
        values.push_back({a,b});
        reserved[i]=false;
    }

    sort(values.begin(),values.end(),Compare);
    //for(int i=0;i<values.size();i++){
    //    cout<<values[i].first<<"_"<<values[i].second<<endl;
    //}
    int count=0;
    for(int i=0;i<N;i++){
        bool canGo=true;
        for(int j=values[i].first ; j<values[i].second; j++){
            if(reserved[j]){
                canGo=false;
                break;
            }
        }
        if(canGo){
            //cout<<"Index : "<<i<<endl;
            for(int j=values[i].first ; j<values[i].second; j++){
                reserved[j]=true;
            } 
            count++;
        }
    }
    cout<<count;
}
*/
