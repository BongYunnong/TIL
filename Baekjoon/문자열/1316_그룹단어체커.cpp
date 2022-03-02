#include <iostream>
#include <string>
using namespace std;
int main(){
    int N;
    cin>>N;

    string s;
    int counting[30]={0,};
    int point = -1;
    int result=0;

    for(int i=0;i<N;i++){
        cin>>s;
        bool yes=true;
        point= -1;
        for(int i=0;i<30;i++){
            counting[i] = 0;
        }

        for(int j=0;j<s.length();j++){
            if((point==-1 || point==(int)s[j]-97)==false){
                if(counting[(int)s[j]-97]>0){
                    yes=false;
                    break;
                }
            }
            counting[(int)s[j]-97]++;
            point = (int)s[j]-97;
        }

        if(yes)
            result++;
    }
    cout<<result;
}