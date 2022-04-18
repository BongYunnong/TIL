// https://www.acmicpc.net/problem/1676

// N!에서 뒤에서부터 처음 0이 아닌 숫자가 나올 때까지 0의 개수를 구하는 프로그램
// N!이 뒤에 0자리가 나오려면, 2*5가 쌍으로 몇 개 있는지를 알아내면 된다.

// for문으로 N까지 차근차근 밟아가면서 약수로 2, 5가 몇개인지 체크한 후 둘 중 작은 개수를 구하면 된다.

#include<iostream>
using namespace std;

int main(){
    int N;
    cin>>N;
    
    int count2 = 0;
    int count5 = 0;
    for(int i=2;i<=N;i++){
        int tmp = i;
        while(tmp%2==0){
            count2++;
            tmp/=2;
        }
        while(tmp%5==0){
            count5++;
            tmp/=5;
        }
    }
    cout<<min(count2,count5);
}