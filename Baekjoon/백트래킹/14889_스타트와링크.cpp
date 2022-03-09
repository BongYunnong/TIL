#include<iostream>
using namespace std;

int N;
int score[20][20];

bool* currTeam1;

int result=10000000;

// startIndex없으면 시간초과
void dfs(int startIndex,int index){
    //cout<<"[dfs]:"<<index<<'_'<<(N/2 -1)<<'\n';
    if(index==N/2){
        int mean1=0;
        int mean2=0;
        //cout<<"Team1";
        //for(int i=0;i<N;i++){
        //    cout<<"_"<<currTeam1[i];
        //}
        //cout<<'\n';

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(currTeam1[i] && currTeam1[j])
                    mean1 += score[i][j];
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
            dfs(i+1,index+1);
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
    dfs(0,0);
    cout<<result;
}