// https://www.acmicpc.net/problem/15650
// 자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성
// 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
// 고른 수열은 오름차순이어야 한다.


#include<iostream>
using namespace std;

bool visited[10];
int arr[10];
int N,M;
void FindNext(int index,int currNum){
    if(index==M){
        for(int i=0;i<M;i++)
            cout<<arr[i]<<' ';
        cout<<'\n';
        return;
    }
    
    // 인자로 받은 이전 값보다 큰 값들에 대해서만 체크
    for(int i=currNum;i<=N;i++){
        if(visited[i]==false){
            visited[i]=true;
            arr[index]=i;
            // 지금 문자열에 넣은 값+1을 인자로 넣어줌
            FindNext(index+1,i+1);
            visited[i]=false;
        }
    }
}

int main(){

    cin>>N>>M;
    FindNext(0,1);
}