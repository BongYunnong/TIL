#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    int t;
    cin >> t;

    int a,b;
    for(int i=0;i<t;i++){
        cin >> a >> b;
        cout<<"Case #"<<i+1<<": "<<a<<" + "<<b<<" = "<<a+b<<"\n";
    }
}