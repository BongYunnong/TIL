#include<iostream>
#include<string>
using namespace std;

class Deque{
public:
    int startIndex;
    int endIndex;
    int arrs[100001];
    Deque(){
        startIndex=10000;
        endIndex=10000;
    }

    void Push_Front(int _val){
        arrs[startIndex]=_val;
        startIndex--;
    }
    void Push_Back(int _val){
        endIndex++;
        arrs[endIndex]=_val;
    }
    int Pop_Front(){
        if(startIndex>=endIndex){
            return -1;
        }else{
            int val = arrs[startIndex+1];
            startIndex++;
            return val;
        }
    }
    int Pop_Back(){
        if(startIndex>=endIndex){
            return -1;
        }else{
            int val = arrs[endIndex];
            endIndex--;
            return val;
        }
    }
    int Size(){
        return endIndex-startIndex;
    }
    int Empty(){
        if(Size()<=0){
            return 1;
        }else{
            return 0;
        }
    }
    int Front(){
        if(startIndex>=endIndex){
            return -1;
        }else{
            int val = arrs[startIndex+1];
            return val;
        }
    }
    int Back(){
        if(startIndex>=endIndex){
            return -1;
        }else{
            int val = arrs[endIndex];
            return val;
        }
    }
};

int main(){
    Deque* deque=new Deque();
    int N;
    cin>>N;
    string input;
    int val;
    for(int i=0;i<N;i++){
        cin>>input;
        if(input=="push_back"){
            cin>>val;
            deque->Push_Back(val);
        }else if(input=="push_front"){
            cin>>val;
            deque->Push_Front(val);
        }else if(input=="front"){
            cout<<deque->Front()<<'\n';
        }else if(input=="back"){
            cout<<deque->Back()<<'\n';
        }else if(input=="size"){
            cout<<deque->Size()<<'\n';
        }else if(input=="empty"){
            cout<<deque->Empty()<<'\n';
        }else if(input=="pop_front"){
            cout<<deque->Pop_Front()<<'\n';
        }else if(input=="pop_back"){
            cout<<deque->Pop_Back()<<'\n';
        }
    }
}