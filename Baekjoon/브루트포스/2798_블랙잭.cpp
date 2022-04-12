// https://www.acmicpc.net/problem/2798

// 마찬가지로, 처음부터 다 해보면 된다.
// 다행히도 블랙잭이고, 3장의 카드만 고르면 되기에, for문을 3번 돌려서 모든 경우의 수를 다 체크해주면 된다.



#include<iostream>
using namespace std;
int main(){
    int N,M;
    cin>>N>>M;

    int cards[101]={-1};
    for(int i=0;i<N;i++){
        cin>>cards[i];
    }

    int max = -1;
    for(int i=0;i<N-2;i++){ // 첫 번째로 집을 것
        for(int j=i+1;j<N-1;j++){   // 두 번째로 집을 것
            for(int k=j+1;k<N;k++){ // 세 번째로 집을 것
                if(cards[i]+cards[j]+cards[k]<=M && max <= cards[i]+cards[j]+cards[k]){
                    max = cards[i]+cards[j]+cards[k];
                }
            }
        }
    }
    cout<<max;
}
