// https://www.acmicpc.net/problem/1620

// 문자열이 많은 것을 보니 딱 봐도 map을 사용해야겠구나 생각이 든다.
// 하지만 map은 string이 key, int가 value이니,
// 반대로 int가 key, string이 value인 map을 따로 만들거나
//  string 배열을 만들어서 index에 따라 값에 접근하면 된다.


#include<iostream>
#include<map>
#include<string>

using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    map<string,int> myMap;
    map<int,string> intMap;
    //string intMap[100001];
    int N,A;
    cin>>N>>A;
    for(int i=1;i<=N;i++){
        string tmp;
        cin>>tmp;
        myMap.insert({tmp,i});
        //intMap[i]=tmp;
        intMap.insert({i,tmp});
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