#include<iostream>
#include<string>
using namespace std;

int N,M;
int result;
string input;
int main(){
    cin>>N>>M;
    cin>>input;

    for(int i=1;i<input.size();i++){
        int count=0;
        if(input[i-1]=='I'){
            while(input[i]=='O' && input[i+1]=='I'){
                i+=2;
                count++;
                if(count==N){
                    count--;
                    result++;
                }
            }
        }
    }
    cout<<result;
}