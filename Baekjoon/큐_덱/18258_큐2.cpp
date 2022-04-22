// https://www.acmicpc.net/problem/18258

// 큐 구현
// push X: 정수 X를 큐에 넣는 연산이다.
// pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// size: 큐에 들어있는 정수의 개수를 출력한다.
// empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
// front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
// back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.

#include<iostream>
#include<string>
using namespace std;

class Queue{
public:
    int startIndex;
    int endIndex;
    int arr[2000001];

    Queue(){
        startIndex=0;
        endIndex=0;
    }
    void Push(int _val){
        arr[endIndex]=_val;
        endIndex++;
    }
    int Pop(){
        if(startIndex < endIndex){
            int result = arr[startIndex];
            startIndex++;
            return result;
        }else{
            return  -1;
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
        if(Empty()==0)
            return arr[startIndex];
        else
            return -1;
    }

    int Back(){
        if(Empty()==0)
            return arr[endIndex-1];
        else
            return -1;
    }
};

int N;
int main(){
    // 이거 안하면 시간초과
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;
    Queue* q = new Queue();
    string input;
    for(int i=0;i<N;i++){
        cin>>input;
        if(input=="push"){
            int val;
            cin>>val;
            q->Push(val);
        }else if(input=="front"){
            cout<<q->Front()<<'\n';
        }else if(input=="back"){
            cout<<q->Back()<<'\n';
        }else if(input=="size"){
            cout<<q->Size()<<'\n';
        }else if(input=="empty"){
            cout<<q->Empty()<<'\n';
        }else if(input=="pop"){
            cout<<q->Pop()<<'\n';
        }
    }
}