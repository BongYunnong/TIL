#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int>> arr;

bool Compare(pair<int,int> a, pair<int,int> b){
    if(a.first>b.first){
        return false;
    }else if(a.first<b.first){
        return true;
    }else{
        if(a.second>=b.second){
            return false;
        }else{
            return true;
        }
    }
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