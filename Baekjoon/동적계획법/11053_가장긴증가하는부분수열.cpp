// https://www.acmicpc.net/problem/11053
// 수열 A가 주어졌을 때 가장 긴 증가하는 부분수열의 길이를 구하자.

// F(N) = 1~N-1까지의 F중, N번째 값보다 작은 숫자들이 갖는 부분수열의 길이 중, 가장 길이가 긴 부분수열의 길이에 +1한 값.

#include<iostream>
using namespace std;

int N;
int arr[1001];
int results[1001];

int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>arr[i];
    }

    int Result=0;
    for(int i=1;i<=N;i++){
        results[i]=1;
        // 현재 index보다 작은 index의 값들을 업데이트 해주자.
        for(int j=i-1;j>=1;j--){
            // 현재 index 값보다 작은 숫자의 index를 마지막으로 갖는 값은 +1을 하여 증가시킬 수 있다.
            // 하지만 현재 index값을 쓰지 않아도 더 길게 만들 수 있다면 그 큰 값을 사용하는 것이 맞다.
            if(arr[i]>arr[j]){
                results[i] = max(results[i],results[j]+1);
            }
        }
        Result = max(results[i],Result);
    }
    cout<<Result;
}


/* 틀림..
// F(N) = N번째에서 시작해서 가장 긴 증가하는 부분수열을 구했을때 그 길이.
// 답은 F(N)중 가장 큰 F(N)을 출력하면 된다.
// 만약 30 10 20 40 50 이렇게 주어진다면, 30부터 시작하면 30,40,50으로 3이지만 10부터 시작하면 10,20,40,50이 된다.

#include<iostream>
using namespace std;

int N;
int arr[1001];
int results[1001];

int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>arr[i];
    }

    int Result=0;
    for(int i=1;i<=N;i++){
        int tmpMax = arr[i];
        results[i]=1;
        for(int j=i+1;j<=N;j++){
            if(tmpMax<arr[j]){
                tmpMax = arr[j];
                results[i]++;
            }
        }
        Result = max(results[i],Result);
    }
    cout<<Result;
}
*/


/* 이론상 진짜 맞는거같은데 왜 틀린지 모르겠음
int N;
int results[1001][1001];
int arr[1001];
int main(){
    cin>>N;

    for(int i=1;i<=N;i++){
        cin>>arr[i];
    }
    
    for(int i=1;i<=N;i++){
        results[i][i]=1;
        int currMax = arr[i];
        for(int j=i+1;j<=N;j++){
            if(currMax<arr[j]){
                results[i][j] = results[i][j-1]+1;
                currMax=arr[j]; 
            }else{
                results[i][j] = results[i][j-1]; 
            }
        }
    }

    int Result=-1;
    for(int i=1;i<=N;i++){
        if(Result<=results[i][N])
            Result=results[i][N];
    }
    cout<<Result;
}
*/