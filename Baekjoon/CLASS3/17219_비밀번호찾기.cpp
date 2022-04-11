// https://www.acmicpc.net/problem/17219
// 그냥 map을 쓰면 된다.

#include<iostream>
#include<string>
#include<map>
using namespace std;

int N,M;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);


    cin>>N>>M;
    map<string,string> book;
    for(int i=0;i<N;i++){
        string address;
        string password;
        cin>>address>>password;
        book.insert({address,password});
    }

    for(int i=0;i<M;i++){
        string input;
        cin>>input;
        cout<<book[input]<<'\n';
    }
}