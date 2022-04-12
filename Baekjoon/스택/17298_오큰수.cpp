// https://www.acmicpc.net/problem/17298

// 오큰수 NGE(i)
// 오큰수는 오른쪽에 있으면서 Ai보다 큰 수 중에서 가장 왼쪽에 있는 수를 의미한다. 그러한 수가 없는 경우에 오큰수는 -1이다.

// 처음에는 쉽겠다 생각했는데, N의 크기가 1000000인 것을 보고 아, 시간초과 걸리겠구나 생각했다.
// 이것을 해결하는 방법은 뒤에서부터 하는 것이다. 맨 마지막 수는 당연하게도 -1이 된다.
// 앞으로 차근차근 results[i]를 채워나가면 되는데, results[i]는 그때까지의 값들 중에서 가장 큰 수이다.
// i까지 가는 동안 N에서 N-i까지 stack에 값을 채워두고, 만약 stack의 top이 그 값보다 크다면 result[i]에 넣고, 만약 stack의 top이 그 값보다 작다면 계속 pop을 하게 된다.
// 그 후에 i번째 요소를 stack에 push한다.
// 그 이유는, 오른쪽에 있는 수 중에서 '가장 가까운' 나보다 큰 수이기 때문이다.

#include<iostream>
#include<stack>

using namespace std;
stack<int> s;

int* inputs;
int* results;
int main(){
    int N;
    cin>>N;
    inputs = new int[N];
    results = new int[N];
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        inputs[i] = tmp;
    }

    for(int i=N-1;i>=0;i--){
        while(s.empty()==false){
            // cout<<"TOP : "<<s.top()<<" inputs[i] :"<<inputs[i]<<endl;
            if(s.top()>inputs[i]){
                results[i]=s.top();
                 break;
            }else{
                s.pop();
            }
        }
        if(s.empty()){
            results[i]=-1;
        }
        s.push(inputs[i]);
    }

    for(int i=0;i<N;i++){
        cout<<results[i]<<' ';
    }
}