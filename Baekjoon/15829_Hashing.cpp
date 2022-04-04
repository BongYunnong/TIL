// https://www.acmicpc.net/problem/15829

// 나머지 공식을 잘 알아둬야겠다.
// (a*b)%c의 결과 == (a%c) * (b%c)

#include<iostream>
#include<string>
using namespace std;


int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    long long size;
    cin>>size;
    string L;
    cin>>L;

    long long result=0;
    for(long long i=0;i<size;i++){
        long long power=1;
        for(int j=0;j<i;j++){
            power*=31;
            if(power>1234567891){
                power = power%1234567891;
            }

        }
        //cout<<(L[i]-'a'+1)<<"_"<<power<<"="<<((L[i]-'a'+1)*power)<<'\n';
        result += (L[i]-'a'+1)* power;
        if(result>1234567891){
            result = result%1234567891;
        }
    }
    cout<<result;
}

/* 50점짜리
#include<iostream>
#include<string>
using namespace std;


int main(){
    int size;
    cin>>size;
    string L;
    cin>>L;

    long long result=0;
    for(int i=0;i<L.size();i++){
        long long power=1;
        for(int j=0;j<i;j++){
            power*=31;
        }
        //cout<<(L[i]-'a'+1)<<"_"<<power<<"="<<((L[i]-'a'+1)*power)<<'\n';
        result += (L[i]-'a'+1)* power;
    }
    cout<<result%1234567891;

}
*/