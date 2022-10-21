#include<iostream>
#include<map>

using namespace std;

int inputDict[50]={0,};
int dict[50]={0,};
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int num = -1;
    cin>>num;

    int ans=0;
    string input = "";
    cin>>input;
    for(int i=0;i<input.size();i++){
        inputDict[input[i]-'A']++;
    }

    for(int i=1;i<num;i++){
        string tmp = "";
        cin>>tmp;
        fill(dict,dict+50,0);
        for(int j=0;j<tmp.size();j++){
            dict[tmp[j]-'A']++;
        }

        int diffCount=0;
        for(int i=0;i<50;i++){
            if(dict[i]!=inputDict[i])
                diffCount+= abs(inputDict[i]-dict[i]);
            if(dict[i]>0 && inputDict[i]==0){
                diffCount=-1;
                break;
            }
        }

        if(diffCount==-1)
            continue;

        if(diffCount<2)
            ans++;
    }
    cout<<ans;
}