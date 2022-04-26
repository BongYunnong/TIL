// https://www.acmicpc.net/problem/1764

// map을 활용해서 듣도 못한 사람을 체크해서 값+1, 보도 못한 사람을 체크해서 값+1을 하면 듣도보도못한사람은 2가 된다.

// 맞음 -> 더 짧음
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
map<string,int> myMap;
vector<string> results;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N,M;
    cin>>N>>M;

    for(int i=0;i<N+M;i++){
        string input;
        cin>>input;
        myMap[input]++;
        if(myMap[input]>=2){
            results.push_back(input);
        }
    }

    sort(results.begin(),results.end());

    cout<<results.size()<<'\n';
    for(int i=0;i<results.size();i++){
        cout<<results[i]<<'\n';
    }
}

/*
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
map<string,int> myMap;
vector<string> results;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N,M;
    cin>>N>>M;

    int xCount=0;
    int yCount=0;
    for(int i=0;i<N+M;i++){
        string input;
        cin>>input;
        if(yCount>=M || (xCount<N && i%2==0)){
            if(myMap.find(input)!=myMap.end()){
                myMap[input]++;
            }else{
                myMap.insert({input,1});
            }
            xCount++;
        }else if(xCount>=N ||  (yCount<M && i%2==1)){
            if(myMap.find(input)!=myMap.end()){
                myMap[input]++;
            }else{
                myMap.insert({input,1});
            }
            yCount++;
        }
    }

    auto iter = myMap.begin();
    while(iter != myMap.end()){
        if(iter->second>=2){
            results.push_back(iter->first);
        }
        ++iter;
    }

    sort(results.begin(),results.end());

    cout<<results.size()<<'\n';
    for(int i=0;i<results.size();i++){
        cout<<results[i]<<'\n';
    }
}

*/