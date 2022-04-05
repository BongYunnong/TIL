#include<iostream>
using namespace std;

long long inputs[100001];
long long sums[100001];

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    
    int N;
    cin>>N;

    int M;
    cin>>M;

    for(int i=0;i<N;i++){
        cin>>inputs[i];
        if(i>=1)
            sums[i]=sums[i-1]+inputs[i];
        else
            sums[i]=inputs[i];
    }
    for(int i=0;i<M;i++){
        int x,y;
        cin>>x>>y;  // x-1부터 y-1까지... y는 항상 1보다 크거나 같음-> 항상 안착 x는 2부터는 괜찮지만 1이라면 문제가 됨
        if(y==x){
            cout<<inputs[x-1]<<'\n';
        }else{
            cout<<(sums[y-1]-sums[x-2])<<'\n';
        }
    }
}