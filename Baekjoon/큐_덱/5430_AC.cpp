// https://www.acmicpc.net/problem/5430

// 함수 R은 배열에 있는 수의 순서를 뒤집는 함수이고,
// D는 첫 번째 수를 버리는 함수이다.
// 배열이 비어있는데 D를 사용한 경우에는 에러가 발생한다.

// 뒤집는다는 것은 앞에서부터 빼던 것을 뒤에서부터 빼겠다는 의미이다.



#include<iostream>
#include<string>
#include<deque>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        string functions,arr;
        int N;
        deque<int> dq;

        cin>>functions;
        cin>>N;
        cin>>arr;

        /* 문자열 시간초과
        arr = arr.substr(1,arr.size());
        arr = arr.substr(0,arr.size()-1);

        int val;
        while(arr.find(',')!=string::npos){
            int pos = arr.find(',');
            val = stoi(arr.substr(0,pos));
            arr = arr.substr(pos+1,arr.size());
            dq.push_back(val);
        }
        if(arr.size()>0)
            dq.push_back(stoi(arr));
        */
        string s = "";
        for (int i = 0; i<arr.length();i++) {
            if (isdigit(arr[i])) {
                s += arr[i];
            }
            else {
                if (!s.empty()) {
                    dq.push_back(stoi(s));
                    s = "";
                }
            }
        }
        
        bool error=false;
        bool reverse=false;
        for(int j=0;j<functions.size();j++){
            if(functions[j]=='R'){
                reverse = !reverse;
            }else if(functions[j]=='D'){
                if(dq.empty()){
                    // deque가 empty인데 delete하라하면 error
                    error=true;
                    break;
                }else{
                    // reverse라면 뒤에서부터, 아니면 앞에서부터 pop
                    if(reverse)
                        dq.pop_back();
                    else
                        dq.pop_front();
                }
            }
        }
        if(error){
            cout<<"error"<<endl;
        }else{
            cout<<'[';
            int size = dq.size();
            if(reverse==false){
                for(int k=0;k<size;k++){
                    cout<<dq.front();
                    if(k+1<size){
                        cout<<',';
                    }
                    dq.pop_front();
                }
            }else{
                for(int k=0;k<size;k++){
                    cout<<dq.back();
                    if(k+1<size){
                        cout<<',';
                    }
                    dq.pop_back();
                }
            }
            cout<<"]\n";
        }
    }
}