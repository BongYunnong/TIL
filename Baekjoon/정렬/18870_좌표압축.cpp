#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

/* 1번 풀이
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    int N;
    cin>>N;

    int tmp;
    vector<int> arr;
    for(int i=0;i<N;i++){
        cin>>tmp;
        arr.push_back(tmp);
        //arr2.push_back(tmp);
        //if((find(arr2.begin(),arr2.end(),tmp)!=arr2.end())==false)
        //    arr2.push_back(tmp);
    }

    //sort(arr2.begin(),arr2.end());

    // 중복 제거
    set<int> s(arr.begin(),arr.end());
    vector<int> v(s.begin(),s.end());

    for(int i=0;i<N;i++){
        cout<<lower_bound(v.begin(),v.end(),arr.at(i))-v.begin()<<' ';
    }
}
*/

/* 2번풀이*/
int main(){
    int N;
    cin>>N;
    vector<pair<int,int>> arr;
    int tmp;
    for(int i=0;i<N;i++){
        cin>>tmp;
        arr.push_back(make_pair(tmp,i)); 
    }

    sort(arr.begin(),arr.end());


    int* answer = new int[N];
    for(int i=0;i<N;i++){
        answer[i]=0;
    }

    int index=0;
    for(int i=0;i<N;i++){
        if(i!=0 && arr[i].first==arr[i-1].first){
            index--;
        }
        answer[arr[i].second]=index++;
    }

    for(int i=0;i<N;i++){
        cout<<answer[i]<<' ';
    }
}