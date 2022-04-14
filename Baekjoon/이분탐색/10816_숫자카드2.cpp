// https://www.acmicpc.net/problem/10816

// 이 문제가 신기한게, 그냥 무지성으로 counting배열 만들어서 다 넣어봐도 성공은 한다.
// 다만, 이분탐색이니까 좀 더 멋있게 문제를 풀어보자면
// sort()한 후에 upper bound, lower bound를 사용할 수 있다.
// 말 그대로 뒤에서부터 그 값을 찾아서 index 배출, 앞에서부터 그 값을 찾아서 index 배출한다.

// 그런데 이 STL을 모를수도 있으니, 이분탐색으로 이 함수를 만들어내면 된다.


// Upper bound, Lower Bound를 만들어냄
#include<iostream>
#include<algorithm>
using namespace std;

int A[500001];
int l_bound(int _low,int _high,int _element){
    while(_low<_high){
        int mid = (_low+_high)/2;
        if(A[mid]<_element){
            _low = mid+1;
        }else{
            _high = mid;
        }
    }
    return _low;
}
int u_bound(int _low,int _high,int _element){
    while(_low<_high){
        int mid = (_low+_high)/2;
        if(A[mid]<=_element){
            _low = mid+1;
        }else{
            _high = mid;
        }
    }
    return _high;
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
    for(int i=0;i<M;i++){
        int lower = 0;
        int upper = N;
        int tmp;
        cin>>tmp;
        // lower찾고 lower부터 upper까지 다시 upper을 찾는것 아주 멋있는 코드인 듯
        lower = l_bound(lower,upper,tmp);
        upper = u_bound(lower,upper,tmp);

        cout<<upper-lower<<' ';
    }
}

/* upper bound, lower bound라는것이 있구만
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> A;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        A.push_back(tmp);
    }
    sort(A.begin(),A.end());
    
    int M;
    cin>>M;
    for(int i=0;i<M;i++){
        int tmp;
        cin>>tmp;
        cout<<upper_bound(A.begin(),A.end(),tmp) - lower_bound(A.begin(),A.end(),tmp)<<' '; 
    }
}
*/


/* 무지성 ok
#include<iostream>
using namespace std;

int counting[20000001];
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    int N;
    cin>>N;

    for(int i=0;i<20000001;i++){
        counting[i]=0;
    }
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        counting[tmp+10000000]++;
    }
    
    int M;
    cin>>M;
    for(int i=0;i<M;i++){
        int tmp;
        cin>>tmp;
        cout<<counting[tmp+10000000]<<' ';
    }
}
*/

/* 시간초과
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<pair<int,int>> A;
int BinarySearch(int _element){
    int start = 0;
    int end = A.size();
    int mid = (start+end)/2;

    while(start<=end){
        mid = (start+end)/2;
        if(A[mid].first==_element){
            return mid;
        }else if(A[mid].first>_element){
            end = mid-1;
        }else{
            start = mid+1;
        }
    }
    return -1;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        if(i==0){
            A.push_back({tmp,1});
        }else{
            sort(A.begin(),A.end());
            int result = BinarySearch(tmp);
            if(result<0){
                A.push_back({tmp,1});
            }else{
                A[result].second++;
            }
        }
    }
    sort(A.begin(),A.end());
    //for(int i=0;i<A.size();i++){
    //    cout<<A[i].first<<","<<A[i].second<<'\n';
    //}
    
    
    int M;
    cin>>M;
    for(int i=0;i<M;i++){
        int tmp;
        cin>>tmp;
        int result = BinarySearch(tmp);
        if(result!=-1){
            cout<<A[result].second<<' ';
        }else{
            cout<<'0'<<' ';
        }
    }
}
*/