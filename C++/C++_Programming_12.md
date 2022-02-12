# C++언어 기초 #12 - 연산자 오버로딩 2
- 지금까지는 함수의 오버로딩에 대해서만 배웠는데, 연산자도 오버로딩이 가능하다.
- int형은 원래 int형과만 더하기를 할 수 있는데, +에 오버로딩을 하면 int형과 float형도 더하기를 할 수 있는 그런 개념이다.

## 1 대입 연산자 =
- 대입 연산자의 특성은 다음과 같다.
    1. 정의하지 않았다면 '디폴트 대입 연산자'가 생성된다.
    2. 디폴트 대입 연산자는 얕은 복사를 한다.
    3. 연산자 내에서 동적 할당을 하거나, 깊은 복사가 필요하면 직접 정의해야한다.​
``` C++
class Point{
private:
   int x,y;
};

int main(){
   Point pos1(1,2);
   Point pos2(2,3);

   pos2 = pos1; // 디폴트 대입 연산자 호출
   //pos2.operator=(pos1);
}
```
- 이 상황에서 Point 클래스에 삽입된 디폴트 대입 연산자는 다음과 같다.
``` C++
Point& operator=(const Point& ref){
   x= ref.x;
   y= ref.y;
   return *this;
}
```
- 그런데 이 디폴트 대입 연산자는 디폴트 복사 생성자와 매우 유사하다.
- 그래서 디폴트 복사 생성자의 문제점을  가지고있다. 그 문제는 바로 얕은 복사 이다.
``` C++
#include<iostream>
#include<cstring>
using namespace std;

class Person{
private:
   char * name;
   int level;
public:
   Person(char *_name,int _level){
      int len = strlen(_name)+1;
      _name=  new char[len];
      strcpy(name,_name);
      level = _level;
   }
   ~Person(){
      delete []name;
      cout << "소멸자"<<endl;
   }
};
int main(){
   Person character1("Kim",10);
   Person character2("Lee",20);
   character2 = character1;
}
```
- character2의 name과 level을 출력해보면 정상적으로 character1의 값이었던 Kim과 10을 출력할 것이다.
- 문제는 클래스가 소멸될때이다. 위의 예시를 실행해보면 소멸자가 1번만 호출된다.
    - 그 이유는 character2가 character1의 name을 복사할 때 얕은 복사를 통해 "Kim"의 주소를 가져왔기 때문이다.
    - 그래서 character1이 소멸된 후 character2를 소멸하려 보면 character2의 name은 이미 소멸되어있는 상태이다.
    - 또한 character2를 생성할 때 할당된 Lee를 가리키는 주소값을 잃게되므로 메모리 누수로 이어진다.
    - 이렇듯 디폴트 대입 연산자는 그냥 사용하기에는 문제가 있기에 프로그래머가 직접 연산자 오버로딩을 해주어야할 때가 있다.
- 그럼 어떻게 오버로딩을 해주어야할까?
``` C++
Person& operator=(const Person& ref){
   delete []name;
   int len = strlen(ref.name)+1;
   name = new char[len];
   strcpy(name,ref.name);
   level = ref.level;
   return *this;
}
```
- 위처럼, name을 미리 delete해주어서 메모리 누수를 막으면 된다.


- 그리고 주의할 점이 또 있다.
    - 자식 클래스의 디폴트 대입 연산자는 부모 클래스의 대입 연산자도 호출하는데,
    - 자식 클래스에 연산자 오버로딩을 해놓고 부모 클래스의 대입 연산자를 따로 호출하지 않으면 부모 클래스의 대입 연산자는 호출되지 않는다.
    ``` C++
    Warrior& operator=(const Warrior& ref){
        Person::operator=(ref);
        warrirorLevel =  ref.warriorLevel;
        return *this;
    }
    ```
    - 그래서 위의 예시처럼 부모 클래스의 대입 연산자를 사용하겠다고 명시해주어야한다.
​
- tip) 이니셜라이저의 성능 향상 이유를 대입 연산자로 알아보자.
``` C++
#include<iostream>
using namespace std;
class MyNumber{
private:
   int num;
public:
   MyNumber(int _n=0):num(_n){
      cout<<"MyNumber(int _n=0)"<<endl;
   }
   MyNumber(const MyNumber& ref): num(ref.num){
      cout<<"MyNumber(const MyNumber& ref)"<<endl;
   }
   MyNumber& operator=(const MyNumber& ref){
      num = ref.num;
      cout<<"operator=(const MyNumber& ref)"<<endl;
      return *this;
   }
};
class MyMyNumber{
private:
   MyNumber mNum;
public:
   MyMyNumber(const MyNumber& ref):mNum(ref){}
};
class MyMyNumber2{
private:
   MyNumber mNum;
public:
   MyMyNumber2(const MyNumber& ref){mNum = ref;}
};
int main(){
   MyNumber mNum(10);
   cout<<"--------"<<endl;
   MyMyNumber mNum1(mNum);
   cout<<"--------"<<endl;
   MyMyNumber2 mNum2(mNum);
}
```
```
MyNumber(int _n=0)
--------
MyNumber(const MyNumber& ref)
--------
MyNumber(int _n=0)
operator=(const MyNumber& ref)
```
위의 결과를 보듯이, mNum을 이니셜라이저로 받으면 선언과 동시에 초기화가 되어 하나의 생성자만 호출이된다.
- 그에 비해 mNum을 생성자의 몸체 부분을 통해 받으면 선언 따로, 초기화 따로 진행하는 형태로 바이너리 코드가 생성되기에 생성자와 대입 연산자 총 2개의 함수가 호출되어 더욱 느려진다.


## 2 배열 클래스, 인덱스 연산자
- 배열 클래스는 '배열의 역할을 하는 클래스'이다.
- arrayClass[3]이라는 문장이 있을 때, []를 연산자라고 생각하면 arrayClass.operator[](3) 이렇게 해석할 수 있다.
``` C++
#include<iostream>
#include<cstdlib>
using namespace std;
class ArrayCalss{
private:
   int * arr;
   int arrLength;
public:
   ArrayClass(int len) : arrLength(len){
      arr = new int[len];
   }
   int& operator[] (int index){
      if(index<0 || index>=arrLength){
         cout<<"out of index"<<endl;
         exit(1);
      }
      return arr[index];
   }
   ~ArrayClass(){
      delete []arr;
   }   
};
int main(){
   ArrayClass arr(2);
   arr[0] = 0;
   arr[1] = 1;

   //arr[2] = 2;  out of index출력   
}
```
- 이렇게 굳이 배열을 클래스로 만드는 이유는 무엇일까?
    - C++의 배열은 경계검사를 하지 않아서 크기가 5인 int형 배열 arr이 있다고 할 때,
        - arr[-1]를 "arr의 주소 + sizeof(int) * -1"의 위치에 접근하는 것으로 해석하고,
        - arr[10]을 "arr의 주소 + sizeof(int) * 10"의 위치에 접근하는 것으로 해석하여 배열의 크기를 넘어서 접근할 수 있기 때문이다.
        - 이것이 유용할때도 있지만, 많은 상황에서 이러한 특징은 문제가 될 수 있기에 위의 예시처럼 배열 클래스를 만들어서 제한을 둔 것이다.
    - 이렇게 배열의 크기를 제한해줄수도 있지만, 대입 연산자를 private로 오버로딩해서 대입이 불가능하도록 만들수도 있다.

- 그럼 이제 배열 클래스를 const로 사용하는 법을 알아보자.
``` C++
#include<iostream>
#include<cstdlib>
using namespace std;
class ArrayClass{
private:
   int *arr;
   int arrLength;
   ArrayClass(const ArrayClass& arr){}
   Arraycalss& operator=(const ArrayClass& arr){}
public:
   ArrayClass(int len):arrLength(len){
      arr = new int[len];
   }
   int& operator[] (int index){
      if(index<0 || index>=arrLength){
         cout<<"out of index"<<endl;
      }
      return arr[index];
   }
   int operator[] (int index) const{
      if(index<0 || index>=arrLength){
         cout<<"out of index"<<endl;
      }
      return arr[index];
   }
   int GetArrayLength() const{return arrLength;}
   ~ArrayLength(){delete []arr;}
};
void ShowArrayData(const ArrayClass& ref){
   int len = ref.GetArrayLength();
   for(int i=0;i<len;i++)
      cout<<ref[index]<<endl;
}
int main(){
   ArrayClass arr(5);
   for(int i=0;i<5;i++)
      arr[i]=i;
   ShowArrayData(arr);
}
```
- 여기에서 봐야 할 점은, ShowArrayData의 매개변수가 const로 선언되었다는 것이다. ShowArrayData에서 배열의 값이 변하면 안되기 때문이다.
- 그 다음으로는 operator[] 함수가 2개 정의되었다는 것인데, 차이점으로는 const함수로 정의되었는지이다.
    - ShowArrayData의 매개변수 ref가 const이기때문에, ref의 const 함수만이 사용 가능하다.
    - 이때 operator[]를 아예 const형으로 만들면 배열에 저장이 불가능 해지는 등 다른 문제가 생길수도 있다. 그래서 기본 operator[]함수와 별개로 const형 operator[]를 오버로딩 한 것이다.
- 또한 반환형이 int&에서 int로 바뀌어 참조형에서 값을 바로 반환하는 형태로 정의되었다.

​
- 마지막으로 객체를 저장하기위한 배열 클래스를 정의해보자.
    - 객체를 저장하려면 1)객체의 주소 값을 저장하는 배열, 2)객체 자체를 저장하는 배열 이 둘 중 하나를 사용하면 된다.
``` C++
#include<iostream>
#include<cstdlib>
using namespace std;
class Point{
private:
   int xPos,yPos;
public:
   Point(int x=0,int y=0):xPos(x), yPos(y) {}
   friend ostream& operator<<(ostream& os, const Point& pos);
};
ostream& operator<<(ostream& os, const Point& pos){
   os<<"("<<pos.xPos<<", "<<pos.yPos<<")"<<endl;
   return os;
}

class ArrayClass{
private:
   Point *arr;
   int arrLength;
   ArrayClass(const ArrayClass& arr){}
   Arraycalss& operator=(const ArrayClass& arr){}
public:
   ArrayClass(int len):arrLength(len){
      arr = new Point[len];
   }
   Point& operator[] (int index){
      if(index<0 || index>=arrLength){
         cout<<"out of index"<<endl;
      }
      return arr[index];
   }
   Point operator[] (int index) const{
      if(index<0 || index>=arrLength){
         cout<<"out of index"<<endl;
      }
      return arr[index];
   }
   int GetArrayLength() const{return arrLength;}
   ~ArrayLength(){delete []arr;}
};
int main(){
   ArrayClass arr(3);
   arr[0] = Point(1,2);
   arr[1] = Point(3,4);
   arr[2] = Point(5,6);

   for(int i=0;i<arr.GetArrayLength();i++)
      cout<<arr[i];
}
```

- 위의 예시는 객체 자체를 저장하는 방식으로, 객체간의 대입 연산을 통해 객체를 저장한다.

``` C++
#include<iostream>
#include<cstdlib>
using namespace std;
class Point{
private:
   int xPos,yPos;
public:
   Point(int x=0,int y=0):xPos(x), yPos(y) {}
   friend ostream& operator<<(ostream& os, const Point& pos);
};
ostream& operator<<(ostream& os, const Point& pos){
   os<<"("<<pos.xPos<<", "<<pos.yPos<<")"<<endl;
   return os;
}

class ArrayClass{
private:
   (Point*)* arr;
   int arrLength;
   ArrayClass(const ArrayClass& arr){}
   Arraycalss& operator=(const ArrayClass& arr){}
public:
   ArrayClass(int len):arrLength(len){
      arr = new Point*[len];
   }
   (Point*)& operator[] (int index){
      if(index<0 || index>=arrLength){
         cout<<"out of index"<<endl;
      }
      return arr[index];
   }
   (Point*) operator[] (int index) const{
      if(index<0 || index>=arrLength){
         cout<<"out of index"<<endl;
      }
      return arr[index];
   }
   int GetArrayLength() const{return arrLength;}
   ~ArrayLength(){delete []arr;}
};
int main(){
   ArrayClass arr(3);
   arr[0] =new Point(1,2);
   arr[1] =new Point(3,4);
   arr[2] =new Point(5,6);

   for(int i=0;i<arr.GetArrayLength();i++)
      cout<<arr[i];
   delete arr[0];
   delete arr[1];
   delete arr[2];
}
```
- 이 방법은 객체의 주소 값을 저장하는 방법이다. 이렇게하면 new와 delete를 사용해야하지만 깊은복사인지, 얕은복사인지 머리쓸 필요가 없다.
- 상황에 따라 알맞은 방법을 선택하여 사용하면 된다.

## 3 그 이외의 연산자 오버로딩
1. new delete
    - new와 delete를 그냥 키워드로 알고있는 경우가 많은데, 이것들은 연산자이다. 그래서 연산자 오버로딩이 가능하다.
    - 하지만 지금까지 배운 오버로딩과는 조금 다른 방식으로 오버로딩해야한다.
    - 우선 new가 하는 일을 정리해보자.
        1. 메모리 공간 할당
        2. 생성자 호출
        3. 할당하고싶은 자료형에 맞게 반환된 주소 값의 형 변환
    - malloc은 프로그래머가 직접 형 변환을 해주어야 했지만, new를 사용하면 C++컴파일러가 알아서 형 변환을 해주고, 생성자를 호출해준다.
    - 그래서 new를 오버로딩할때는 메모리 공간의 할당만 오버로딩 할 수 있다.
        - new를 오버로딩할때는 다음의 규칙을 지키면 된다.
            - void* operator new(size_t size){ ... }
            - 반환형을 void*형으로 만들고, 매개변수는 size_t 형이어야한다. (size_t는 일반적으로 typedef unsigned int size_t 이다.)
    - 만약 Point *ptr = new Point(1,2); 이런 문장이 있으면 먼저 필요한 메모리를 계산한 뒤 operator new 함수를 호출한다.
    - delete는 다음의 규칙을 지킨다.
        - void operator delete(void* address){ ... }
    - 그럼 이제 예시를 보자.

    ``` C++
    #include <iostream>
    using namespace std;

    class Point{
    private:
        int xPos,yPos;
    public:
        Poitn(int x=0,int y=0) : xPos(x), yPos(y){}
        friend ostream& operator<<(ostream& os, const Point& pos);
        void* operator new(size_t size){
            cout<<"operator new"<<endl;
            void* address = new char[size];
            return address;
        }
        void operator delete(void* address){
            cout<<"operator delete"<<endl;
            delete[] adr;
        }
    };
    ostream& operator<<(ostream& os, const Point& pos){
        os<<"("<<pos.xPos<<", "<<pos.yPos<<")"<<endl;
        return os;
    }
    int main(){
        Point* ptr= new Point(1,2);
        cout<<*ptr<<endl;
        delete ptr;
    }
    ```
    ```
    operator new
    (1, 2)

    operator delete
    ```
    - 정상적으로 작동하는데, 의문점이 하나 있다.
    - Point클래스의 멤버함수로 delete를 오버로딩해서 사용하는데, 객체가 생성되기도 전에 operator가 실행되었다. 이것은 new와 delete가 멤버함수의 형태로 선언이 되었어도 static 함수이기 때문이다. 덕분에 객체가 생성되지 않았어도 사용이 가능한 것이다.

    - new와 delete 오버로딩에 대해서 하나만 더 정리하자면
        - Point* arr = new Point[3]; 이런 문장이 있듯이, new는 void* operator new[] (size_t size)이런 형태로 오버로딩이 가능하다.
        - 즉, void* operator new(size_t size){ ... }와 void* operator new[] (size_t size)를 따로 오버로딩해주어야한다.
        - delete도 마찬가지로 void* operator delete[] (void* adr) 이러한 형태가 따로 있다.


- 하지만 오버로딩 방식이 딱히 다르지는 않다. 그냥 new뒤에 []만 붙여주면 된다.
    ``` C++
   void* operator new(size_t size){
      cout<<"operator new"<<endl;
      void* address = new char[size];
      return address;
   }
   void* operator new[](size_t size){
      cout<<"operator new[]"<<endl;
      void* address = new char[size];
      return address;
   }
   ```

2. -> , *
    - ->와 *는 포인터 연산자이다.
    ``` C++
    #include<iostream>
    using namespace std;
    class MyNum{
    private:
        int num;
    public:
    MyNum(int n):num(n){}
        void ShowDate() {cout<<num<<endl;}

        MyNum * operator->(){
            return this;
        }
        MyNum& operator*(){
            return *this;
        }
    };
    int main(){
        Mynum num(10);
        num.ShowData();
        (*num) = 20;
        num->ShowData();
        (*num).Showdata();
    }
    ```
    - (\*num)=20;은 (num.operator*()) = 20;로, (num.operator*()).ShowData();로 해석할 수 있다.
    - num->ShowData()는 해석하면 num.operator->() ShowData();가 되어 잘 이어지지 않는데, num.operator->() -> ShowData();이렇게 ->를 하나 더 추가하여 해석한다.

3. 스마트 포인터
    - 스마트포인터는 포인터가 일을 하도록 만든 객체이다. 아까 배열 클래스처럼 특수한 기능을 위해 임의로 만든 객체이다.
    ``` C++
    #include<iostream>
    using namespace std;
    class Point{
    private:
        int xPos, yPos;
    public:
        Point(int x=0,int y=0):xPos(x),yPos(y){cout<<"생성자"<<endl;}
        ~Point(){cout<<"소멸자"<<endl;{
        void SetPos(int x,int y){
            xPos = x;
            yPos = y;
        }
        friend ostream& operator<<(ostream& os,const Point& pos);
    };
    ostream& operator<<(ostream& os, const Point& pos){
        os<<"("<<pos.xPos<<", "<<pos.yPos<<")"<<endl;
        return os;
    }
    class SmartPointer{
    private:
        Point* posPtr;
    public:
        SmartPointer(Point * ptr):posPtr(ptr){}
        Point& operator*() const{ return *posPtr);}
        Point* operator->() const{return posPtr);}
        ~SmartPointer(){delete posPtr;}
    };
    int main(){
        SmartPointer sptr1(new Point(1,2));
        SmartPointer sptr1(new Point(3,4));
        SmartPointer sptr1(new Point(5,6));
        cout<<*sptr1;
        cout<<*sptr2;
        cout<<*sptr3;

        sptr1->SetPos(10,20);
        sptr2->SetPos(30,40);
        sptr3->SetPos(50,60);
        cout<<*sptr1;
        cout<<*sptr2;
        cout<<*sptr3;
    }
    ```
    - 위의 예시에서 스마트포인터 객체는 new와 delete를 따로 사용할 필요 없이 생성과 소멸을 자동으로 처리해준다.

4. ()
    - 함수를 호출할 때 사용되는 ()도 연산자 오버로딩을 할 수 있다. 이렇게 하면 객체를 함수처럼 사용할 수 있다.

    ``` C++
    class MyClass{
    public:
        int operator()(const int& num1,const int& num2){ return num1+num2;}
    };
    int main(){
        MyClass m;
        cout<<m(2,3)<<endl;
    }
    ```
    - 이런식으로 말이다. 이렇게 함수처럼 사용 가능한 클래스를 'Functor' 또는 'Funciton Object'라고 부른다.
    - 쓸데없는것처럼 보이지만, 함수에 객체의 특징인 상속 개념을 도입하여 사용할 수도 있다. 최상위 객체에 virtual로 함수를 만들면 인자에 따라서 다양한 결과를 낼 수도 있다.