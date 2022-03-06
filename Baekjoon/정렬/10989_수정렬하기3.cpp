#include<iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int N;
    cin>>N;

    int* sorted = new int[10001];    
    for(int i=0;i<10001;i++){
        sorted[i]=0;
    }
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        sorted[tmp]++;
    }
    // 숫자를 세고, 그 수에 따라 반복 출력.
    for(int i=1;i<=10000;i++){
        while(sorted[i]>0){
            cout<<i<<'\n';
            sorted[i]--;
        }
    }
}