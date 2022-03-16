#include<iostream>
#include<stack>

using namespace std;
stack<int> s;

int* inputs;
int* results;
int main(){
    int N;
    cin>>N;
    inputs = new int[N];
    results = new int[N];
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        inputs[i] = tmp;
    }

    for(int i=N-1;i>=0;i--){
        while(s.empty()==false){
            //cout<<"TOP : "<<s.top()<<" inputs[i] :"<<inputs[i]<<endl;
            if(s.top()>inputs[i]){
                results[i]=s.top();
                 break;
            }else{
                s.pop();
            }
        }
        if(s.empty()){
            results[i]=-1;
        }
        s.push(inputs[i]);
    }

    for(int i=0;i<N;i++){
        cout<<results[i]<<' ';
    }
}