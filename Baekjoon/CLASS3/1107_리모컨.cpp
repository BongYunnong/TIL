// https://www.acmicpc.net/problem/1107
// 브루트포스 문제
// 테스트케이스가 적어서 그냥 다 돌리는 것이 낫다고 한다.
// 나는 리모컨이 고장난 곳에서 모든 값을 다 넣어보는 것을 생각했는데, 0이나 9일 경우 자릿수가 바뀌는 것 때문에 포기를 했다.

#include<iostream>
using namespace std;

bool arr[11];
int check(int n){
    // 이동하려는 채널이 0일 경우 특별히 처리
    if(n==0){
        if(arr[0])
            return 0;
        else
            return 1;
    }

    int len=0;
    while(n>0){
        // 버튼이 고장났을 경우
        if(arr[n%10])
            return 0;
        // 버튼이 고장나지 않았다면 다음 자리의 수 체크
        n/=10;
        len++;
    }
    // 리모컨을 누른 횟수
    return len;
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    cout.tie(NULL);

    int n,m;
    cin>>n>>m;

    for(int i=0;i<m;i++){
        int x;
        cin>>x;
        arr[x]=true;
    }
    int ans = abs(n-100);
    for(int i=0;i<10000000;i++){
        int c = i;
        int len = check(c);
        if(len>0){
            int press = abs(c-n);
            if(ans>press+len){
                ans = press+len;
            }
        }
    }
    cout<<ans;
}

/* 포기..
#include<iostream>
#include<string>
using namespace std;

bool remoteController[10];
int answer;

int input[7];
int N;

int result[7];

void FindAnswer(){
    int result=100;


    int firstWrongIndex=-1;
    for(int i=0;i<7;i++){
        if(remoteController[input[i]]==true){
            // 버튼이 정상적으로 있으면 다음 것 확인
            result[i]=input[i];
            continue;
        }else{
            if(firstWrongIndex==-1)
                firstWrongIndex=i;

            if(input[i]==9){
                int index=0;
                while(remoteController[index]==false){
                    index++;
                }
                int index2=8;
                while(remoteController[index2]==false){
                    index2--;
                }

                
                int index3=0;
                while(remoteController[index]==false){
                    index3++;
                }
                
                int sum1=N[i]+1;


            }else if(N[i]==0){

            }else{

            }
            break;
        }
    }
}

int main(){
    cin>>N;
    int index=0;
    while(N>=10){
        input[index]=N/10;
        index++;
    }
    input[index]=N;

    int M;
    cin>>M;
    fill(remoteController,remoteController+10,true);
    for(int i=0;i<M;i++){
        int tmp;
        cin>>tmp;
        remoteController[tmp]=false;
    }
    FindAnswer();

}
*/