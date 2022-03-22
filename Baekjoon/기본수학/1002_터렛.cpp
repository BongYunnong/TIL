//https://www.acmicpc.net/problem/1002

// 두개의 터렛이 있는데, 각각 적의 위치까지의 거리를 계산해보았다.
// 적이 있을 수 있는 위치의 수를 출력하자.

#include<iostream>
#include<math.h>
using namespace std;
int main(){
    int T;
    cin>>T;

    int x1,y1,r1,x2,y2,r2;
    for(int i=0;i<T;i++){
        cin>>x1>>y1>>r1>>x2>>y2>>r2;

        // 두 터렛 사이의 거리를 계산
        double dist =sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));


        if(x1==x2&&y1==y2&&r1==r2){
            // 두 터렛이 완전히 겹치는 경우 거리가 똑같기에 원 자체가 적이 있을 수 있는 위치가 되어 무한대가 된다.
            cout<<-1<<'\n';
        }else if( dist==r1+r2){
            // 두 터렛이 계산한 거리의 합과 두 터렛의 거리가 같다면 한 점에서 만나는 경우이다.
            cout<<1<<'\n';
        }else if( dist==abs(r1-r2)){
            // 두 터렛이 계산한 거리의 차와 두 터렛의 거리가 같다면 한 터렛이 다른 터렛 안에 존재하고, 한 점에서 만나는 경우이다.
            cout<<1<<'\n';
        }else if(dist>r1+r2){
            // 두 터렛이 계산한 거리의 합보다 두 터렛의 거리가 멀다면 두 원은 교차하지 않는다.
            cout<<0<<'\n';
        }else if((r1>r2 && dist+r2<r1) || (r2>r1 && dist+r1<r2)){
            // 한 터렛이 다른 터렛 안에 존재하는데, 안에 있는 터렛+ 두 터렛의 거리가 큰 터렛이 계산한 거리보다 짧다면, 두 원은 교차하지 않는다.
            cout<<0<<'\n';
        }else{
            // 이 이외의 경우는 두 원이 2 점에서 교차하는 경우이다.
            cout<<2<<'\n';
        }
    }
}