// https://www.acmicpc.net/problem/14889
// N명의 사람을 둘로 나누어서 팀을 정하는데, 능력치 차이가 최소가 되도록 만든다.
// input은 시너지이다.

#include<iostream>
using namespace std;

int N;
int score[20][20];

bool* currTeam1;

int result=10000000;

// startIndex없으면 시간초과
void dfs(int startIndex,int count){
    //cout<<"[dfs]:"<<index<<'_'<<(N/2 -1)<<'\n';
    if(count==N/2){
        // 반절만큼 팀을 꾸렸을 때, 결과 계산
        int mean1=0;
        int mean2=0;
        //cout<<"Team1";
        //for(int i=0;i<N;i++){
        //    cout<<"_"<<currTeam1[i];
        //}
        //cout<<'\n';

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                // i와 j가 둘 다 team1이라면
                if(currTeam1[i] && currTeam1[j])
                    mean1 += score[i][j];
                // i와 j가 둘 다 team1이 아니라면(team2라면)
                else if(currTeam1[i]==false && currTeam1[j]==false)
                    mean2 += score[i][j];
            }
        }
        
        int tmpResult = mean1-mean2;
        //cout<<"result : "<<mean1<<"_"<<mean2<<'\n';
        if(tmpResult<0){
            tmpResult*=-1;
        }
        if(result>=tmpResult)
            result = tmpResult;
        return;
    }

    for(int i=startIndex;i<N;i++){
        if(currTeam1[i]==false){
            currTeam1[i] = true;
            // 무작정 하나씩 team1에 넣어보기
            dfs(i+1,count+1);
            currTeam1[i]=false;
        }
    }

}

int main(){
    cin>>N;
    currTeam1 = new bool[N];
    for(int i=0;i<N;i++){
        currTeam1[i]=0;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>score[i][j];
        }
    }
    dfs(0);
    cout<<result;
}