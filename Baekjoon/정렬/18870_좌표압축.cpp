// https://www.acmicpc.net/problem/18870

// unordered_map 사용하는 방법
// sort 후
// unordered_map<int,int> m;
// for i=0 to num , if m.count(arr[i]==0) , m.insert({arr[i],idx++})
// map이 비어있으면 현재 counting된 index를 추가하는 방법

// 이분탐색 이용한 방법
// sort, 중복 제거 후
// cout<<lower_bound(vec.begin(), vec.end(), origin[i]) - vec.begin()<<' ';


#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

/* 1번 풀이 - set 사용
*/

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    int N;
    cin>>N;

    int tmp;
    vector<int> arr;
    for(int i=0;i<N;i++){
        cin>>tmp;
        arr.push_back(tmp);
    }

    // 중복 제거, 자동 정렬
    set<int> s(arr.begin(),arr.end());
    vector<int> v(s.begin(),s.end());

    for(int i=0;i<N;i++){
        cout<<lower_bound(v.begin(),v.end(),arr.at(i))-v.begin()<<' ';
    }
}


/* 2번풀이*/
/*
int main(){
    int N;
    cin>>N;
    vector<pair<int,int>> arr;
    int tmp;
    for(int i=0;i<N;i++){
        cin>>tmp;
        arr.push_back(make_pair(tmp,i)); 
    }

    sort(arr.begin(),arr.end());


    int* answer = new int[N];
    for(int i=0;i<N;i++){
        answer[i]=0;
    }

    int index=0;
    for(int i=0;i<N;i++){
        if(i!=0 && arr[i].first==arr[i-1].first){
            index--;
        }
        answer[arr[i].second]=index++;
    }

    for(int i=0;i<N;i++){
        cout<<answer[i]<<' ';
    }
}
*/