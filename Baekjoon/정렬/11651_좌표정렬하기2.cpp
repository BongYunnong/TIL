// https://www.acmicpc.net/problem/11651

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool Compare(pair<int,int> a, pair<int,int> b){
    if(a.second==b.second)
        return a.first<b.first;
    else
        return a.second<b.second;
}

int main(){
    int N;
    cin>>N;

    vector<pair<int,int>> arr;
    int x,y;
    for(int i=0;i<N;i++){
        cin>>x>>y;
        arr.push_back(make_pair(x,y));
    }

    sort(arr.begin(),arr.end(),Compare);

    for(int i=0;i<arr.size();i++){
        cout<<arr[i].first<<' '<<arr[i].second<<'\n';
    }
}