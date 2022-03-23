//https://www.acmicpc.net/problem/11054
// 11053_가장긴증가하는부분수열을 푼 다음에는 쉽게 풀 수 있다.
// 가장 긴 증가하는 부분수열과 가장 긴 감소하는 부분수열을 각각 구한다.
// 두 F(N)+G(N)을 해서 가장 큰 값 -1(N 원소가 겹칠테니)을 하면 된다.

#include<iostream>
using namespace std;

int N;
int inputs[1001];
int results[1001];
int reverse_results[1001];
int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>inputs[i];
    }
    for(int i=1;i<=N;i++){
        results[i]=1;
        for(int j=1;j<=i;j++){
            if(inputs[j] < inputs[i] && results[i]<results[j]+1){
                results[i] = results[j]+1;
            }
        }
    }
    for(int i=N;i>=1;i--){
        reverse_results[i]=1;
        for(int j=N;j>=i;j--){
            if(inputs[i] > inputs[j] && reverse_results[j]+1>reverse_results[i]){
                reverse_results[i] = reverse_results[j]+1;
            }
        }
    }
    int result=0;
    for(int i=0;i<=N;i++){
        if(result < results[i]+reverse_results[i] - 1)
            result = results[i]+reverse_results[i] - 1;
    }
    cout<<result;
}

/* 틀림..
int N;

int inputs[1001];

int RealRealResult=0;
int RealResults[1001]={0,};
int results[1001][1001];

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>inputs[i];
    }

    for(int i=0;i<N;i++){
        int key = inputs[i];

        int currMax=inputs[i];
        for(int j=0;j<N;j++){
            results[j][j]=1;

            currMax=inputs[j];
            int count = 0;
            for(int k=j+1;k<i;k++){
                if(currMax<inputs[k] && inputs[k]<key){
                    currMax =inputs[k];
                    results[j][k] = results[j][k-1]+1;
                }else{
                    results[j][k] = results[j][k-1];
                }

                if(count<results[j][k]){
                    count = results[j][k];
                }
            }

            currMax=inputs[i];
            results[j][i]=1;
            int count2 = 0;
            for(int k=i+1;k<N;k++){
                if(currMax>inputs[k]){
                    currMax =inputs[k];
                    results[j][k] = results[j][k-1]+1;
                }else{
                    results[j][k] = results[j][k-1];
                }

                if(count2<results[j][k]){
                    count2 = results[j][k];
                }
            }
            RealResults[j] = count+count2+1;
        }

        for(int j=0;j<N;j++){
            if(RealRealResult<=RealResults[j]){
                RealRealResult = RealResults[j];
            }
        }
    }
    cout<<RealRealResult;
}
*/