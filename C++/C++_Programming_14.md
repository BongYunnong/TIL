# C++언어 기초 #14 - 템플릿 2
- 저번에 이어서 템플릿에 대해 조금 더 공부해보자.

## 1. 배열 클래스 템플릿
- 아래 예시는 배열클래스를 템플릿으로 사용하는 것을 보여준다.
``` c++
#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class BoundCheckArray{
priavate:
   T * arr;
   int arrlength;
   BoundCheckArray(const BoundCheckArray& arr){}
   BoundCheckArray& operator=(const BoundCheckArray& arr){}
public:
   BoundCheckArray(int length){
      arrlength = length;
      arr = new T[length];
   }
   T& operator[](int index){
      if(index<0 || index >=arrlength){
         cout<<"out of index"<<endl;
         exit(1);
      }
      return arr[index];
   }
   T operator[](int index) const{
      if(index<0 || index >=arrlength){
         cout<<"out of index"<<endl;
         exit(1);
      }
      return arr[index];
   }
   int GetLength() const{
      return arrlength;
   }
   ~BoundCheckArray(){
      delete []arr;
   }
}

class Point{
private:
   int xPos,yPos;
public:
   Point(int x=0,int y=0){
      xPos = x;
      yPos = y;
   }
   friend ostream& operator<<(ostream& os,const Point& pos);
};
ostream& operator<<(ostream& os, const Point& pos){
   os<<pos.xPos<<", "<<pos.yPos<<endl;
   return os;
}

int main(){
   BoundCheckArray<int> intArray(3);
   for(int i=0;i<3;i++){
      intArray[i] = i;
      cout<<intArray[i]<<endl;
   }

   BoundCheckArray<Point> pointArray(4);
   for(int i=0;i<4;i++){
      pointArray[i] = Point(i,i*2);
      cout<<pointArray[i];
   }

   typedef Point* Point_P;
   BoundCheckArray<Point_P> point_pArray(3);
   for(int i=0;i<point_pArray.GetLength();i++){
      point_pArray[i] = new Point(i,i*2);
      cout<<*(point_pArray[i]);
   }
   delete point_pArray[0];
   delete point_pArray[1];
   delete point_pArray[2];
}
```
```
0,
1
2
0, 0
1, 2
2, 4
3, 6
0, 0
1, 2
2, 4
```
- 여기에서 만약 Point가 xPos,yPos에 float이나 double형도 저장할 수 있도록 만들고싶다면
``` C++
template <typename T>
class Point{
private:
   T xPos,yPos;
public:
   Point(T x=0;y=0);
   void ShowPosition() const;
}
```
- 이렇게 Point 클래스도 템플릿으로 만들어서
    - BoundCheckArray\<Point\<double>> pointArray(5); 이런식으로 사용하면 된다.


## 2. 클래스 템플릿 특수화
- 함수 템플릿에 특수화가 가능한 것 처럼 클래스 템플릿도 당연하게 특수화가 가능하다.
``` C++
template <typename T>
class Point{
private:
   T xPos,yPos;
public:
   Point(T x=0;T y=0){
      xPos = x;
      yPos = y;
   }
   void ShowPoint() const{
      cout<<xPos<<", "<<yPos<<endl;
   }
};

template <>
class Point <int>{
private:
   int xPos,yPos;
public:
   Point(int x=0;int y=0){
      xPos =x;
      yPos =y;
   }
   void ShowPoint() const{
      coust<<"[int]"<<xPos<<", "<<yPos<<endl;
   }
};
template <>
class Point <char*>{
private:
   char* xPos,yPos;
public:
   Point(char* x;char* y){
      xPos =new char[strlen(x)+1];
      strcpy(xPos,x);
      yPos =new char[strlen(y)+1];
      strcpy(yPos,y);
   }
   void ShowPoint() const{
      coust<<"[char*]"<<xPos<<" "<<yPos<<endl;
   }
};
```

## 3.  템플릿 인자
- 템플릿은  자료형을 특정하지 않을 수 있다는 장점이 있는데, 그렇다고 int같은 자료형을 선언할 수 없는 것이 아니다.
``` C++
template <typename T, int length=3>
class MyArray{
private:
   T arr[length];
public:
   T& operator[] (int index){
      return arr[index];
   }
};
```
- MyArray<int, 10> myArr1; 이런식으로 10을 전달해서 크기가 10인 배열을 만들 수 있다.


## 4.  static
- static은 처음에 한번 초기화된다는 성격이 있으니까 템플릿으로 만든 함수들이 다 값을 공유할 것 같은데, 그렇지 않다.
- static을 T형으로 선언하면 템플릿 함수에 각각 따로 존재하게된다.