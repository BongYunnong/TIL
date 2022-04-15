// https://www.acmicpc.net/problem/10814

// 가입한 사람의 나이와 이름이 주어질 때, 나이가 증가하는 순으로, 나이가 같으면 먼저 가입한 사람이 앞에 오도록 정렬

// 그냥 sort를 쓰려면 tuple을 사용해서 가입한 시간도 저장을 해야한다.
// 그러고싶지 않으면 그냥 stable_sort를 사용하면 된다.

// stable_sort -> 메모리 9732kb, 100ms
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


// sort- tuple -> 메모리 11256kb, 시간 108ms
/*
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<tuple>
using namespace std;

bool compare(tuple<int,string,int> a,tuple<int,string,int> b){
    if(get<0>(a)==get<0>(b))
        return get<2>(a)<get<2>(b);
    else
        return get<0>(a)<get<0>(b);
}

int main(){
    int N;
    cin>>N;
    
    vector<tuple<int,string,int>> vec;
    for(int i=0;i<N;i++){
        int x;
        string s;
        cin>>x>>s;
        
        vec.push_back(make_tuple(x,s,i));
    }
    sort(vec.begin(),vec.end(),compare);
    
    for(int i=0;i<N;i++){
        cout<<get<0>(vec[i])<<" "<<get<1>(vec[i])<<'\n';
    }
    
}
*/