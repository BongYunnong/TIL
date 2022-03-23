#include<iostream>
#include<queue>
using namespace std;

// 최대 힙과 최소 힙을 만들어서
// 최대 힙에는 작은 값들, 최소 힙에는 큰 값을 넣는다.
// 그러면 최대 힙의 top에는 작은 값 중 가장 큰 값이,
// 최소 힙의 top에는 큰 값 중 가장 작은 값이 들어가게 된다.
// 그리고 만약 최대 힙의 top 값이 최소 힙의 top 값보다 커지게 되면,
// 최대 힙의 top과 최소 힙의 top을 Swap해준다.
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;
    priority_queue<int> max;
    priority_queue<int,vector<int>,greater<int>> min;

    for(int i=0;i<N;i++){
        int a, size;
        cin>>a;
        if(max.size()==min.size()){
            max.push(a);
        }else{
            min.push(a);
        }

        if(max.empty()==false && min.empty()==false && max.top() > min.top()){
            int maxVal, minVal;
            maxVal = max.top();
            minVal = min.top();
            max.pop();
            min.pop();
            max.push(minVal);
            min.push(maxVal);
        }
        cout<<max.top()<<'\n';
    }
}

/* 시간초과
priority_queue<int> pq1;
priority_queue<int> pq2;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    int N;
    cin>>N;
    
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        
        if(i%2==0){
            pq1.push(tmp);
            if(i==0){
                pq2.push(pq1.top());
                pq1.pop();
                cout<<pq2.top()<<'\n';
            }else{
                for(int j=0;j<i/2;j++){
                    pq2.push(pq1.top());
                    pq1.pop();
                }
                cout<<pq1.top()<<'\n';
                while (pq1.empty()==false)
                {
                    pq2.push(pq1.top());
                    pq1.pop();
                }
            }
        }else{
            pq2.push(tmp);

            int left;
            for(int j=0;j<=i/2;j++){
                left = pq2.top();
                pq1.push(left);
                pq2.pop();
            }
            if(pq2.top() < left){
                cout<<pq2.top()<<'\n';
            }else{
                cout<<left<<'\n';
            }

            while (pq2.empty()==false)
            {
                pq1.push(pq2.top());
                pq2.pop();
            }
        }
    }
}
*/


/* 흠..
int arr[1000001];
int arrCount=0;
void Heap_Push(int x){
    arr[++arrCount]=x;
    int child = arrCount;
    int parent = child/2;

    while(child>1 && arr[child]>arr[parent]){
        int tmp = arr[child];
        arr[child] = arr[parent];
        arr[parent] = tmp;
        child = parent;
        parent = child/2;
    }
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    int N;
    cin>>N;
    
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        Heap_Push(tmp);

        cout<<arr[arrCount/2+1]<<'\n';
    }

}
*/