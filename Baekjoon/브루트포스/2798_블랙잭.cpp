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
    for(int i=0;i<N-2;i++){
        for(int j=i+1;j<N-1;j++){
            for(int k=j+1;k<N;k++){
                if(cards[i]+cards[j]+cards[k]<=M && max <= cards[i]+cards[j]+cards[k]){
                    max = cards[i]+cards[j]+cards[k];
                }
            }
        }
    }
    cout<<max;
}
