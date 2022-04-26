// https://www.acmicpc.net/problem/5525

// N+1개의 I와 N개의 O로 이루어져있으면, I와 O가 교대로 나오는 문자열을 P_N이라 하자.
// I와 O로만 이루어진 S와 정수 N이 주어졌을 때 P_N이 몇 군데 포함되어있는가

#include<iostream>
#include<string>
using namespace std;

int N,M;
int result;
string input;
int main(){
    cin>>N>>M;
    cin>>input;

    for(int i=1;i<input.size();i++){
        int count=0;
        if(input[i-1]=='I'){
            while(input[i]=='O' && input[i+1]=='I'){
                // 다음과 그 다음이 조건을 만족하면, 뛰어넘고 count+1
                i+=2;
                count++;
                // count가 N에 도달하면, P_N에 속하는 것이므로 result+1
                if(count==N){
                    count--;
                    // 여기서 count를 뺴주는 이유는, 연결된 P_N이 또 있을 수 있으므로 앞의 IO를 제외한다고 보면 된다.
                    result++;
                }
            }
        }
    }
    cout<<result;
}