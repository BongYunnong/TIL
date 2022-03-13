//https://www.acmicpc.net/problem/1541
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
        if(inputs.find("-")!=string::npos){
            index = inputs.find("-");
        }
        if(inputs.find("+")!=string::npos){
            if(index==-1 || (index!=-1 && index> inputs.find("+"))){
                index = inputs.find("+");
            }
        }
        if(index==-1){
            stringArr.push_back(inputs);
            break;
        }
        string substring = inputs.substr(0,index);
        stringArr.push_back(substring);
        inputs.erase(0,index);
        //cout<<inputs<<endl;
        substring = inputs.substr(0,1);
        stringArr.push_back(substring);
        inputs.erase(0,1);
        //cout<<inputs<<endl;
    }

    //for(int i=0;i<stringArr.size();i++){
    //    cout<<"YES : "<<stringArr[i]<<'\n';
    //}


    int answer = stoi(stringArr[0]);
    int currState = 1;
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