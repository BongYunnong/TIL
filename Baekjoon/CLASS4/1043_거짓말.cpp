#include<iostream>
#include<vector>
using namespace std;

int parents[51];
vector<int> detective;
vector<int> party[51];

int FindParent(int x){
    if(x==parents[x]) return x;
    else return parents[x] = FindParent(parents[x]);
}
void UnionParent(int x,int y){
    x = FindParent(x);
    y = FindParent(y);
    parents[y]=x;
}
bool SameParent(int x,int y){
    x = FindParent(x);
    y = FindParent(y);
    if(x==y) return true;
    else return false;
}

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);
    
    int N,M;
    cin>>N>>M;
    int tc;
    cin>>tc;
    for(int i=0;i<tc;i++){
        int tmp;
        cin>>tmp;
        detective.push_back(tmp);
    }

    for(int i=0;i<M;i++){
        int c;
        cin>>c;
        for(int j=0;j<c;j++){
            int tmp;
            cin>>tmp;
            party[i].push_back(tmp);
        }
    }
    int ans=M;
    for(int i=1;i<=N;i++){
        parents[i]=i;
    }
    for(int i=0;i<M;i++){
        // 파티에서 만난 사람들 다 parent union
        int x = party[i][0];
        for(int j=1;j<party[i].size();j++){
            int y = party[i][j];
            UnionParent(x,y);
        }
    }

    for(int i=0;i<M;i++){
        bool canGo=true;
        for(int j=0;j<party[i].size();j++){
            if(canGo==false)break;
            int x = party[i][j];
            for(int k=0;k<detective.size();k++){
                int y = detective[k];
                if(SameParent(x,y)==true){
                    // 일반인 x와 탐정 y가 만났었거나, 앞으로 만날 수 있으면? 그 파티는 못 감
                    canGo=false;
                    break;
                }
            }
        }
        if(canGo==false)
            ans--;
    }
    cout<<ans;
}