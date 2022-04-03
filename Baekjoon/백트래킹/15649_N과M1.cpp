// https://www.acmicpc.net/problem/15649
// 자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성
// 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
#include<iostream>
using namespace std;

int arr[10];
bool lock[10];
int N,M;
void FindNext(int index){
    if(index==M){
        // 길이가 M까지 도달하면 결과 출력
        for(int i=0;i<M;i++){
            cout<<arr[i]<<" ";
        }
        cout<<'\n';
        return;
    }
    for(int i=1;i<=N;i++){
        if(lock[i]==false){
            lock[i]=true;
            arr[index]=i;
            // 문자열의 index 위치에 i를 넣어보고
            FindNext(index+1);
            // 나중에 다시 참조될 것을 위해서 lock 풀기
            lock[i]=false;
        }
    }
}

int main(){
    cin>>N>>M;
    FindNext(0);
}