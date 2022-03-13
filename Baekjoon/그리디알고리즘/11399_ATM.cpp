// https://www.acmicpc.net/problem/11399
#include <iostream>
#include <algorithm>
using namespace std;

int N;
int* times;
int main(){
    cin>>N;
    times = new int[N+1];
    for(int i=0;i<N;i++){
        cin>>times[i];
    }
    sort(times,times+N);

    int answer=times[0];
    for(int i=1;i<N;i++){
        times[i] = times[i-1]+times[i];
        answer+=times[i];
    }
    cout<<answer;
}