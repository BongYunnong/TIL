// https://www.acmicpc.net/problem/1966

// 현재 Queue의 가장 앞에 있는 문서의 ‘중요도’를 확인한다.
// 나머지 문서들 중 현재 문서보다 중요도가 높은 문서가 하나라도 있다면,
// 이 문서를 인쇄하지 않고 Queue의 가장 뒤에 재배치 한다. 그렇지 않다면 바로 인쇄를 한다.


#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
bool Compare(int a,int b){
    return a>b;
}
int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N;
        cin>>N;
        int M;
        cin>>M;

        int index=0;
        queue<pair<int,int>> q;
        int* arrs = new int[N];
        for(int j=0;j<N;j++){
            int val;
            cin>>val;
            // index와 중요도 push
            q.push({j,val});
            // 문서의 중요도를 arrs에 저장
            arrs[j] = val;
        }
        sort(arrs,arrs+N,Compare);

        while(q.size()>=1){
            // arrs[index]는 현재 최대 중요도의 문서
            // q는 sort되지 않은 queue
            if(q.front().second==arrs[index]){
                // 중요도가 같은데
                if(q.front().first==M){
                    // 원하는 문서를 찾으면 출력, 탈출
                    cout<<index+1<<'\n';
                    break;
                }else{
                    // 중요도가 같은데 원하는 문서가 아니라면 그냥 빼고 push를 안 해도 됨
                    q.pop();
                    index++;
                }
            }else{
                // 뒤로 보내기
                pair<int,int> tmp = q.front();
                q.pop();
                q.push(tmp);
            }
        }
    }
}