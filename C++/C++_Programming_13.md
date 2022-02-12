# C++언어 기초 #13 - 템플릿
- 이제 템플릿에 대해 배울텐데, 그전에 string 클래스에 대해서 배우자.

## 1. String
- c++ 표준 라이브러리인 string 클래스를 사용하면 문자열을 아주 쉽게, 유용하게 사용할 수 있다.
``` C++
#include<iostream>
#include<string>
using namespace std;

int main(){
   string str1 = "Hello";
   string str2 = " World";
   string str3 = str1+str2;

   cout<<str1<<endl;
   cout<<str3<<endl;

   str3+=str2;
   cout<<str3<<endl;

   if(str1==str2)
      cot<<"str1==str2"<<endl;
   else
      cout<<"str1!=str2"<<endl;

   string str4;
   cout<<"문자열 입력: ";
   cin>>str4;
   cout<<"입력한 문자열 : "<<str4<<endl;
}
```
```
Hello
Hello World
Hello World World
str1!=str2
문자열 입력 : hi
입력한 문자열 : hi
```
- 지금까지 char을 크기에 맞춰서 동적배열 하던것을 생각해보면 속이 뻥 뚫릴듯이 편하다.
- 이것을 우리가 지금까지 배운것들을 통해 구현하려면 다음과 같이 코드를 작성하면 된다.
``` C++
#include <iostream>
#include <cstring>
using namespace std;

class String{
private:
   int length;
   char * str;
public:
   String(){
      length=0;
      str= NULL;
   }
   String(const char* s){
      len = strlen(s)+1;
      str = new char[length];
      strcpy(str,s);
   }
   String(const String& s){
      len = s.length;
      str = new char[length];
      strcpy(str,s.str);
   }
   ~String(){
      if(str!=NULL)
         delete []str;
   }
   String& operator=(const String& s){
      if(str!=NULL)
         delete []str;
      length=s.length;
      str = new char[length];
      strcpy(str,s.str);
      return * this;
   }
   String& operator+=(const String& s){
      length+=(s.length-1);
      char* tempStr= new char[length];
      strcpy(tempStr,str);  //복사
      strcat(tempStr,s.str);//더하기
      if(str!=NULL)
         delete []str;
      str=  tempStr;
      return *this;
   }
   bool operator==(const String& s){
      return strcmp(str,s.str) ? false : true;
   }
   String operator+(const String& s){
      char& tempStr = new char[length+s.length-1];
      strcpy(tempStr,str);  //복사
      strcat(tempStr,s.str);//더하기
      String temp(tempStr);
      delete []tempStr;
      return temp;
   }
}
ostream& operator<<(ostream& os,const String& s){
   os<<s.str;
   return os;
}
istream& operator>>(istream& is, String& s){
   char str[100];
   is>>str;
   s= String(str);
   return is;
}
```

## 2. 함수 템플릿
- 템플릿은 함수를 만드는 도구이다. 함수의 자료형이 결정되어있지 않아서, 기능은 유지한 채 다양한 자료형의 변수를 사용하는 함수를 많이 만들어낼 수 있다.
- 템플릿의  기본형태는 아래와 같다.
    ``` C++
    template <typename T>
    T Add(T num1, T num2){
        return num1+num2;
    }
    ```
    - 이것을 우리는 '함수 템플릿'이라고 부른다.
    - template \<typename T>는 문장 아래의 함수를 함수를 템플릿으로 정의한다는 것이다.
    - \<typename T> 대신  \<class T> 이렇게 써도 되고, T대신 다른 문자를 써도 되는데, template인 것을 명시하기위해 T를 사용하자.

- 위와 같이 만든 템플릿을 사용하는 방법은 아래와 같다.
``` C++
#include <iostream>
using namespace std;
template <typename T>
T Add(T num1, T num2){
   return num1+num2;
}

int main(){
   cout << Add<int>(10,20) <<endl;
   cout << Add<double>(1.2,3.14) <<endl;
}
```
```
30
4.34
```
- Add\<int>, Add\<double> 이렇게 꺽쇠안에 원하는 자료형을 넣으면 T가 해당 자료형으로 바뀌어서 컴파일러가 int Add(int num1, int num2), double Add(double num1, double num2)를 만들어낸다. 
- 이것을 우리는 '템플릿 함수'라고 부른다.
    - 물론 한번 만들어내면 나중에 똑같은 자료형의 함수를 만들지는 않고 호출한다. 또한, 따로 int Add(int num1,int num2)이러한 일반적인 함수를 만들면 템플릿 함수와 다른 것으로 인식되어 구분된다.
    - 이 꺽쇠<>는 사실 없앨수도있는데, 그러면 컴파일러가 인자를 보고 자동으로 자료형을 결정해준다. Add\<int>(1.2,2.14)이렇게 double형 인자를 int로 바꾸고싶다면 꺽쇠를 사용해서 원하는 자료형을 명시해주자.
    - 그런데 매개변수는 여러개인데 다 똑같은 자료형만 쓸 수 있으면 그 의미가 너무 축소된다. 그래서 템플릿은 여러개의 자료형을 사용할 수 있게 해준다.
``` c++
#include <iostream>
using namespace std;
template <typename T1,typename T2>
void PrintAddedData(double num1, double num2){
   return cout<<(T1)num1<<" / "<<(T2)num2<<endl;
}

int main(){
   cout << Add<char,int>(65,66) <<endl;
   cout << Add<int,double>(10,20.1) <<endl;
   cout << Add<double,int>(1.2,3.14) <<endl;
}
```
```
A / 66
10 / 20.1
1.2 / 3
```
- 자료형을 T1, T2 이렇게 여러개를 만들고,  강제 형변환을 해주었다.

- 여기에 추가적으로, '템플릿의 특수화'라는 것이 있다.
- 특수화를 통해서 템플릿의 기능에 예외를 둘 수 있다.
``` c++
#include <iostream>
using namespace std;
template <typename T>
T Max(T a, T b){
   if(a>=b)
       return a;
   else
      return b;
}

tmeplate<>
char* Max<char*>(char* a,char* b){
   if(strlen(a)>=strlen(b))
       return a;
   else
      return b;
}

int main(){
   cout<<Max(10,20)<<endl;
   cout<<Max(3.14.6.28)<<endl;

   char str1[] ="A";
   char str2[] ="ABC";
   cout<<Max(str1,str2)<<endl;
}
```
```
20
6.28
ABC
```
- 원래 Max 템플릿 함수로는 문자열의 주소값을 비교해서 return했겠지만,  함수 템플릿의 특수화를 통해 문자열은 예외적으로 다른 기능을 할 수 있도록 만들어졌다. 이것도 함수 오버로딩처럼 매개변수, 반환형에 따라서 사용될 템플릿이 결정된다.

- char* Max<char*>(char* a,char* b)의 <char*>는 없어도 되는데, 자료형을 의미를 명확히 하기 위해 써주자.

​

# 3. 클래스 템플릿
- 아까는 함수 템플릿을 만들었는데, 템플릿으로 클래스도 만들 수 있다.
``` c++
#include<iostream>
using namespace std;

template <typename T>
class TwoData{
private:
   T a,b;
public:
   TwoData(T x=0,T y=0) : a(x),b(y){}
   void ShowData() const{
      cout<<"Data1 : "<<a<<" / Data2 : "<<b<<endl;
   }
   void ShowData2() const;
};

template <typename T>
void TwoData<T>::ShowData2() const{
   cout<<"[Data1 : "<<a<<" , Data2 : "<<b<<"]"<<endl;
}

int main(){
   TwoData<int> data1(10,20);
   TwoData<double> data2(3.14,6.28);
   TwoData<char> data3('A','C');

   data1.ShowData();
   data2.ShowData();
   data3.ShowData();
   data1.ShowData2();
   data2.ShowData2();
   data3.ShowData2();
}
```
```
Data1 : 10 / Data2 : 20
Data1 : 3.14 / Data2 : 6.28
Data1 : A / Data2 : C
[Data1 : 10 , Data2 : 20]
[Data1 : 3.14 , Data2 : 6.28]
[Data1 : A , Data2 : C]
```
