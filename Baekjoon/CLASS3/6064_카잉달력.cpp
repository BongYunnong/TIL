// https://www.acmicpc.net/problem/6064
// 최소공배수를 사용해야한다는 패턴은 찾았는데, 시간초과가 걸림
// 1부터 다 체크하는 것은 무리라고 함
// 간과한 패턴이 있는데, N을 계속 진행시킨 것을 M으로 나눈 나머지가 y가 되면 우리가 찾던 것이 나온다는 것..

#include<iostream>
using namespace std;

int gcd(int x,int y){
    int tmp;
    if(x<y){
        tmp = x;
        x = y;
        y = tmp;
    }
    int c;
    while(y!=0){
        c = x%y;
        x=y;
        y=c;
    }
    return x;
}
int lcm(int x, int y)
{
    return x * y / gcd(x, y);
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int M,N,x,y;
        cin>>M>>N>>x>>y;

        int prog1 =x;
        int prog2;
        int LCM = lcm(M,N);
        while(prog1<=LCM){
            prog2 = prog1%N;
            if(prog2==0)
                prog2=N;
            if(prog2==y)
                break;
            prog1+=M;
        }
        if(prog1>LCM)
            cout<<-1<<'\n';
        else
            cout<<prog1<<'\n';
    }
}

/* 시간초과..ㅠ
#include<iostream>
using namespace std;

int gcd(int x,int y){
    int c;
    while(y!=0){
        c = x%y;
        x=y;
        y=c;
    }
    return x;
}
int lcm(int x, int y)
{
    return x * y / gcd(x, y);
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int M,N,x,y;
        cin>>M>>N>>x>>y;

        int result=-1;
        int LCM = lcm(M,N);
        for(int j=1;j<=LCM/M;j++){
            int currVal = M*j+x;
            for(int k=1;k<=LCM/N;k++){
                if(currVal==k*N+y){
                    result=currVal;
                    break;
                }
            }
            if(result>=0){
                break;
            }
        }
        cout<<result<<'\n';
    }
}
*/
