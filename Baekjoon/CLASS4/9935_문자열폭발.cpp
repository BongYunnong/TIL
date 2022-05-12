// 뭐지? 나는 왜 틀렸지?

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    string str;
    cin>>str;
    string trigger;
    cin>>trigger;
    string result="";

    int explodeIndex = trigger.size()-1;

    for(int i=0;i<str.size();i++){
        result+= str[i];

        if(result[result.size()-1] == trigger[explodeIndex]){
            if(result.size() >= trigger.size()){
                int k=1;
                for(int j=explodeIndex-1;j>=0;j--){
                    if(result[result.size()-1-(explodeIndex-j)] != trigger[j]){
                        break;
                    }
                    k++;
                }

                if(k==trigger.size()){
                    for(int t=0;t<trigger.size();t++){
                        result.pop_back();
                    }
                }
            }
        }
    }

    if(result.size()==0){
        cout<< "FRULA";
    }else{
        cout<<result;
    }
}

/* 2퍼 틀림
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    string str;
    cin>>str;
    string trigger;
    cin>>trigger;

    vector<pair<char,int>> explodeList;

    for(int i=0;i<str.size();i++){
        if(trigger.find(str[i]) != string::npos){
            explodeList.push_back({str[i],i});

            if(str[i]==trigger[trigger.size()-1]){
                bool canExplode=true;
                int k=0;
                for(int j=trigger.size()-1;j>=0;j--){
                    if(trigger[j]!=explodeList[explodeList.size()-1-k].first){
                        canExplode=false;
                        break;
                    }
                    k++;
                }

                if(canExplode){
                    for(int t=1;t<=trigger.size();t++){
                        str[explodeList[explodeList.size()-t].second]=' ';
                    }
                    explodeList.erase(explodeList.end()-trigger.size(), explodeList.end());
                }
            }
        }
    }

    string result="";
    for(int i=0;i<str.size();i++){
        if(str[i]!=' '){
            result+=str[i];
        }
    }
    if(result.size()==0){
        result = "FRULA";
    }
    cout<<result;
}
*/