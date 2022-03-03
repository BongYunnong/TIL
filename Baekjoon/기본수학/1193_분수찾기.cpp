#include <iostream>
using namespace std;

int main(){
    long n;
    cin>>n;

    long count =1;
    long plus=0;

    long result = 0;
    while(true){
        if(count<= n && n< count+plus+1){
            break;
        }else{
            plus+=1;
            count+=plus;
            result++;
        }
    }

    int dist = n-count;
    if(result%2!=0)
        cout<<(dist+1)<<'/'<< (result+1)-(dist);
    else
        cout<<(result+1)-(dist)<<'/'<< (dist+1);
}

/*
1/1                     1        1
1/2 2/1                 3        2
1/3 2/2 3/1             6        3
1/4 2/3 3/2 4/1         10       4
1/5 2/4 3/3 4/2 5/1     15       5
...
1
2~3
4~6
7~10
11~15


1/n 2/n-1 3/n-2 4/n-3 .... n/1

*/