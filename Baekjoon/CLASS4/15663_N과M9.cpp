#include<iostream>
#include<algorithm>
#include<set>
#include<vector>

using namespace std;

set<vector<int>> answer;

int input[10];
int arr[10];
int visited[10];
int N,M;

void Search(int count){
    if(count==M){
        vector<int> v;
        for(int i=0;i<M;i++){
            v.push_back(arr[i]);
        }
        answer.insert(v);
        v.clear();
    }else{
        for(int i=0;i<N;i++){
            if(!visited[i]){
                visited[i]=true;
                arr[count]=input[i];
                Search(count+1);
                visited[i]=false;
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N>>M;

    for(int i=0;i<N;i++){
        cin>>input[i];
    }

    sort(input,input+N);

    Search(0);

    set<vector<int>>::iterator iter;
    for(iter = answer.begin();iter!=answer.end();iter++){
        for(int i=0;i<iter->size();i++){
            cout<<iter->at(i)<<' ';
        }
        cout<<'\n';
    }   
}

/*
#include<iostream>
#include<algorithm>
using namespace std;

int input[10];
int visited[10];
int N,M;

int curIndex=0;
int answer[10];

void Search(int startIndex,int count){
    answer[count-1]=input[startIndex];
    if(count==M){
        for(int i=0;i<count;i++){
                cout<<answer[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=0;i<N;i++){
        if(visited[i]>0){
            visited[i]--;
            Search(i,count+1);
            visited[i]++;
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N>>M;

    for(int i=0;i<N;i++){
        cin>>input[i];
    }

    sort(input,input+N);

    for(int i=0;i<N;i++){
        visited[curIndex]++;
        if(i+1 < N  && input[i]!=input[i+1]){
            curIndex++;
        }
    }

    for(int i=0;i<N;i++){
        if(i+1<N && input[i+1]==input[i]){
        }else{
            fill(answer,answer+N,-1);
            visited[i]--;
            Search(i,1);
            visited[i]++;
        }
    }
}
*/

/*
#include<iostream>
#include<algorithm>
using namespace std;

int input[10];
bool visited[10];
int N,M;

int curIndex=0;
int answer[10];

void Search(int startIndex,int count){
    answer[count-1]=input[startIndex];
    if(count==M){
        for(int i=0;i<count;i++){
            cout<<answer[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    for(int i=0;i<N;i++){
        if(visited[i]==false){
            if(i+1<N && input[i+1]==input[i]){
            }else{
                visited[i]=true;
                Search(i,count+1);
                visited[i]=false;
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N>>M;

    for(int i=0;i<N;i++){
        cin>>input[i];
    }

    sort(input,input+N);

    for(int i=0;i<N;i++){
        if(i+1<N && input[i+1]==input[i]){
        }else{
            fill(answer,answer+N,-1);
            visited[i]=true;
            Search(i,1);
            visited[i]=false;
        }
    }
}
*/

/*

*/