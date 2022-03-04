#include<iostream>
#include<math.h>
using namespace std;
int main(){
    int T;
    cin>>T;

    int x1,y1,r1,x2,y2,r2;
    for(int i=0;i<T;i++){
        cin>>x1>>y1>>r1>>x2>>y2>>r2;

        double dist =sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        if(x1==x2&&y1==y2&&r1==r2){
            cout<<-1<<'\n';
        }else if( dist==r1+r2){
            cout<<1<<'\n';
        }else if( dist==abs(r1-r2)){
            cout<<1<<'\n';
        }else if(dist>r1+r2){
            cout<<0<<'\n';
        }else if((r1>r2 && dist+r2<r1) || (r2>r1 && dist+r1<r2)){
            cout<<0<<'\n';
        }else{
            cout<<2<<'\n';
        }
    }
}