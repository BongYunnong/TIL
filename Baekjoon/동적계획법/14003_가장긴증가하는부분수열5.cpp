// https://www.acmicpc.net/problem/14003

// 정말 슬픔을 이루 말할 수 없다.
// pair로 first,second를 두어서 결정된 값을 출력하는 방법은, 막판에 치고들어온 값을 처리하지 못해서 틀리게 되었다.

// 인터넷으로 검색한 방법은 이렇다.
// A에 push를 할 때, A에 저장되는 index값을 같이 저장한다.
// 만약 작은 값이 나와서 바꿔치기를 할 때에도, 바꿔치기 하는 값의 index에 그 바꿔치기한 위치를 저장한다.
// 그 후에 A의 끝 위치에서부터 index가 같은 값을 asnwer에 push하는데,
// 9
// -81 -35 22 -45 27 -27 54 -35 -8
// 이 예시의 경우, -35, -8이 막판에 치고들어오지만 먼저 찾는 값은 A의 size()인 4이므로 54를 먼저 찾고, 그 후에 순차적으로 27,22,-35,-81을 찾게 된다.
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N;
int Arr[1000001];
int indexArr[1000001];
vector<int> A;
int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>Arr[i];
    }
    for(int i=0;i<N;i++){
        if(A.size()==0 || A.back()<Arr[i]){
            A.push_back(Arr[i]);
            indexArr[i]=A.size()-1;
        }else{
            auto iter = lower_bound(A.begin(),A.end(),Arr[i]);
            *iter=Arr[i];
            indexArr[i]= distance(A.begin(),iter);
        }
    }
    
    /*
    for(int i=0;i<N ;i++){
        cout<<indexArr[i]<<' ';
    }
    cout<<'\n';
    */
    cout<<A.size()<<'\n';
    vector<int> answer;
    int foundedIndex=A.size()-1;
    for(int i=N-1;i>=0 ;i--){
        if(indexArr[i]==foundedIndex){
            foundedIndex--;
            answer.push_back(Arr[i]);
        }
    }
    for(int i=answer.size()-1;i>=0;i--){
        cout<<answer[i]<<' ';
    }
}

/* 반례를 결국 못 해결합
#include<iostream>
#include<vector>
using namespace std;

int N;
vector<pair<int,int>> A;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        if(A.size()==0){
            pair<int,int> a={tmp,tmp};
            A.push_back(a);
        }else if(A.back().first < tmp){
            pair<int,int> a={tmp,tmp};
            A.back().second = A.back().first;
            A.push_back(a);
        }else{
            int index=-1;
            for(int j=0;j<A.size();j++){
                if(A[j].first >= tmp){
                    A[j].first=tmp;
                    if(i==N-1 && j==A.size()-1){
                        A[j].second=tmp;
                    }
                    break;
                }else{
                    A[j].second=A[j].first;
                }
            }
        }
    }

    
    cout<<A.size()<<'\n';
    for(int i=0;i<A.size();i++){
        cout<<'('<<A[i].first<<","<<A[i].second<<')';
    }
    
    cout<<A.size()<<'\n';
    for(int i=0;i<A.size();i++){
        cout<<A[i].second<<' ';
    }
}
*/