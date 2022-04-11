// set 사용하기
/*
#include<iostream>
#include<set>

using namespace std;

int t,k;
char oper;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>t;
    for(int i=0;i<t;i++){
        multiset<int> s;
        cin>>k;
        for(int j=0;j<k;j++){
            cin>>oper;
            int num;
            cin>>num;
            if(oper=='I'){
                s.insert(num);
            }else{
                if(s.empty()==false){
                    if(num==1){
                        s.erase(--s.end());
                    }else{
                        s.erase(s.begin());
                    }
                }
            }
        }
            if(s.empty()){
                cout<<"EMPTY\n";
            }else{
                cout<<*(--s.end()) << " "<<*(s.begin())<<'\n';
            }
    }
}
*/

// Map사용하기
// map은 key를 오름차순 정렬
#include<iostream>
#include<queue>
#include<vector>
#include<map>
using namespace std;

int t,k;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    cin>>t;
    for(int i=0;i<t;i++){
        map<int,int> m;
        cin>>k;
        for(int j=0;j<k;j++){
            char oper;
            cin>>oper;
            int num;
            cin>>num;
            if(oper=='I'){
                m[num]++;
            }else if(oper=='D'){
                if(m.empty()==false){
                    if(num==1){
                        if(--m[m.rbegin()->first]==0){
                            m.erase(m.rbegin()->first);
                        }
                    }else{
                        if(--m[m.begin()->first]==0){
                            m.erase(m.begin()->first);
                        }
                    }
                }
            }
        }
        if(m.empty()){
            cout<<"EMPTY\n";
        }else{
            cout<<m.rbegin()->first<<" "<<m.begin()->first<<"\n";
        }
    }
}


/* 시간초과 - 구현하기
#include<iostream>
#include<algorithm>
using namespace std;

class DPQ{
public:
    DPQ(){
        start=0;
        end=0;
    }
    int arr[1000001];
    int start=0;
    int end=0;
    void Insert(int _num){
        arr[end]=_num;
        end++;
        sort(arr+start,arr+end);
    }
    void Delete(int _oper){
        if(start<end){
            if(_oper==1){
                end--;
            }else{
                start++;
            }
        }
    }
    void Print(){
        if(start<end){
            cout<<arr[end-1]<<' '<<arr[start]<<'\n';
        }else{
            cout<<"EMPTY\n";
        }
    }
};

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        DPQ* dpq = new DPQ();
        int k;
        cin>>k;
        
        for(int j=0;j<k;j++){
            char oper;
            cin>>oper;

            if(oper=='I'){
                int num;
                cin>>num;
                dpq->Insert(num);
            }else if(oper=='D'){
                int oper2;
                cin>>oper2;
                dpq->Delete(oper2);
            }
        }
        dpq->Print();
        
    }
}
*/