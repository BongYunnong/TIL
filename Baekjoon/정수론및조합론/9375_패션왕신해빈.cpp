// https://www.acmicpc.net/problem/9375

// 개 쉬운 문제인데 문제를 잘못 이해해서 시간이 좀 지체되었다.
// 똑같은 옷을 안 입는다고하고, 똑같은 조합의 옷은 안 입는다고 하니, 그냥 모든 경우의 수를 다 구해주고, 아무것도 안 입는 1개만 빼주면 된다.
// 주의할 점은, 모든 수를 구할 때 안 입는 것까지 포함해서 1 더한 후 곱해야 한다는 것이다.

#include<iostream>
#include<vector>
#include<string>
using namespace std;

#include<map>

int main(){
    int T,N;
    cin>>T;
    for(int i=0;i<T;i++){
        string _tmpCloth;
        string _tmpType;
        map<string,int> m;
        cin>>N;
        for(int j=0;j<N;j++){
            cin>>_tmpCloth>>_tmpType;
            // find를 해서 없으면 map의 end를 반환함
            if(m.find(_tmpType) == m.end()){
                m.insert({_tmpType,1});
            }else{
                m[_tmpType]++;
            }
        }
        int result=1;
        for(auto i:m){
            result*=(i.second+1);
        }
        result-=1;
        cout<<result<<'\n';
    }
}

// 이론상 맞는거같은데 틀림
/*
vector<pair<string,int>> clothes;

int T,N;
int main(){
    cin>>T;
    for(int i=0;i<T;i++){
        cin>>N;
        if(N<1){
            cout<<0<<'\n';
            break;
        }else{
            clothes.clear();
            for(int j=0;j<N;j++){
                string _tmpCloth;
                string _tmpType;
                cin>>_tmpCloth>>_tmpType;
                if(clothes.size()<1){
                    //cout<<"Push : "<<_tmpType<<endl;
                    clothes.push_back({_tmpType,1});
                }else{
                    bool founded=false;
                    for(int k=0;k<clothes.size();k++){
                        if(clothes[k].first==_tmpType){
                            clothes[k].second++;
                            founded=true;
                            break;
                        }
                    }
                    if(founded==false){
                        //cout<<"Push : "<<_tmpType<<endl;
                        clothes.push_back({_tmpType,1});
                    }
                }
            }
            int result =1;
            for(int j=0;j<clothes.size();j++){
                result*=(clothes[j].second+1);
            }
            cout<<result-1<<endl;
        }
    }
}
*/