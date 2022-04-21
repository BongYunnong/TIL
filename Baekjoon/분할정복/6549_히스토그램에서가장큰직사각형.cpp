#include<iostream>
using namespace std;

int inputs[100001];

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

int main(){
    while(true){
        int N;
        cin>>N;
        if(N==0){
            break;
        }
        for(int i=0;i<N;i++){
            cin>>inputs[i];
        }

    }
}