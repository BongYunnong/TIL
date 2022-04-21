#include<iostream>
#include<algorithm>
using namespace std;

int N,M;
int arr[10];
int num[10];
void Seq(int x, int count){
    if(count==M){
        for(int i=0;i<M;i++){
            cout<<arr[i]<<' ';
        }
        cout<<'\n';
        return;
    }

    int last=0;
    for(int i=x;i<N;i++){
        if(num[i] != last){
            arr[count]=num[i];
            last = arr[count];
            Seq(i,count+1);
        }
    }
    return;
}

int main(){
    cin>>N>>M;
    for(int i=0;i<N;i++){
        cin>>num[i];
    }
    sort(num,num+N);
    Seq(0,0);
}
/* 맞긴했지만 더 간단한 방법이 있지 않을까..?
#include <iostream>
#include <set>
#include <vector>
using namespace std;

set<int> s;
set<vector<int>> answer;
int N,M;
int inputs[10];
int results[10];
int counting=0;

void SearchNM(int num,int count){
    results[count]=num;
    if(count==M){
        vector<int> v;
        for(int i=0;i<count;i++){
            v.push_back(results[i]);
        }
        answer.insert(v);
    }else if(count<M){
        for(int i=0;i<counting;i++){
            if(inputs[i]>=num){
                SearchNM(inputs[i],count+1);
            }
        }
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N>>M;

    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        s.insert(tmp);
    }
    for(auto tmp :s){
        inputs[counting]=tmp;
        counting++;
    }
    for(int i=0;i<counting;i++){
        SearchNM(inputs[i],0);
    }
    
    for(auto a : answer){
        for(int j=0;j<a.size();j++){
            cout<<a[j]<<' ';
        }
        cout<<'\n';
    }
}

*/