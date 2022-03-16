#include<iostream>
#include<string>
using namespace std;

class Stack{
public:
    int num[10001];
    int index;

    Stack(){
        index=0;
        for(int i=0;i<10001;i++){
            num[i]=-1;
        }
    }
    void Push(int _x){
        num[index]=_x;
        index++;
    }
    void Pop(){
        if(index>0){
            cout<<num[index-1]<<'\n';
            index--;
        }
        else
            cout<<-1<<'\n';
    }
    void Size(){
        cout<<index<<'\n';
    }
    void Empty(){
        if(index>0){
            cout<< 0<<'\n';
        }else{
            cout<<1<<'\n';
        }
    }
    void Top(){
        if(index>0)
            cout<<num[index-1]<<'\n';
        else
            cout<<-1<<'\n';
    }
};


int main(){
    int N;
    cin>>N;
    Stack* stak = new Stack();
    string oper;
    int param;
    for(int i=0;i<N;i++){
        cin>>oper;
        if(oper=="push"){
            cin>>param;
            stak->Push(param);
        }else if(oper=="pop"){
            stak->Pop();
        }else if(oper=="size"){
            stak->Size();
        }else if(oper=="empty"){
            stak->Empty();
        }else if(oper=="top"){
            stak->Top();
        }else{
            cout<<"NONE";
        }
    }
}