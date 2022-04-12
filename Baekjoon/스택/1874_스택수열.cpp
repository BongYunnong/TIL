// https://www.acmicpc.net/problem/1874

// stack이 비어있거나 top이 현재 만들려는 수열 요소보다 작으면 push를 한다.(못 만들 가능성도 있기에, index가 N을 넘어가면 break한다.)
// 만약 수열 요소와 맞으면 pop을 한다.

#include<iostream>
#include<stack>
#include<vector>

using namespace std;
int main(){
    int N;
    cin>>N;
    stack<int> s;

    vector<char> results;
    int index=2;
    s.push(1);
    results.push_back('+');
    bool yes=true;
    for(int i=0;i<N;i++){
        int tmp;
        cin>> tmp;
        while(true){
            if(s.empty()){
                s.push(index);
                results.push_back('+');
                index++;
            }else{
                if(s.top() != tmp && index<=N){
                    s.push(index);
                    results.push_back('+');
                    index++;
                }else{
                    break;
                }
            }
        }

        if(s.empty()==false){
            if(s.top() != tmp && index>N){
                yes=false;
                break;
            }else{
                results.push_back('-');
                s.pop();
            }
        }
    }

    if(yes){
        for(int i=0;i<results.size();i++){
            cout<<results[i]<<'\n';
        }
    }else{
        cout<<"NO\n";
    }
}