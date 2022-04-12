// https://www.acmicpc.net/problem/15654
// 자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성
// N개의 자연수는 모두 다른 수
// N개의 자연수 중에서 M개를 고른 수열
// 수열은 사전 순으로 증가하는 순서로 출력

// 지금까지는 1부터 N까지의 자연수였지만, 지금은 정렬되지 않은 무작위 숫자를 사용해야함

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N,M;
bool visited[9];
vector<int> inputs;
vector<int> results;

void dfs(int count){
    if(count>=M){
        for(int i=0;i<results.size();i++){
            cout<<inputs[results[i]]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=0;i<N;i++){
        if(visited[i]==false){
            visited[i]=true;
            results.push_back(i);
            dfs(count+1);
            results.pop_back();
            visited[i]=false;
        }
    }
}

int main(){

    cin>>N>>M;

    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        inputs.push_back(tmp);
    }
    
    fill(visited,visited+9,false);

    sort(inputs.begin(),inputs.end());

    for(int i=0;i<N;i++){
        visited[i]=true;
        results.push_back(i);
        dfs(1);
        visited[i]=false;
        results.pop_back();
    }
}