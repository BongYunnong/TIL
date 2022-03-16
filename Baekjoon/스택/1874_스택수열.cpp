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