#include<iostream>
using namespace std;

int N;
int arr[15];
int result=0;
void dfs(int count){
    if(count==N){
        result++;
    }else{
	    for(int i=0;i<N;i++){
	    	bool canDo=true;
	    	arr[count]=i;
	    	for(int j=0;j<count;j++){
	    		if(arr[j]==arr[count] || abs(arr[count]-arr[j])==count-j)
	    			canDo= false;
	    	}
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