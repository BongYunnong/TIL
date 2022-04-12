// https://www.acmicpc.net/problem/7568

// 덩치 등수 구하기
// 주어진 순서대로 등수를 출력해야하기에 굳이 정렬을 할 필요는 없다.
// 다른 브루트포스 문제와 마찬가지로, 어떤 사람의 등수를 알려면 모든 사람들에 대해서 자신보다 덩치가 큰 사람이 있는지 체크하고, 그만큼 등수를 내리면 된다.
// 그러면 자동으로 공동 등수가 결정이 된다.

#include<iostream>

using namespace std;
int main(){
    int N;
    cin>>N;

    int xs[51];
    int ys[51];

    int x,y;
    for(int i=0;i<N;i++){
        cin>>x>>y;

        xs[i]=x;
        ys[i]=y;
    }

    for(int i=0;i<N;i++){
        int count=0;
        for(int j=0;j<N;j++){
            if(i==j || (xs[i]<xs[j] && ys[i]<ys[j])){
                count++;
            }
        }
        cout<<count <<' ';
    }
}