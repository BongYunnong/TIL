Divide and Conquer
=================
<br>

Max Problem
--------------------
--------------------
- Problem : Fine a max element in the array S
- n개의 숫자를 가진 리스트 S안에 숫자 x가 존재하는지 확인하는 문제
    - Input : array S
    - Output : max element in S

- Instance
    - Input : S=[10,7,11,5,13,8]
    - Output : 13

- 시간복잡도
    - F(n) = F(n/2) + F(n/2) + 1 = 2f(n/2)+1
    - F(1) = 1
    - F(n/2) = 2(F(n/(2<sup>2</sup>)))+1
    - F(n) = n
    - 이 경우에는 divide and conquer로 한다 해도 얻을 수 있는 것이 없음. (쪼개고 합치는 과정에서 더 오래걸릴 수도 있다.)
<br><br>

Search Problem 2
--------------------
--------------------
- Problem : Where is the key x in the array S of n keys?
- n개의 숫자를 가진 리스트 S안에 숫자 x의 위치를 확인하는 문제
    - Input : array S, x
    - Output : x의 index
- 해결방법 : 요소가 하나가 될 때까지 반으로 자르고, 찾으면 위치 out, 못 찾으면 반으로 잘라서 남은 다른 요소를 반으로 자르면서 체크
<br><br>

Search Problem 3
--------------------
--------------------
- Problem : Where is the key x in the array S of n keys which is ordered as nondecreasing?
- n개의 숫자를 가진 오름차순 리스트 S안에 숫자 x의 위치를 확인하는 문제
    - Input : array S, x
    - Output : x의 index
- 해결방법 : 요소가 하나가 될 때까지 반으로 자르고, 찾으면 위치 out, 못 찾으면 x가 S[middle]보다 작으면 왼쪽, 크면 오른쪽에서 x를 탐색
<br><br>

```C++
void binsearch(int n, const keytype S[], keytype x, index& location){
    index low, high, mid;
    low = 1; high = n;
    location = 0;
    while(low <= high && location ==0){
        mid = (low + high) / 2;
        if(x == S[mid]) location = mid;
        else if(x < S[mid]) high = mid -1;
        else low = mid + 1;
    }
}
```
```C++
index location(index low, index high){
    index mid;
    if(low >high)
        return 0;
    else{
        mid = (low+high)/2;
        if(x == S[mid])
            return mid;
        else if (x < S[mid]){
            location(low, mid-1);
        }else{
            location(mid+1, high);
        }
    }
}
```
- 시간복잡도 (n : power of 2)
    - W(n) = W(n/2) + 1 
    - W(1) = 1
    - W(n) = W(2<sup>k</sup>) = W(2<sup>k-1</sup>) + 1 = W(2<sup>k-2</sup>)+2 = W(2<sup>k-3</sup>)+3 ... = W(2<sup>k-p</sup>+p)
    - P에 k를 넣으면? W(2<sup>0</sup>)+k = 1+k
    - k를 n으로 표현하면? W(n) = W(2<sup>k</sup>) -> k = log<sub>2</sub>n
    - O(logN)

<br>

Merge
--------------------
--------------------
- Problem : sorted된 array u, v를 하나의 sorted된 array S로 합치기
    - Input : sorted array u,v
    - Output : sorted array s
```C++
void merge(int h, int m, keytype U[], keytype V[], keytype S[]){
    i = 1; j = 1; k = 1;
    while(i<=h && j <= m){
        if(U[i] < V[j]){
            S[k] = U[i];
            i++;
        }else{
            S[k] = V[j];
            j++;
        }
        k++;
    }
    if(i>h)
        copy V[j] through V[m] to S[k] through S[h+m];
    else
        copy U[j] through U[m] to S[k] through S[h+m];
}
```

Merge Sort
--------------------
--------------------
- Problem : array S를 하나의 sorted된 array S로 만들기
    - Input : array S
    - Output : sorted array s
```C++
void mergesort(int n, keytype S[]){
    const int h = n / 2, m = n-h;
    keytype U[1...h], V[1...m];

    if(n>1){
        copy S[1] through S[h] to U[1] through U[h];
        copy S[h+1] through S[n] to V[1] through V[m];
        mergesort(h, U);
        mergesort(m, V);
        merge(h,m,U,V,S);
    }
}
```
- 시간복잡도
    - 나누는 과정에서 각각 n시간
    - 합치는 과정에서 f(n/2)시간 * 2
    - 마지막 단계에서 n시간
    - f(n) = 2n + 2f(n/2)
    - f(1) = 1
    - f(n) = 2n + 2(n + 2f(n/4)) = 2<sup>2</sup> * f(n/(2<sup>2</sup>)) + 2n + 2n
    - f(n) = 2<sup>k</sup> * f(n/(2<sup>k</sup>)) + k*2*n
        - k를 log<sub>2</sub>n이라고 생각한다면?
        - n * f(n/n) + 2n*log<sub>2</sub>n = n + 2nlog<sub>2</sub>n
    - n + 2nlogn
    - O(nlogn)
<br>

Quick Sort
--------------------
--------------------
- Problem : low부터 high까지 array를 Sort하기
    - Input : low, high
    - Output : sorted array s
- 학생들을 키 순에 따라 줄세울때, 한 명을 기준으로 잡고, 그 기준보다 작은 학생은 전부 왼쪽, 큰 학생은 전부 오른쪽에 배치. 그리고 왼쪽, 오른쪽을 방금의 방법과 같게 반복.
```C++
void quickSort(index low, index high){
    index pivotPoint;
    if(high > low){
        partition1(low, high, pivotPoint);
        quickSort(low, pivotPoint - 1);
        quickSort(pivotPoint + 1 , high);
    }
}
```

- 시간복잡도 (Worst)
    - T(n)은 n-1(partition) + T(0) + T(n-1)
    - T(0) = 0
    - T(n) = T(n-1) + n-1 = T(n-2) + (n-2) + (n-1)
    - ((n-1)*n)/2 -> O(n<sup>2</sup>)
- 시간복잡도 (Best)
    - T(n) = (n-1) + T(n/2) + T(n/2) = n+T(n/2)
    - T(n) = n + n/2 + n/4 + n/8 + n/16 + ... + n/2<sup>k</sup> =  2n*(1-(1/2)<sup>k</sup>)
    - n = 2<sup>k</sup>일 때, 재귀 호출이 끝난다. k = log<sub>2</sub>n
    - 2n*(1-2<sup>-k</sup>) = 2n - 2n * 2<sup>-k</sup> = 2n - 2n * 2<sup>-log<sub>2</sub>n</sup> = 2n + 2n * log<sub>2</sub>n => nlog<sub>2</sub>n 

- merge sort는 메모리를 2배 쓰고, copy하는데에도 시간이 걸림
- 똑같은 nlogn이라도 mergesort의 nlogn과 quicksort의 nlogn은 다르다.

<br>

Partition Problem
--------------------
--------------------
- Problem : 배열 S를 나누는 함수
    - Input : array S
    - Output : pivot location, array S
- A와 B라는 새로운 배열을 만들어서 작은것, 큰 것 넣어주고 S에 삽입.
```C++
void partition1(index low, index high, index& pivotPoint){
    index i,j,k,m;
    keytype pivotItem;
    keytype* A = new keytype[high-low+1];
    keytype* B = new keytype[high-low+1];
    pivotItem = S[low];
    j = 1; k = 1;
    for(i = low; i<=high ; i++){
        if(S[i] < pivotItem){
            A[j] = S[i];
            j++;
        }else{
            B[k] = S[i];
            k++;
        }
    }
    pivotPoint = j;
    i = low;
    for(m= 1;m<j;m++){
        S[i] = A[m];
        i++;
    }
    S[i] = pivotItem;
    i++;
    for(m=1;m<k;m++){
        S[i] = B[m];
        i++;
    }
    delete[] A;
    delete[] B;
}
```
- Simple하긴 하지만 공간 복잡도가 늘어남.
- A와 B를 합쳐서 하나의 n개 메모리를 사용해도 되지 않을까?
- C라는 메모리를 만들어서 A에 넣을 것은 앞에서부터, B에 넣을 것은 뒤에서부터 넣으면 됨.
- C도 사용 안하면 어떨까?
```C++
void partition(index low, index high, index& pivotPoint){
    index i,j;
    keytype pivotItem;
    pivotItem = S[low];
    j=low;
    for(i=low+1;i<high;i++){
        if(S[i] < pivotItem){
            j++;
            exchange S[i] and S[j];
        }
    }
    pivotPoint = j;
    exchange S[low] and S[pivotPoint];
}
```
- 3개의 그룹으로 나누어보자. 정렬된 값들, pivotItem 왼쪽의 값들, pivotItem오른쪽의 값들

- 시간복잡도
    - Partition : n번
    - Worst : n<sup>2</sup>
    - Average : nlogn
    - Best : nlogn

------------------
------------------

<br>

퀵 정렬
----------------------
---------------------
- 특정한 값을 기준으로 큰 숫자와 작은 숫자를 나누자.
- 시간복잡도 : 최악의 경우 O(n<sup>2</sup>), 평균 O(nlogn)
- 다 정렬이 되어있는 경우, 한가지 숫자만 정렬이 되기에 n<sup>2</sup>이 된다.
```C++
void QuickSort(int* data,int start,int end){
    if(start>=end){
        return;
    }
    int key= start;
    int i = start+1, j = end, temp;
    while(i<=j){
        // 왼쪽에서 오른쪽으로 key보다 큰 값 찾기
        while(i<=end && data[i] <= data[key]){
            i++;
        }
        // 오른쪽에서 왼쪽으로 key보다 작은 값 찾기
        while(j > start && data[j] >= data[key]){
            j--;
        }
        if(i>j){
            // i와 j가 엇갈리면 key와 작은 값 swap
            // 지금까지 찾은 값들은 key 왼쪽이 됨
            temp = data[j];
            data[j] = data[key];
            data[key] = temp;
        }else{
            // 엇갈리지 않을 때 작은 값과 큰 값 swap
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    // j 는 이미 정렬되어있기에 start ~ j-1, j+1 ~ end
    QuickSort(data, start, j-1);
    QuickSort(data, j+1, end);
}
```

<br>

병합 정렬
----------------------
---------------------
- 다 나누었다가 합치면서 정렬하자.
- 시간복잡도 : O(nlogn) 보장 
- 시간복잡도는 좋지만 메모리를 별도의 할당해야한다.
```C++
int sorted[8];
void merge(int a[], int _start, int _middle, int _end){
    int start = _start;
    int start2 = _middle+1;
    int index = _Start;
    while(start<=middle && start2<=_end){
        // 더 작은 것을 먼저 sorted에 넣는다.
        if(a[start] <= a[start2]){
            sorted[index] = a[start];
            start++;
        }else{
            sorted[index] = a[start2];
            start2++;
        }
        index++;
    }
    // start에서부터와 start2에서부터 중 남은 것을 마저 sorted에 넘김
    if(start > _middle){
        for(int t=start2; t <= _end; t++){
            sorted[index] = a[t];
            index++;
        }
    }else{
        for(int t=start; t <= _middle; t++){
            sorted[index] = a[t];
            index++;
        }
    }

    for(int t=start; t <= _end; t++){
        a[t] = sorted[t];
}
void mergeSort(int a[], int m, int n){
    if(m < n){
        middle = (m+n)/2;
        mergeSort(a,m,middle);
        mergeSort(a,middle+1,n);
        merge(a,m,middle,n);
    }
}
```
<br>

STL Sort()
----------------------
---------------------
```C++
#include<iostream>
#include<algorithm>
int main(){
    int a[10] = {9,3,5,4,1,10,8,6,7,2};
    sort(a,a+10);
    for(int i=0;i<10 ; i++){
        cout<<a[i] << ' ';
    }
}
```
```C++
bool Compare(int a, int b){
    // 아래 것을 >로 바꾸면 내림차순이 된다.    
    return a<b ;
}
int main(){
    int a[10] = {9,3,5,4,1,10,8,6,7,2};
    sort(a,a+10,Compare);
    for(int i=0;i<10 ; i++){
        cout<<a[i] << ' ';
    }
}
```
```C++
class student{
    public:
        string name;
        int score;
        student(string name, int score){
            this->name = name;
            this->score = score;
        }
        bool operator<(student & student){
            return this->score < student.score;
        }
}
```
----------------------
- 클래스 정의는 속도 면에서 유리하지 않음
- 클래스는 실무에 적합하고, 프로그래밍 대회에서는 'pair'를 사용

```C++
#include<iostream>
#include<vector>
#include<algorithm>
int main(){
    vector<pair<int, string>> v;
    v.push_back(pair<int,string>(90,"A"));
    v.push_back(pair<int,string>(85,"B"));
    ...
    sort(v.begin(), v.end());
}
```
```C++
bool Compare(pair<string, pair<int,int>> a, pair<string, pair<int,int>> b){
    if(a.second.first == b.second.first){
        return a.second.second > b.second.second;
    }else{
        return a.second.first > b.second.first;
    }
}
```
