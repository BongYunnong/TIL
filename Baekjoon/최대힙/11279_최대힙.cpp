#include<iostream>
using namespace std;

#include<queue>

int N;
priority_queue<int> pq;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    cin>>N;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;

        if(tmp==0){
            if(pq.empty()){
                cout<<0<<'\n';
            }else{
                cout<<pq.top()<<'\n';
                pq.pop();
            }
        }else{
            pq.push(tmp);
        }
    }
}

/* heap 만들기 실패
int arr[100001];
int N;
int arrCount;

void Sort(){
    for(int i=arrCount-1;i>=0;i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        int root = 0;
        int c = 1;
        do{
            c = 2*root+1;
            if(c<i-1 && arr[c] < arr[c+1]){
                c++;
            }
            if(c<i && arr[root] < arr[c]){
                temp = arr[root];
                arr[root] = arr[c];
                arr[c] = temp;
            }
            root = c;
        }while(c<i);
    }
}

void Pop(){
    if(arrCount>0){
        cout<<arr[0]<<'\n';
        arr[0] = arr[arrCount];
        arrCount--;
    }else{
        cout<<0<<'\n';
    }
    Sort();
}

int main(){
    cin>>N;
    arrCount=0;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        if(tmp==0){
            Pop();
        }else{
            arr[arrCount]=tmp;
            Sort();
            arrCount++;
        }
    }
    for(int i=1;i<N;i++){
        int c = i;
        do{
            int root = (c-1)/2;
            if(arr[root]<arr[c]){
                int temp = arr[root];
                arr[root] = arr[c];
                arr[c] = temp;
            }
            c = root;
        }while(c!=0);
    }

}
*/