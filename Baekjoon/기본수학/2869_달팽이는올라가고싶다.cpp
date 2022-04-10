// https://www.acmicpc.net/problem/2869
// 높이가 V미터인 나무 막대를 올라가는 달팽이
// 낮에는 A미터 올라가고 밤에 잠을 자는 동안 B미터 미끄러진다.
// 정상에 올라가면 미끄러지지 않는다.
// 나무 막대를 모두 올라가려면 며칠이 걸릴까

#include<iostream>
using namespace std;
int main(){
    int A,B,V;
    cin>>A>>B>>V;

    // 하루에 결국 얼마만큼 올라갈 수 있는가?
    int dist = A-B;

    // 마지막에 A만큼 올라가면 밤에 내려오는 것을 생각하지 않아도 된다.
    // 왜 A를 딱 자르느냐 하면 어차피 dist로 나눌 때 Calculated를 넘어가지 않는 최대 값으로 계산되기 떄문에 
    // calculatedV % dist가 0이 아니라면 calculatedV/dist보다 한 밤을 더 계산해내야한다.
    // 결국, 완벽하게 딱 올라가는 것과, 완벽하지 않아서 한 번 쉬었다가 올라가는 경우 2개의 경우밖에 없다.
    int calculatedV = V-A;
    if(calculatedV%dist==0){
        cout<<calculatedV/dist+1;
    }else{
        cout<<calculatedV/dist+2;
    }
}