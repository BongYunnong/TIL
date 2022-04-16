#include<iostream>
#include<queue>
using namespace std;

int inOrder[100001];
int postOrder[100001];
queue<int> preOrder;

int counts=0;
    int n;

void SearchAnswer(int _start, int _end,int _postStart, int _postEnd){
    if(_start > _end || _postStart>_postEnd){
        return;
    }

    int finding = postOrder[_postEnd];
    int bound=-1;
    for(int i=0;i <=n;i++){
        if(inOrder[i]== finding){
            bound=i;
            break;
        }
    }
    preOrder.push(finding);

    SearchAnswer(_start, bound-1, _postStart,_postStart+(bound-_start)-1);
    SearchAnswer(bound+1, _end, _postStart+(bound-_start),_postEnd-1);
}


int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>inOrder[i];
    }
    for(int i=0;i<n;i++){
        cin>>postOrder[i];
    }

    SearchAnswer(0,n-1,0,n-1);

    for(int i=0;i<n;i++){
        cout<< preOrder.front()<<' ';
        preOrder.pop();
    }
}

/* 분할하는 패턴을 찾은 것 까지는 좋았는데...왜 그 다음을 못하니..ㅠ
#include<iostream>
#include<queue>
using namespace std;

int inOrder[100001];
int postOrder[100001];
queue<int> preOrder;

int counts=0;
    int n;

void SearchAnswer(int _start, int _end){
    counts++;
    if(counts>100){
        return;
    }
    cout<<_start<<","<<_end<<'\n';
    cout<<"PUSH "<<postOrder[_end]<<'\n';
    preOrder.push(postOrder[_end]);

    if(_start>=_end){
        return;
    }

    int bound = -1;
    
    for(int i=0;i<n;i++){
        cout<<inOrder[i]<<" ";
    }
    cout<<"\n finding"<<postOrder[_end]<<"\n";

    for(int i=0;i <=n;i++){
        if(inOrder[i]== postOrder[_end]){
            bound=i;
            break;
        }
    }
    cout<<"bound "<<bound<<'\n';
    
    if(_start<=(bound-_start)-1){
        SearchAnswer(_start,bound-2);
    }
    if(bound<=_end-1){
        SearchAnswer(bound+1,_end-1);
    }
}


int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>inOrder[i];
    }
    for(int i=0;i<n;i++){
        cin>>postOrder[i];
    }

    SearchAnswer(0,n-1);

    for(int i=0;i<n;i++){
        cout<< preOrder.front()<<' ';
        preOrder.pop();
    }
}
*/