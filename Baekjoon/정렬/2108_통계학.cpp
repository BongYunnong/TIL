#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> arr;

int main(){
    int N;
    cin>>N;

    int* counting= new int[8001];
    for(int i=0;i<8001;i++){
        counting[i]=0;
    }

    int mean=0;
    for(int i=0;i<N;i++){
        int tmp;
        cin>>tmp;
        arr.push_back(tmp);
        counting[tmp+4000]++;
        mean += tmp;
    }
    sort(arr.begin(), arr.end());

    int maxCount=-10000;
    int maxCountIndex=-4001;
    bool isFirst= true;

    for(int i=0;i<8001;i++){
        if(counting[i]==0)
            continue;
        if(counting[i]==maxCount){
            if(isFirst==false){
                maxCountIndex = i-4000;
                isFirst=true;
            }
        }
        if(counting[i]>maxCount){
            maxCount = counting[i];
            maxCountIndex=i-4000;
            isFirst=false;
        }
    }

    // Mean을 그냥 넣으면 -0이 뜰 수 있음
    mean = round((float)mean/N);
    cout<< mean<<endl;
    cout<< arr[arr.size()/2]<<endl;
    cout<<maxCountIndex<<endl;
    cout<<arr.back()-arr.front()<<endl;
}
