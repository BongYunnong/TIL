#include<iostream>
using namespace std;

int arr[100001];
int results[100001];

int N;
int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }
    
    results[0] = arr[0];
    int result = results[0];
    for(int i=1;i<N;i++){
        results[i] = max(results[i-1]+arr[i],arr[i]);
        result = max(result, results[i]);
    }

    cout<<result;
}

/* 시간초과
long arr[100001];
long results[100001];
long tmpResults[100001];
long answer=-1000;

int N;
int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>arr[i];
        results[i]=-1000;
    }
    
    for(int i=1;i<=N;i++){
        for(int j=i;j<=N;j++){
            if(i==j)
                tmpResults[i] = arr[i];
            else
                tmpResults[j] =tmpResults[j-1]+arr[j];
        }
        for(int j=1;j<=N;j++){
            //cout<<tmpResults[j]<<'+';
            if(results[i]<tmpResults[j])
                results[i] = tmpResults[j];
            
        }
        //cout<<'\n';
    }

    for(int i=1;i<=N;i++){
        if(answer<results[i])
            answer = results[i];
        //cout<<"Result : "<<results[i];
    }
    cout<<answer;
}
*/


/* out of bounds
long arr[100001];
int results[100001][100001];
long answer=-1000;

int N;
int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>arr[i];
    }
    
    for(int i=1;i<=N;i++){
        for(int j=i;j<=N;j++){
            if(i==j)
                results[i][j] = arr[i];
            else
                results[i][j] =results[i][j-1]+arr[j];
            answer = max(answer, results[i][j]);
        }
    }
    cout<<answer;
}
*/