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
                    error=true;
                    break;
                }else{
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