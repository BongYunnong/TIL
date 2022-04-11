#include<iostream>
#include<map>
#include<string>

using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    map<string,int> myMap;
    string intMap[100001];
    int N,A;
    cin>>N>>A;
    for(int i=1;i<=N;i++){
        string tmp;
        cin>>tmp;
        myMap.insert({tmp,i});
        intMap[i]=tmp;
    }


    for(int i=1;i<=A;i++){
        string tmp;
        cin>>tmp;
        if('0' <= tmp[0] && tmp[0] <='9'){
            int index = stoi(tmp);
            cout<<intMap[index]<<'\n';
        }else{
            cout<<myMap[tmp]<<'\n';
        }
    }
}