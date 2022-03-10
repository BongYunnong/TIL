#include <iostream>
using namespace std;

int count0;
int count1;
int fibonacci(int n) {
    if (n == 0) {
        count0++;
        return 0;
    } else if (n == 1) {
        count1++;
        return 1;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}
int T;
int main(){
    cin>>T;
    int N;
    for(int i=0;i<T;i++){
        cin>>N;
        count0=0;
        count1=0;
        fibonacci(N);
        cout<<count0<<' '<<count1<<'\n';
    }
}

/*
pair<int,int> fiboResult[41]; 

pair<int,int> fibonacci(int n) {
    if (fiboResult[n].first == 0 && fiboResult[n].second == 0) {
        pair<int,int> n1 = fibonacci(n-1);
        pair<int,int> n2 = fibonacci(n-2);
        fiboResult[n].first = (n1.first+n2.first);
        fiboResult[n].second =  (n1.second+n2.second);
    }
    return fiboResult[n];
}

int T;

int main(){
    cin>>T;
    int N;

    for(int i=0;i<41;i++){
        fiboResult[i] = make_pair(0,0);
    }
    fiboResult[0].first=1;
    fiboResult[0].second=0;
    fiboResult[1].first=0;
    fiboResult[1].second=1;

    for(int i=0;i<T;i++){
        cin>>N;
        cout<<fibonacci(N).first<<' '<<fibonacci(N).second<<'\n';
    }
}
*/