//https://www.acmicpc.net/problem/1541
// 괄호를 적절히 쳐서 식의 값을 최소로 만드는 문제

// 
#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string> stringArr;
string inputs;

int main(){
    cin>>inputs;
    
    while(true){
        int index=-1;
        if(
            inputs.find("-")!=string::npos){
            index = inputs.find("-");
        }

        // +를 찾았는데, 그 이전에 -가 없거나, 있더라도 지금 찾은 +보다 뒤에 있다면 -로 못 바꾸니 추출
        if(inputs.find("+")!=string::npos){
            if(index==-1 || (index!=-1 && index> inputs.find("+"))){
                index = inputs.find("+");
            }
        }

        // -와 + 모두 못 찾으면 마지막 숫자 값이니 stringArr에 Add하고 탈출
        if(index==-1){
            stringArr.push_back(inputs);
            break;
        }

        // 숫자 추출해내기
        string substring = inputs.substr(0,index);
        stringArr.push_back(substring);
        inputs.erase(0,index);
        //cout<<inputs<<endl;
        // 연산자 추출해내기
        substring = inputs.substr(0,1);
        stringArr.push_back(substring);
        inputs.erase(0,1);
        //cout<<inputs<<endl;
    }

    //for(int i=0;i<stringArr.size();i++){
    //    cout<<"YES : "<<stringArr[i]<<'\n';
    //}


    // 일단 첫 번째 숫자 저장
    int answer = stoi(stringArr[0]);
    int currState = 1;

    // arr에 저장된 연산자, 숫자들을 계산
    // 만약 -를 찾으면 그 이후의 값들은 괄호를 사용해서 어떻게든 -로 만들어낼 수 있다.
    for(int i=1;i<stringArr.size();i+=2){
        //cout<<"index : "<<i<<"/"<<stringArr.size()<<' ';
        if(stringArr[i]=="-"){
            currState=-1;
            answer += stoi(stringArr[i+1])*currState;
        }else if(stringArr[i] =="+"){
            answer += stoi(stringArr[i+1])*currState;
        }
        //cout<<stoi(stringArr[i+1])<<"_"<<answer<<endl;
    }
    cout<<answer;
}