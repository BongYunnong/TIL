// https://www.acmicpc.net/problem/9663
// 퀸은 한 줄에 하나밖에 놓을 수 없다.

#include<iostream>
using namespace std;

int N;
int arr[15];
int result=0;
void dfs(int count){
    if(count==N){
        result++;
    }else{
        // 퀸은 한 줄에 하나밖에 넣을 수 없기에 N번 반복하는 for문 -> 하나씩 다 넣어봄
        // arr[x]는 x의 행, arr[x]의 열에 퀸을 놓겠다는 뜻 
	    for(int i=0;i<N;i++){
	    	bool canDo=true;
	    	arr[count]=i;

            // 퀸을 같은 열에 놓거나, 기울기가 1이 되어버리면 못 놓음
	    	for(int j=0;j<count;j++){
	    		if(arr[j]==arr[count] || abs(arr[count]-arr[j])==count-j)
	    			canDo= false;
	    	}

            // 놓을 수 있으면 다음 퀸 도전
	    	if(canDo)
				dfs(count+1);
	    }
    }
}
int main(){
    cin>>N;
    dfs(0);
    cout<<result;
}

/* Time Exceed...
int N;

int visited[16][16];

int counts=0;
void dfs(int _x,int _y,int _index){
    if(_index==N){
        counts++;
        return;
    }

    for(int i=1;i<=N;i++){
        if(visited[_x][_y]==-1){
            dfs(_x+1,_y,_index);
            dfs(_x,_y+1,_index);
        }else{
            for(int j=1;j<=N;j++){
                for(int k=1;k<=N;k++){
                    if(j==_x || k == _y || j-_x==_y-k || j-_x==-_y+_x){
                        visited[j][k]=-1;
                    }
                }
            }
            dfs(_x+1,_y,_index+1);
            dfs(_x,_y+1,_index+1);
        }
    }
}

int main(){
    cin>>N;


    for(int i=0;i<=N;i++){
        for(int g=0;g<=N;g++){
            visited[i][g]=0;
        }
    }
    dfs(0,0,1);
    cout<<counts;
}
*/