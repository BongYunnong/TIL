// https://www.acmicpc.net/problem/1316
// 그룹단어 : 존재하는 모든 문자에 대해서 각 문자가 연속해서 나타나는 경우
// ccazzzzbb는 c,a,z,b가 모두 연속하고 kin도 k,i,n이 연속하므로 그룹단어이다.
// 그러나 aabbccb는 b 하나가 떨어져있기에 그룹 단어가 아니다.

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
            // 처음 나타난 문자이거나 pointing된 문자가 아닐 경우
            if((point==-1 || point==(int)s[j]-97)==false){
                // 이미 counting되어있다면 그룹단어가 아님
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