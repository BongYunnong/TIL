#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
int inputs[10001];
stack<int> s;


void Search(int _start,int _end){
    if(_start>=_end){
        return ;
    }
    //cout<<_start<<" : "<<inputs[_start]<<'\n';
    s.push(inputs[_start]);
    int index= upper_bound(inputs+(_start+1),inputs+_end,inputs[_start])-inputs;
    if(index>=0){
        Search(index,_end);
        Search(_start+1,index);
    }else{
        Search(_start+1,_end);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    
    int i=0;
    while(cin.eof()==false){
        cin>>inputs[i];
        i++;
    }

    Search(0,i-1);

    while(s.empty()==false){
        cout<<s.top()<<'\n';
        s.pop();
    }

    return 0;
}