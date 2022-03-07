#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

bool Compare(pair<int,string> a, pair<int,string> b){
    return a.first<b.first;
}

int main(){
    int N;
    cin>>N;

    vector<pair<int,string>>  arr;

    int x;
    string str;
    for(int i=0;i<N;i++){
        cin>>x>>str;
        arr.push_back(make_pair(x,str));
    }

    //stable_sort...
    stable_sort(arr.begin(),arr.end(),Compare);

    for(int i=0;i<arr.size();i++){
        cout<<arr[i].first<<' ' <<arr[i].second<<'\n';
    }
}