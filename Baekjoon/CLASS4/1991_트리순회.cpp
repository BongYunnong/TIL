// https://www.acmicpc.net/problem/1991
// 애초에 PreOrder, InOrder, Post Order를 재귀함수로 만드는 것을 생각하지 못하고 BFS로 뻘짓을 했다.
// 그런데 알고 나서도 class와 포인터를 다루는 것에 익숙하지 않아서인지 계속 쓰레기 값이 들어가서 힘들었다.

#include<iostream>
#include<queue>
using namespace std;

class MyNode{
public:
    MyNode(){
    }
    char myValue;
    MyNode* leftNode;
    MyNode* rightNode;
};

MyNode* myNodes;

void PreOrder(MyNode* tmpNode){
    cout<<tmpNode->myValue;
    if(tmpNode->leftNode)
        PreOrder(tmpNode->leftNode);
    if(tmpNode->rightNode)
        PreOrder(tmpNode->rightNode);
}
void InOrder(MyNode* tmpNode){
    if(tmpNode->leftNode)
        InOrder(tmpNode->leftNode);
    cout<<tmpNode->myValue;
    if(tmpNode->rightNode)
        InOrder(tmpNode->rightNode);
}
void PostOrder(MyNode* tmpNode){
    if(tmpNode->leftNode)
        PostOrder(tmpNode->leftNode);
    if(tmpNode->rightNode)
        PostOrder(tmpNode->rightNode);
    cout<<tmpNode->myValue;
}

int main(){
    int N;
    cin>>N;

    myNodes = (MyNode*)malloc(sizeof(MyNode)*N);
    for(int i=0;i<N;i++){
        char x,y,z;
        cin>>x>>y>>z;
        int num = x-'A';
        myNodes[num].myValue=x;

        if(y!='.'){
            int tmpIndex=y-'A';
            myNodes[num].leftNode= &myNodes[tmpIndex];
        }else{
            myNodes[num].leftNode=NULL;
        }
        if(z!='.'){
            int tmpIndex=z-'A';
            myNodes[num].rightNode= &myNodes[tmpIndex];
        }else{
            myNodes[num].rightNode=NULL;
        }
    }
    PreOrder(&myNodes[0]);
    cout<<'\n';
    InOrder(&myNodes[0]);
    cout<<'\n';
    PostOrder(&myNodes[0]);
}
/* 클래스 만들어서 하려했는데 실패
#include<iostream>
#include<queue>
using namespace std;

class MyNode{
public:
    MyNode(){
    }
    char myValue;
    MyNode* leftNode;
    MyNode* rightNode;
};

MyNode* myNodes[27];

void Search(MyNode* tmpNode){
    cout<<tmpNode->myValue;
    if(tmpNode->leftNode!=nullptr)
        Search(tmpNode->leftNode);
    if(tmpNode->rightNode!=nullptr)
        Search(tmpNode->rightNode);
}

int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        myNodes[i]=new MyNode();
        myNodes[i]->myValue='A'+i;
    }
    for(int i=0;i<N;i++){
        char x,y,z;
        cin>>x>>y>>z;

        if(y!='.'){
            int tmpIndex=y-'A';
            myNodes[i]->leftNode= myNodes[tmpIndex];
        }
        if(z!='.'){
            int tmpIndex=z-'A';
            myNodes[i]->rightNode= myNodes[tmpIndex];
        }
    }
    Search(myNodes[0]);
}
*/