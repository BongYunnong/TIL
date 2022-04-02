#include<iostream>
#include<string>
using namespace std;

class SClass{
public:
    bool arr[21];
    void add(int _x){
        arr[_x]=true;
    }
    void remove(int _x){
        arr[_x]=false;
    }
    void check(int _x){
        if(arr[_x]){
            cout<<1<<'\n';
        }else{
            cout<<0<<'\n';
        }
    }
    void toggle(int _x){
        arr[_x] = !arr[_x];
    }
    void all(){
        for(int i=0;i<21;i++){
            arr[i]=true;
        }
    }
    void empty(){
        for(int i=0;i<21;i++){
            arr[i]=false;
        }
    }
};

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    SClass* s = new SClass();

    int M;
    cin>>M;
    for(int i=0;i<M;i++){
        string oper;
        cin>>oper;
        if(oper=="add"){
            int num;
            cin>>num; 
            s->add(num);
        }else if(oper=="remove"){
            int num;
            cin>>num; 
            s->remove(num);
        }else if(oper=="check"){
            int num;
            cin>>num; 
            s->check(num);
        }else if(oper=="toggle"){
            int num;
            cin>>num; 
            s->toggle(num);
        }else if(oper=="all"){
            s->all();
        }else if(oper=="empty"){
            s->empty();
        }
    }
}