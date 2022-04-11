// https://www.acmicpc.net/problem/17626

// 시간초과 걸릴 줄 알았는데 그냥 해도 됐다.
// _count가 result보다 커졌을 때 그냥 return하는 것이 꽤 크지 않았을까 싶다.

#include<iostream>
#include<math.h>
using namespace std;

int powers[225];

int result=10000000;
void SearchAnswer(int _curr,int _count){
    if(_count>=result){
        return;
    }
    //cout<<"c1 : "<<_curr<<", c2 : "<<_count<<"\n";
    for(int i= sqrt(_curr);i>=1;i--){
        if(powers[i]==_curr){
            // 값이 같다면 
            if(result>=_count)
                result = _count;
                return;
        }else if(powers[i]<_curr){
            // 최댓값을 찾으면
            SearchAnswer(_curr-powers[i] ,_count+1);
        }
    }
}


int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int n;
    cin>>n;

    for(int i=1;i<225;i++){
        powers[i] = i*i;
    }

    SearchAnswer(n,1);
    cout<<result;
}