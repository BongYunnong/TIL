//https://www.acmicpc.net/problem/2981
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> answer;

int gcd(int a,int b){
    int n;
    while(b!=0){
        n = a%b;
        a=b;
        b=n;
    }
    return a;
}


int N;
int* Ms;
int main(){
    cin>>N;
    Ms = new int[N+1];
    for(int i=0;i<N;i++){
        cin>>Ms[i];
    }
    sort(Ms,Ms+N);
    
    int tmp =Ms[1]-Ms[0];
    for(int i=2;i<N;i++){
        tmp = gcd(tmp, Ms[i]-Ms[i-1]);
    }
    
    for(int i=1;i*i<=tmp;i++){
        if(tmp%i==0){
            answer.push_back(i);
            // 중복을 막은 대칭 값 넣기
            if(i!=tmp/i){
                answer.push_back(tmp/i);
            }
        }
    }

    sort(answer.begin(),answer.end());
    for(int i=0;i<answer.size();i++){
        if(answer[i]!=1)
            cout<<answer[i]<<' ';
    }
}

/* 시간초과
int N;
int* Ms;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>N;
    Ms = new int[N+1];
    for(int i=0;i<N;i++){
        cin>>Ms[i];
    }

    for(int i=2;i<Ms[0];i++){
        //cout<<"I : "<<i<<endl;
        int val = Ms[0]%i;
        bool founded=true;
        for(int j=0;j<N;j++){
            if(val != Ms[j]%i){
                founded=false;
            }
        }
        if(founded){
            cout<<i<<' ';
        }
    }
}
*/