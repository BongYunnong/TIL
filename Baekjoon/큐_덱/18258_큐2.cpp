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