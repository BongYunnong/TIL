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
                results[i][j] = max(results[i-1][j],results[i][j-1]);
            }
        }
    }
    cout<<results[arr.length()][arr2.length()];
}