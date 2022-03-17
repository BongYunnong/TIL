#include<iostream>
#include<deque>
using namespace std;

deque<int> dq;

int main(){
    int N;
    cin>>N;

    int M;
    cin>>M;
    for(int i=1;i<=N;i++){
        dq.push_back(i);
    }

    int count=0;
    for(int i=0;i<M;i++){
        int tmp;
        cin>>tmp;

        int index=0;
        for(int j=0;j<dq.size();j++){
            if(dq.at(j)==tmp){
                index=j;
                break;
            }
        }

        if(index <= dq.size()/2){
            while(true){
                if(dq.front()==tmp){
                    dq.pop_front();
                    break;
                }
                int val = dq.front();
                dq.pop_front();
                dq.push_back(val);
                count++;
            }
        }else{
            while(true){
                if(dq.front()==tmp){
                    dq.pop_front();
                    break;
                }
                int val = dq.back();
                dq.pop_back();
                dq.push_front(val);
                count++;
            }
        }
    }
    cout<<count;
}