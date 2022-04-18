//https://www.acmicpc.net/problem/2981

// 숫자 N개를 종이에 적는다. 그 다음, 종이에 적은 수를 M으로 나누었을 때, 나머지가 모두 같게 되는 M을 모두 찾자

// 약수를 사용해야한다는 것은 알았지만 각 수를 뺀 후에 최대공약수를 구하고,
// 그 최대공약수와 다음번 구한 최대공약수의 최대공약수를 구하는 것은 생각지 못했다.

// A = a * x + y
// B = b * x + y
// 여기까지 생각하고, A-B = (a-b) * x만 생각했는데,
// C = c* x +y가 있으면 B-C = (b-c) * x 이고,
// 여기서 x가 무엇인지 모르니, 둘의 최대공약수를 잡아내면 되는 것이다.

// 거기에서 그치는 것이 아니라, 모든 가능한 M을 구해야하는데,
// x가 최대 공약수이므로 그 이상의 값은 될 수 없다. 그러면서도 나머지가 같아야한다는 것은
// x를 어떤 수로 나누었을 때 나머지가 0이어야 된다는 것을 의미한다.

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
    
    // 여기서 i*i인 이유는 안쪽을 보면 대칭값을 넣어주므로 연산을 줄이기 위함으로 보임
    // 그냥 약수를 찾는 것임
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