#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;

    int max = -1000;
    char inputs[81];
    for(int i=0;i<n;i++){
        cin>>inputs;
        int score=0;
        int combo=1;
        for(int j=0;j<81;j++){
            if(inputs[j]=='O'){
                score+=combo;
                combo++;
            }else{
                combo=1;
            }
            inputs[j]='_';
        }
        cout<<score<<'\n';
    }
}