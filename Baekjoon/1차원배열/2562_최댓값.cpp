#include <iostream>
using namespace std;
int main(){
    long max = -1000000;

    long tmp;
    int index;
    for(int i=0;i<9;i++){
        cin>>tmp;
        if(tmp>max){
            max = tmp;
            index = i+1;
        }
    }
    cout << max << '\n' << index;
}