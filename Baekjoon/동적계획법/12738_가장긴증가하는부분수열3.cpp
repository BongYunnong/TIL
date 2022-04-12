// https://www.acmicpc.net/problem/12738
// 뭐지? 가장 긴 증가하는 부분수열 2와 코드가 똑같다.
// https://www.acmicpc.net/problem/12015
// 달라진 조건은 주어지는 Ai가 달라진다는 것인데,  (-1,000,000,000 ≤ Ai ≤ 1,000,000,000) 범위가 이렇게 변한다.
// 그런데 -라고 해도 어차피 vector 내의 큰 값이 작은 값으로 변한다는 사실은 변함이 없다.

#include<iostream>
#include<vector>
using namespace std;

int N;
vector<int> A;
int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;

        if(A.size()==0 || A.back()<tmp){
            A.push_back(tmp);
        }else{
            auto iter = lower_bound(A.begin(),A.end(),tmp);
            *iter = tmp;
        }
    }

    cout<<A.size();
}