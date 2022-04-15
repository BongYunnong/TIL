// https://www.acmicpc.net/problem/11650

// 2차원 평면 위의 점 N개가 주어진다. 좌표를 x좌표가 증가하는 순으로, x좌표가 같으면 y좌표가 증가하는 순서로 정렬


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int>> arr;

bool Compare(pair<int,int> a, pair<int,int> b){
    if(a.first == b.first)
        return a.second<b.second;
    return a.first<b.first;
}

int main(){
    int N;
    cin>>N;

    int x;
    int y;
    for(int i=0;i<N;i++){
        cin>>x>>y;
        arr.push_back(make_pair(x,y));
    }

    sort(arr.begin(),arr.end(),Compare);
    for(int i=0;i<arr.size();i++){
        cout<<arr[i].first<< ' '<<arr[i].second<<endl;
    }
}