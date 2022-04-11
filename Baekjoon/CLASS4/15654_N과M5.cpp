// https://www.acmicpc.net/problem/15654

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N,M;
bool visited[9];
vector<int> inputs;


vector<int> results;

void dfs(int start, int count){
    if(count==M){
        for(int i=0;i<results.size();i++){
            cout<<inputs[results[i]]<<' ';
        }
        cout<<'\n';
        return;
    }else if(count>M){
        return;
    }

    for(int i=0;i<N;i++){
        int index = i;
        if(index !=start && visited[index]==false){
            visited[index]=true;
            results.push_back(i);
            dfs(index,count+1);
            results.pop_back();
            visited[index]=false;
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
        dfs(i,1);
        visited[i]=false;
        results.pop_back();
    }
}