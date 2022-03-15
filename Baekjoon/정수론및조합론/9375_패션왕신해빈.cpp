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