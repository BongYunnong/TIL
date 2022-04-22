// https://www.acmicpc.net/problem/10866

// dque 구현
// push_front X: 정수 X를 덱의 앞에 넣는다.
// push_back X: 정수 X를 덱의 뒤에 넣는다.
// pop_front: 덱의 가장 앞에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// pop_back: 덱의 가장 뒤에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// size: 덱에 들어있는 정수의 개수를 출력한다.
// empty: 덱이 비어있으면 1을, 아니면 0을 출력한다.
// front: 덱의 가장 앞에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// back: 덱의 가장 뒤에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.

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