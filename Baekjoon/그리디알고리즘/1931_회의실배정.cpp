// https://www.acmicpc.net/problem/1931
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


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
