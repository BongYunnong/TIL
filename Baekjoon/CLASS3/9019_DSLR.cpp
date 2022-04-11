#include<iostream>
#include<queue>
#include<string>
using namespace std;

bool visited[10000];
int answers[10000][4];
int a,b;
char functions[4]={'D','S','L','R'};

int OperD(int N){
    return (N*2%10000);
}
int OperS(int N){
    if(N==0){
        return 9999;
    }else{
        return N-1;
    }
}
int OperL(int N){
    int x = N/1000;
    return (N%1000)*10+x;
}
int OperR(int N){
    int x = N%10;
    return x*1000+N/10;
}

void Answer(int start){
    
    queue<pair<string,int>> q;

    q.push({"",start});
    for(int i = 0 ; i < 10000 ; i++)
    {
        visited[i]=false;
    }
    visited[start]=true;
    while (q.empty()==false)
    {
        string currOper = q.front().first;
        int currNumber =   q.front().second;
        //cout<<currOper<<","<<currNumber<<'\n';
        if(currNumber==b){
            break;
        }
        q.pop();
        for(int i=0;i<4;i++){
            int k=answers[currNumber][i];
            if(visited[k])
                continue;
            visited[k]=true;
            q.push({currOper+functions[i],k});
        }
    }
    cout<<q.front().first<<'\n';
}



int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int T;
    cin>>T;

    for(int i = 0 ; i < 10000 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            int currNumber;
            switch (functions[j])
            {
            case 'L':
                currNumber = OperL(i);
                break;
            case 'R':
                currNumber = OperR(i);
                break;
            case 'D':
                currNumber = OperD(i);
                break;
            case 'S':
                currNumber = OperS(i);
                break;
            default:
                break;
            }
            answers[i][j] = currNumber;
        }
    }


    for(int i=0;i<T;i++){
        cin>>a>>b;
        Answer(a);
    }
}

/* 메모리초과..ㅠ
#include<iostream>
#include<queue>
#include<tuple>
#include<string>
using namespace std;

int a,b;

int OperD(int N){
    return (N*2%10000);
}
int OperS(int N){
    if(N==0){
        return 9999;
    }else{
        return N-1;
    }
}
int OperL(int N){
    int x = N/1000;
    return (N%1000)*10+x;
}
int OperR(int N){
    int x = N%10;
    return x*1000+N/10;
}

void Answer(int start, int count){
    queue<tuple<string,int,int>> q;

    q.push(make_tuple("",start,0));

    while (q.empty()==false)
    {
        string currOper =  get<0>(q.front());
        int currNumber =  get<1>(q.front());
        int currCount =  get<2>(q.front());
        q.pop();

        switch (currOper.back())
        {
        case 'L':
            currNumber = OperL(currNumber);
            break;
        case 'R':
            currNumber = OperR(currNumber);
            break;
        case 'D':
            currNumber = OperD(currNumber);
            break;
        case 'S':
            currNumber = OperS(currNumber);
            break;
        default:
            break;
        }
        //cout<<currOper<<","<<currNumber<<','<<currCount<<'\n';

        if(currNumber==b){
            cout<<currOper;
            cout<<'\n';
            break;
        }
        string originOper=currOper;
        q.push(make_tuple(originOper.append("L"),currNumber,currCount+1));
        originOper=currOper;
        q.push(make_tuple(originOper.append("R"),currNumber,currCount+1));
        originOper=currOper;
        q.push(make_tuple(originOper.append("D"),currNumber,currCount+1));
        originOper=currOper;
        q.push(make_tuple(originOper.append("S"),currNumber,currCount+1));
    }
}



int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int T;
    cin>>T;

    for(int i=0;i<T;i++){
        cin>>a>>b;
        Answer(a,0);
    }
}
*/