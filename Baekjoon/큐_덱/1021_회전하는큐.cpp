// https://www.acmicpc.net/problem/1021

//이 큐에서 다음과 같은 3가지 연산을 수행할 수 있다.
//1. 첫 번째 원소를 뽑아낸다. 이 연산을 수행하면, 원래 큐의 원소가 a1, ..., ak이었던 것이 a2, ..., ak와 같이 된다.
//2. 왼쪽으로 한 칸 이동시킨다. 이 연산을 수행하면, a1, ..., ak가 a2, ..., ak, a1이 된다.
//3. 오른쪽으로 한 칸 이동시킨다. 이 연산을 수행하면, a1, ..., ak가 ak, a1, ..., ak-1이 된다.

// 큐에 처음에 포함되어 있던 수 N이 주어진다. 그리고 지민이가 뽑아내려고 하는 원소의 위치가 주어진다.
// 이때, 그 원소를 주어진 순서대로 뽑아내는데 드는 2번, 3번 연산의 최솟값을 출력하는 프로그램을 작성하시오.

// 음 좀 어려운 것 같은데, 양 옆으로 pop할 수 있는 deque를 만들고
// 원하는 값이 절반을 기준으로 왼쪽에 있는지 오른쪽에 있는지 확인한 후
// 왼쪽에 있다면 앞에서부터 빼고, 오른쪽에 있다면 오른쪽에서부터 빼면 된다.

// 이런 연산으로 인해서 오름차순이 아니게 된다 하더라도, 그냥 원하는 값의 index가 왼,오에 있는지를 판단하는 것이기에 문제 없다.

#include<iostream>
#include<deque>
using namespace std;

deque<int> dq;

int main(){
    int N;
    cin>>N;

    int M;
    cin>>M;
    for(int i=1;i<=N;i++){
        dq.push_back(i);
    }

    int count=0;
    for(int i=0;i<M;i++){
        int tmp;
        cin>>tmp;

        int index=0;
        for(int j=0;j<dq.size();j++){
            if(dq.at(j)==tmp){
                index=j;
                break;
            }
        }

        if(index <= dq.size()/2){
            while(true){
                if(dq.front()==tmp){
                    dq.pop_front();
                    break;
                }
                int val = dq.front();
                dq.pop_front();
                dq.push_back(val);
                count++;
            }
        }else{
            while(true){
                if(dq.front()==tmp){
                    dq.pop_front();
                    break;
                }
                int val = dq.back();
                dq.pop_back();
                dq.push_front(val);
                count++;
            }
        }
    }
    cout<<count;
}