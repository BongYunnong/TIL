// https://www.acmicpc.net/step/27

// 나동빈님의 강좌를 보고 푼 문제
// 먼저 Pattern 안의 Pattern을 찾아낸다.(중복되는 문자열을 찾아서 vector<int> table로 만들어냄)
// j를 통해 패턴이 일치하는지 반복적으로 탐색할텐데, table은 이 패턴 내부의 index를 결정하는데에 도움을 줌
// j가 0일때는 table을 쓰지 않다가, parent[i]와 pattern[j]가 달라졌을 경우(어느정도는 맞다가 다른 부분이 확인되었을 경우) j는 table[j-1]이 되어서 중복되었던 마지막 부분으로 다시 돌아간다.

#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> answer;
vector<int> MakeTable(string pattern){
    vector<int> table(pattern.size());
    int j=0;
    for(int i=1;i<pattern.size();i++){
        while(j>0 && pattern[i]!=pattern[j]){
            j = table[j-1];
        }
        if(pattern[i]==pattern[j]){
            table[i]=++j;
        }
    }
    return table;
}

void KMP(string parent, string pattern){
    vector<int> table = MakeTable(pattern);
    int j=0;
    for(int i=0;i<parent.size();i++){
        while(j>0 && parent[i]!=pattern[j]){
            j=table[j-1];
        }
        if(parent[i]==pattern[j]){
            if(j==pattern.size()-1){
                answer.push_back(i-pattern.size()+2);
                j=table[j];
            }else{
                j++;
            }
        }
    }
}

int main(){
    string T;
    string P;
    getline(cin,T);
    getline(cin, P);
    KMP(T,P);

    cout<<answer.size()<<'\n';
    for(int i=0;i<answer.size();i++){
        cout<<answer[i]<<' ';
    }
}