// https://www.acmicpc.net/problem/1629
// 자연수 A를 B번 곱한 수
// 이를 C로 나눈 나머지

// 지수법칙과 모듈러 성질은 꼭 숙지해야만 한다.

// #지수법칙
// a^(n+m) = a^n * a^m;
// 모듈러 성질
// (a*b)%c = (a%c*b%c)%c


#include<iostream>
#include<vector>
using namespace std;


int A,B,C;

long long Pow(long long x, long long m){
    if(m==0){ // 0승이니까 1
        return 1;
    }else if(m==1){ // 1승이니까 x
        return x;
    }
    if(m%2 >0){ // m이 홀수라면 지수 하나를 빼서 다음 m을 짝수로 만듦
        return Pow(x,m-1)*x;
    }
    // 짝수일 때
    long long half = pow(x,m/2);
    half%=C;
    return (half*half)%C;   // 모둘려성질
}
int main(){
    cin>>A>>B>>C;
    cout<<Pow(A,B)%C;    
}

/* 이거는 약간 이해가 어려움
#include<iostream>
#include<vector>
using namespace std;


int A,B,C;

long long Remain(long long x){
    if(x==0) // 이거 처리 안하면 틀림
        return 0;
    if(x==1)    // 지수가 1 남는다면 A%C임
        return A%C;
    long long y = Remain(x/2)%C;    // 지수를 둘로 쪼개기 (A^n)%C과 같음
    if(x%2==0)  // 짝수라면 그대로 계산
        return (y*y)%C;
    else    // 홀수라면 한번 더 계산
        return (y* (y*A))%C;
}
int main(){
    cin>>A>>B>>C;
    cout<<Remain(B);    
    // remain(B)는 A^B % C임
    // B= n+m일때 지수법칙에 의해서, remain(B) = (A^n * A^m)%C
    // 모듈러 성질에 의해서, remain(B) = ((A^n)%C * (A^m)%C)%C
}
*/

/* 시간초과 되었다가 틀림
vector<pair<int,int>> remains;//index,value

long A;
long B;
long C;
int main(){
    cin>>A>>B>>C;

    int Result=1;
    int startIndex=0;
    int dist=0;

    if(B==0){
        cout<<1;
        return 0;
    }

    for(int i=0;i<B;i++){
        Result*=A;
        Result = Result%C;

        int founded=-1;
        for(int j=0;j<remains.size();j++){
            if(Result==remains[j].second){
                founded=j;
                break;
            }
        }
        if(founded>=0){
            startIndex = remains[founded].first;
            dist = i-startIndex;
            break;
        }else{
            remains.push_back({i,Result});
        }
    }
    //for(int i=0;i<remains.size();i++){
    //    cout<<'('<<remains[i].first<<","<<remains[i].second<<')'<<endl;
    //}
    //cout<<"Start : "<<startIndex<<endl;
    //cout<<"B-startIndex : "<<(B-1)-startIndex<<endl;
    //cout<<"dist : "<<dist<<endl;


    if(dist==0){
       cout<<remains[startIndex+(((B-1)-startIndex))].second;
    }else{
        //cout<<"distCalc : "<<(((B-1)-startIndex)%dist)<<endl;
        //cout<<"index : "<<startIndex+(((B-1)-startIndex)%dist)<<endl;
       cout<<remains[startIndex+(((B-1)-startIndex)%dist)].second;
    }
}
*/