// https://www.acmicpc.net/problem/14500
// 알고보니, ㅏ 모양 빼고는 어떤 정점에서부터 4번 이동하였을 때 경로들이었다.
// 근데 결과를 보니 메모리랑 시간은 무식한 방법이 더 적긴 하다.

#include<iostream>
using namespace std;

int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};

int arr[501][501];
bool visited[501][501];
int N,M;

int result;
void GetMaxNum(int y,int x,int depth,int currScore){
    if(depth==3){
        if(result < currScore){
            result = currScore;
        }
        return;
    }

    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx<0||ny<0||ny>=N||nx>=M||visited[ny][nx])
            continue;
        visited[ny][nx]=true;

        GetMaxNum(ny,nx,depth+1,currScore+arr[ny][nx]);
        visited[ny][nx]=false;
    }
}

void GetMax(int y,int x){
    // ㅏ 형태는 한개의 경로를 통해 탐색할 수 없어서 수동을 해줘야함
    // ㅜ
    if (y + 1 < N && x + 2 < M)
        result = max(result, arr[y][x] + arr[y][x + 1] + arr[y][x + 2] + arr[y + 1][x + 1]);
    // ㅏ
    if (y + 2 < N && x + 1 < M)
        result = max(result, arr[y][x] + arr[y + 1][x] + arr[y + 1][x + 1] + arr[y + 2][x]);
    // ㅗ
    if (y - 1 >= 0 && x + 2 < M)
        result = max(result, arr[y][x] + arr[y][x + 1] + arr[y][x + 2] + arr[y - 1][x + 1]);
    // ㅓ
    if (y + 2 < N && x - 1 >= 0)
        result = max(result, arr[y][x] + arr[y + 1][x] + arr[y + 1][x - 1] + arr[y + 2][x]);

    visited[y][x]=true;
    GetMaxNum(y,x,0,arr[y][x]);
    visited[y][x]=false;
}

int main(){
    cin>>N>>M;
    
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>arr[i][j];
		}
	}
    
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
            GetMax(i,j);
		}
	}
    cout<<result;
}


// 도형 계산에 착오가 있어서 틀렸었음 -> 근데 이건 너무 무식한 방법
/*
#include <iostream>
using namespace std;

int arr[501][501];

int tmpResult=0;
int MaxResult=-1;
void Compare(){
	if(MaxResult<tmpResult){
		MaxResult=tmpResult;
	}
}
int main() {
	int N,M;
	cin>>N>>M;
	
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>arr[i][j];
			//cout<<arr[i][j]<<'_';
		}
		//cout<<'\n';
	}
	
	
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			//1)가로 4개
			if(j+3<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i][j+2];
				tmpResult+=arr[i][j+3];
			}
			Compare();
			//2)세로 4개
			if(i+3<N){
				tmpResult=arr[i][j];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i+2][j];
				tmpResult+=arr[i+3][j];
			}
			Compare();
			//3)스퀘어
			if(i+1<N && j+1<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i+1][j+1];
			}
			Compare();
			//4)L1
			if(i+2<N && j+1<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i+2][j];
				tmpResult+=arr[i+2][j+1];
			}
			Compare();
			//5)L2
			if(i+1<N && j+2<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i][j+2];
				tmpResult+=arr[i+1][j];
			}
			Compare();
			//6)L3
			if(i+2<N && j+1<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i+2][j+1];
			}
			Compare();
			//7)L4
			if(i+1<N && j+2<M){
				tmpResult=arr[i+1][j];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i+1][j+2];
				tmpResult+=arr[i][j+2];
			}
			Compare();
			//8)L5
			if(i+2<N && j+1<M){
				tmpResult=arr[i+2][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i+2][j+1];
			}
			Compare();
			//9)L6
			if(i+1<N && j+2<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i+1][j+2];
			}
			Compare();
			//10)L7
			if(i+2<N && j+1<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i+2][j];
			}
			Compare();
			//11)L8
			if(i+1<N && j+2<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i][j+2];
				tmpResult+=arr[i+1][j+2];
			}
			Compare();
			//12)z1
			if(i+2<N && j+1<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i+2][j+1];
			}
			Compare();
			//13)z2
			if(i+1<N && j+2<M){
				tmpResult=arr[i+1][j];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i][j+2];
			}
			Compare();
			//14)z3
			if(i+1<N && j+2<M){
				tmpResult=arr[i][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i+1][j+2];
			}
			Compare();
			//15)z4
			if(i+2<N && j+1<M){
				tmpResult=arr[i][j+1];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i+2][j];
			}
			Compare();
			//16)ㅏ
			if(i+2<N && j+1<M){
				tmpResult=arr[i+1][j];
				tmpResult+=arr[i][j];
				tmpResult+=arr[i+2][j];
				tmpResult+=arr[i+1][j+1];
			}
			Compare();
			//17)ㅜ
			if(i+1<N && j+2<M){
				tmpResult=arr[i][j+1];
				tmpResult+=arr[i][j];
				tmpResult+=arr[i+1][j+1];
				tmpResult+=arr[i][j+2];
			}
			Compare();
			//18)ㅗ
			if(i+1<N && j+2<M){
				tmpResult=arr[i+1][j+1];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i+1][j+2];
			}
			Compare();
			//19)ㅓ
			if(i+2<N && j+1<M){
				tmpResult=arr[i+1][j+1];
				tmpResult+=arr[i+1][j];
				tmpResult+=arr[i][j+1];
				tmpResult+=arr[i+2][j+1];
			}
			Compare();
		}
	}
	
	cout<<MaxResult;
}

*/