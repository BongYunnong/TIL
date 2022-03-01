#include <iostream>
using namespace std;

int main(){
    int a, b;
    cin >> a>> b;

    int time;
    cin >> time;

    if(b+time < 60)
        cout << a << " "<< b+time;
    else{
        int hourAdd = (int)((b+time)/60);
        int dayAdd = (int)((a+hourAdd)/24);
        cout << (a+hourAdd)%24 << " "<< (b+time)%60;
    }
}