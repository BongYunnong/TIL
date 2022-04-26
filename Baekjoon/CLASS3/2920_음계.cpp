// https://www.acmicpc.net/problem/2920

// index로 combo를 이어나가자

#include<iostream>
using namespace std;

int main(){
    int combo=0;

    int num;
    cin>>num;
    int last=num;

    for(int i=1;i<8;i++){
        cin>>num;

        if(num>last){
            combo++;
        }else if(num < last){
            combo--;
        }

        last=num;
    }
    
    if(combo>=7){
        cout<<"ascending";
    }else if(combo<=-7){
        cout<<"descending";
    }else{
        cout<<"mixed";
    }

}