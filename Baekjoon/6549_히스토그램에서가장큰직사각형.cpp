// https://www.acmicpc.net/problem/6549
// 세그먼트 트리, 분할정복 등으로 풀 수 있다고 함


#include<iostream>
using namespace std;

int inputs[100001];

/*
int solve(int left, int right){
    int mid= (left+right)/2;
    int h = inputs[mid];
    int midArea= inputs[mid];

    int _left = mid-1;
    int _right = mid+1;

    if(left+1 >= right){
        return midArea;
    }
    while(_left > left || _right < right){
        if(_left<=left || (_right<right && inputs[_left]<=inputs[_right])){
            h = min(inputs[_right], h);
            _right++;
        }else{
            h = min(inputs[_left],h);
            _left--;
        }
        int width = _right-1-_left;
        midArea = max(midArea,width*h);
    }
    return max(midArea,max(solve(_left,mid),solve(mid,right)));
}
*/
int N;
int result=0;
void solve(int val, int st,int ed){
    if(st>ed)
        return;
    
    int mid = (st+ed)/2;
    
    int count=0;
    int currResult=0;
    for(int i=0;i<N;i++){
        if(inputs[i]>=mid){
            count++;
            currResult+=mid;
        }else{
            count=0;
            currResult=0;
        }
        result = max(result,currResult);
    }

    solve(val,st,mid);
    solve(val,mid+1,ed);

}

int main(){
    while(true){
        result=0;
        cin>>N;
        if(N==0){
            break;
        }
        for(int i=0;i<N;i++){
            cin>>inputs[i];
        }
        solve(N,0,N-1);
        cout<<result;
    }
}