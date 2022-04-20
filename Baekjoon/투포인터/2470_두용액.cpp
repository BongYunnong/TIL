#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N;
    cin>>N;
    int* inputs = new int[N];
    for(int i=0;i<N;i++){
        cin>>inputs[i];
    }

    int minVal=1000000000;
    int start=0;
    int end = N-1;

    int result1;
    int result2;
    for(start =0;start < N-1;start++){
        end = N-1;
        int pastSum = 1000000000;
        // 다음 합의 절댓값이 더 커지면 탈출
        if(abs(pastSum) > abs(sum)){
            pastSum=abs(sum);
            end--;
        }else{
            break;
        }

        if(minVal > pastSum){
            minVal = pastSum;
            result1= start;
            result2=end+1;
        }
    }
    cout<<inputs[result1]<<' '<<inputs[result2];
}