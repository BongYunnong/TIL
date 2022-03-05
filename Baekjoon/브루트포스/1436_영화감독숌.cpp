#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;

    int combo=0;
    int maxCombo=0;
    int index=666;

    int resultCount=0;
    
    while(resultCount<N){
        while(true){
            int curr = index;
            combo=0;
            maxCombo=0;
            while(true){
                if(curr<10){
                    if(curr==6)
                        combo++;
                    else
                        combo=0;
                    if(maxCombo<combo)
                        maxCombo=combo;
                    break;
                }else{
                    if(curr%10==6){
                        combo++;
                    }else{
                        combo=0;
                    }
                    curr/=10;
                    if(maxCombo<combo)
                        maxCombo=combo;
                }
            }
            if(maxCombo>=3){
                resultCount++;
                index++;
                break;
            }
            index++;
        }
    }
    cout<<index-1;
}