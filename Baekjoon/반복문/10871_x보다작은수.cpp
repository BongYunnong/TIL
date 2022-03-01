#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    int n;
    cin >> n;
    int x;
    cin >> x;

    int element;
    for(int i=0;i<n;i++){
        cin >> element;
        if(element < x){
            cout<<element<<" ";
        }
    }
}