// https://www.acmicpc.net/problem/14002
// 아.. 미친...
// 가장 긴 부분수열 너무 어렵다.
// 또 까먹어서 11053번을 봤는데도 틀렸다.
// 어쨋든 핵심은, 어떤 배열에 해당 index보다 앞에 있는 값들 중 index 요소의 값보다 작은 값이 몇 개 있는지를  체크해나가는 것이다.
// 그냥 체크하면 안되고, 그 요소 값보다 작은 값 중에서 최대 길이에 +1 하는 형태이다.

// 이 문제의 차이점은, 길이 뿐만 아니라 수열을 출력해야한다는 점이다. 이것은 dp에 저장된 length를 뒤에서부터 찾아나가는 방법으로 해결한다.

#include<iostream>
#include<vector>
using namespace std;

int A[1001];
int len;
int dp[1001];
vector<int> results;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int maxVal=0;
    int maxIndex=-1;
    int N;
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>A[i];
        len=0;
        for(int j=1;j<i;j++){
            if(A[j]<A[i]){
                len = max(dp[j],len);
            }
        }
        dp[i]=len+1;

        if(maxVal<len+1){
            maxVal=len+1;
            maxIndex=i;
        }
    }

    /*
    for(int i=1;i<=N;i++){
        cout<<dp[i]<<' ';
    }
    cout<<'\n';
    */

   // 이 부분이 섹시한 부분
   // maxIndex를 받아왔으면, 이제 그 이전값들은 maxIndex보다 작은 값이 된다.
   // 여기서 maxIndex에서 1씩 감소하면서 백트래킹을 하는 것이다.
    for(int i=maxIndex;i>=1;i--){
        if(dp[i]==maxVal){
            results.push_back(A[i]);
            maxVal--;
        }
    }
    
    int size = results.size();
    cout<<size<<'\n';
    for(int j=0;j<size;j++){
        cout<<results.back()<<' ';
        results.pop_back();
    }
}


/* 반례 -> 앞에 이미 size가 3개라서, 3부터는 size가 작다고 판단하고 안 하나봄
7
2 100 200 3 4 5 6
4
3 4 5 6
*/
/*
#include<iostream>
#include<vector>
using namespace std;

int A[1001];
vector<int> results[1001];
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>A[i];
        results[i].push_back(A[i]);
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<i;j++){
            if(A[j]<A[i] && results[j].back() <A[i] && results[i].size() < results[j].size()+1){
                results[j].push_back(A[i]);
            }
        }
    }
    
    int max=0;
    int maxIndex=-1;
    for(int i=0;i<N;i++){
        if(results[i].size() > max){
            max = results[i].size();
            maxIndex=i;
        }
    }

    cout<<results[maxIndex].size()<<'\n';
    for(int j=0;j<results[maxIndex].size();j++){
        cout<<results[maxIndex].at(j)<<' ';
    }
}
*/