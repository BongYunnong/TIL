// https://www.acmicpc.net/problem/9251
// LCS(Longest Common Subsequence, 최장 공통 부분 수열) : 두 수열이 주어졌을 때 모두의 부분 수열이 되는 수열 중 가장 긴 것을 찾는 문제
// ex. ACAYKP와 CAPCAK의 LCS는 ACAK

// arr, arr2 전부 순차적으로 돌기 위해서 2차원 배열이 필요함
// results[i][j]는 arr을 i까지, arr2를 j까지 사용했을 때 LCS임
// F(i,j) = max(F(i-1,j),F(i,j-1)) or F(i-1,j-1)+1
// answer는 F를 arr의 끝, arr2의 끝까지 계산한 값.

#include<iostream>
#include<string>
using namespace std;

string arr;
string arr2;
int results[1001][1001];

int main(){
    cin>>arr;
    cin>>arr2;
    
    for(int i=1;i<=arr.length();i++){
        for(int j=1;j<=arr2.length();j++){
            if(arr[i-1]==arr2[j-1]){
                results[i][j] = results[i-1][j-1] + 1;
            }else{
                // 만약 string의 index가 가리키는 값이 다를 경우
                // 그냥 그 값을 사용하지 않았을 때의 최댓값을 사용하면 된다.
                results[i][j] = max(results[i-1][j],results[i][j-1]);
            }
        }
    }
    cout<<results[arr.length()][arr2.length()];
}


/* 실패!!!  -> 생각해보니 arr -> arr2만 생각하고 arr2 -> arr을 생각 안함

// 꼭 연속할 필요도 없기에 그냥 많이 사용하면 많이 사용할수록 더 큰 값이 나오지 적은 값이 나오지는 않음
// F(N) = A의 N번째 요소를 사용했을 때 최대 LCS길이
// 1(A),2(AC),3(ACA),3(ACA),4(ACAK),4(ACAK)
// F(N) = (마지막 index에서부터 B를 순차적으로 돌았을 때 A[N]이 있다면)? F(N-1)+1 : F(N-1) 

#include<iostream>
#include<string>
using namespace std;

string arr;
string arr2;
int results[1001];

int main(){
    cin>>arr;
    cin>>arr2;

    int arr2Index=0;    
    for(int i=0;i<arr.length();i++){
        bool founded=false;
        for(int j=arr2Index;j<arr2.length();j++){
            if(arr[i]==arr2[j]){
                arr2Index=j;
                founded=true;
                break;
            }
        }
        if(i==0)
            results[i] = founded? 1 : 0;
        else
            results[i] = founded? results[i-1]+1 : results[i-1];
    }
    cout<<results[arr.length()-1];
}
*/
