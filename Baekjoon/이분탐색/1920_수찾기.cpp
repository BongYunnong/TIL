// https://www.acmicpc.net/problem/1920

// 두 수열이 주어질 때 한 수열의 요소가 다른 수열의 요소에 포함되어있는지 확인
// binary search를 위해서는 먼저 sort를 해야한다.

// 원래는 무지성으로 찾고, map도 활용해보고 했는데, 시간초과, 메모리 초과가 됨

#include<iostream>
#include<algorithm>
using namespace std;
int A[100001];

    bool BinarySearch(int start, int end, int element){
        if(start>end){
            return false;
        }

        int mid = (start+end)/2;
        if(A[mid] == element){
            return true;
        }else if(A[mid] > element){
            return BinarySearch(start, mid-1,element);
        }else{
            return BinarySearch(mid+1,end,element);
        }
    }

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>A[i];
    }
    sort(A,A+N);

    int M;
    cin>>M;
    int B[M];
    for(int i=0;i<M;i++){
        cin>>B[i];
        if(BinarySearch(0,N-1,B[i])==true){
            cout<<1<<'\n';
        }else{
            cout<<0<<'\n';
        }
    }
}

/*
// 시간초과3 - using sort + binary -> syncwithsdio 필요
#include<iostream>
using namespace std;
#include<algorithm>
int A[100001];

bool BinarySearch(int start,int end, int element){
    //cout<<start<<','<<end<<'_'<<element<<"___"<<A[(start+end)/2]<<'\n';
    if(A[start]==element || A[(start+end)/2]==element || A[end-1]==element )
        return true;
    else if(start==end || start==end-1){
        return false;
    }

    if(A[(start+end)/2]>element){
        return BinarySearch(start,(start+end)/2,element);
    }else{
        return BinarySearch((start+end)/2,end,element);
    }
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>A[i];
    }
    sort(A,A+N);

    int M;
    cin>>M;
    int B[M];
    for(int i=0;i<M;i++){
        cin>>B[i];
        bool result = BinarySearch(0,N,B[i]);
        if(result==true){
            cout<<1<<'\n';
        }else{
            cout<<0<<'\n';
        }
    }
}
*/

/*
// 시간초과2 - using map -> syncwithstdio해도 틀림
#include<iostream>
using namespace std;
#include<map>

int main(){
    int N;
    cin>>N;
    map<int,int> A;
    map<int,int>::iterator p;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        A.insert(pair<int,int>(tmp,tmp));
    }

    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    int M;
    cin>>M;
    int B[N];
    for(int i=0;i<M;i++){
        cin>>B[i];
        p = A.find(B[i]);
        if(p!=A.end())
            cout<<1<<'\n';
        else
            cout<<0<<'\n';
    }

}
*/


/*
// 시간초과1 - 무지성 -> sync with stdio해도 시간초과
#include<iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    int N;
    cin>>N;
    int A[N];
    for(int i=0;i<N;i++){
        cin>>A[i];
    }

    int M;
    cin>>M;
    int B[N];
    for(int i=0;i<M;i++){
        cin>>B[i];
        bool founded=false;
        for(int j=0;j<N;j++){
            if(A[j]==B[i]){
                founded=true;
                break;
            }
        }
        if(founded)
            cout<<1<<'\n';
        else
            cout<<0<<'\n';
    }

}
*/