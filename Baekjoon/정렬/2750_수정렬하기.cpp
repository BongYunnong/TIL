// https://www.acmicpc.net/problem/2750

// 버블정렬 -> 0ms
#include <iostream>
using namespace std;

int main() {
	int N;
	cin>>N;
	
	int arr[1001];
	
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	
	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			if(arr[i]>arr[j]){
				int temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
		}
	}
	
	for(int i=0;i<N;i++){
		cout<<arr[i]<<'\n';
	}
}

/* sort -> 40ms
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int N;
    cin>>N;

    int arr[1001];
    for(int i=0;i<1001;i++){
        arr[i] = -1;
    }

    int count=0;
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }

    sort(arr,arr+N);

    for(int i=0;i<N;i++){
        cout<<arr[i]<<endl;
    }
}
*/

/* 선택정렬 -> 44ms
#include<iostream>
using namespace std;
int main(){
    int N;
    cin>>N;

    int arr[1001];
    for(int i=0;i<1001;i++){
        arr[i] = -1;
    }

    int count=0;
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }

    // 선택정렬
    int min = 2000;
    int index=-1;
    for(int i=0;i<N;i++){
        min = arr[i];
        index = -1;
        // 가장 작은 값을 찾아서
        for(int j=i+1;j<N;j++){
            if(arr[j] < min){
                min = arr[j];
                index = j;
            }
        }
        // 지금 순서랑 바꿔주기
        if(index>=0){
            int tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
        }
    }

    for(int i=0;i<N;i++){
        cout<<arr[i]<<endl;
    }
}
*/