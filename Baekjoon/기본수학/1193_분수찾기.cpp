// https://www.acmicpc.net/problem/1193
// 1/1->1/2->2/1->3/1->2/2 이렇게 지그재그로 나열된 분수 중 X번째 분수를 구하라

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

#include <iostream>
using namespace std;

int main(){
    long n;
    cin>>n;

    long count =1;
    long plus=0;

    long result = 0;
    while(true){
        // n이 범위 내에 존재할 경우 탈출
        if(count<= n && n<= count+plus){
            break;
        }else{
            // 더해주는 값은 1씩 더 증가한다.
            plus+=1;
            count+=plus;
            result++;
        }
    }

    // 이건 그냥 종이에 써보면 규칙을 알기 더 쉽다.
    // result 값이 (해당 범위의 최댓값-1) 이므로 (그 구하고자하는 위치 n- 해당범위의 최댓값의 실제 값)를 dist로 두고 result와 dist를 분모,분자로 활용하면 된다.
    int dist = n-count;
    if(result%2!=0)
        cout<<(dist+1)<<'/'<< (result+1)-(dist);
    else
        cout<<(result+1)-(dist)<<'/'<< (dist+1);
}
