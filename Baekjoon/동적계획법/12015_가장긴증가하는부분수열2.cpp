// https://www.acmicpc.net/problem/12015

// 쓸데없는거를 지워버리는 것까지는 맞았는데, 아예 처음부터 데이터를 따로 만들어버릴 생각은 못 했고
// 결정적으로 값을 바꿔치기 하는 방법을 생각하지 못했다.
// lower_bound를 쓰는 방법을 기억해둬야겠다. 이것을 쓰면 아주 간단하게 어려운 문제가 풀리는 듯 하다.

#include<iostream>
#include<vector>
using namespace std;

int N;
vector<int> DP;
int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        if(DP.size()==0 || DP.back()<tmp){
            DP.push_back(tmp);
        }else{
            auto iter =lower_bound(DP.begin(),DP.end(),tmp);
            *iter = tmp;
        }
    }
    cout<<DP.size();
}
/*
// 쓸데없는 큰 값은 지워버리는 방법인데.. .이래도 바로 시간초과 걸림
#include<iostream>
#include<vector>
using namespace std;

int N;
vector<int> A;
vector<int> DP;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;
    
    int result=0;
    
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        A.push_back(tmp);
        DP.push_back(1);
        for(int j=A.size()-1;j>=0;j--){
            if(A.back() > A[j]){
                if(DP.back() <= DP[j]+1){
                    DP.back() = DP[j]+1;

                    int currVal = A.back();
                    int currLen = DP.back();
                    // 더 커진 시점에서, 값은 큰데 len이 똑같으면 필요없음
                    for(int k=j-1;k>=0;k--){
                        if(currLen >= DP[k] && currVal <= A[k]){
                            A.erase(A.begin()+k);
                            DP.erase(DP.begin()+k);
                        }
                    }
                }
            }
        }
        result=max(result,DP.back());
    }

    for(int i=0;i<A.size();i++){
        cout<<A[i]<<' '; 
    }
    cout<<'\n';
    for(int i=0;i<DP.size();i++){
        cout<<DP[i]<<' '; 
    }
    cout<<'\n';

    cout<<result;
}
*/

/* 시간초과
#include<iostream>
using namespace std;

int N;
int A[1000001];
int DP[1000001];
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;
    
    int result=0;
    
    for(int i=0;i<N;i++){
        cin>>A[i];
        DP[i]=1;
        for(int j=0;j<i;j++){
            if(A[i]>A[j]){
                DP[i] = max(DP[i],DP[j]+1);
            }
        }
        result=max(result,DP[i]);
    }
    cout<<result;
}
*/