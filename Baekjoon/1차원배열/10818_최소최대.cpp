#include <iostream>
using namespace std;
int main(){
    long n;
    cin >> n;

    long min=1000000;
    long max = -1000000;

    long tmp;
    for(int i=0;i<n;i++){
        cin>>tmp;
        if(tmp<min){
            min = tmp;
        }
        if(tmp>max){
            max = tmp;
        }
    }
    cout << min << " " <<max;
}