# C++언어 기초 #11 - 연산자 오버로딩 1
- 지금까지는 함수의 오버로딩에 대해서만 배웠는데, 연산자도 오버로딩이 가능하다.
- int형은 원래 int형과만 더하기를 할 수 있는데, +에 오버로딩을 하면 int형과 float형도 더하기를 할 수 있는 그런 개념이다.

## 1 operator+
- 잠깐 저번에 만든 가상함수 예시를 보자.
``` C++
#include<iostream>
using namespace std;

class Point{
private:
   int xPos,yPos;
public:
   Point(int x=0,int y=0):xPos(x),yPos(y){}
   Point operator+(const Point &ref){
      Point pos(xPos+ref.xPos,yPos+ref.yPos);
      return pos;
   }
};
int main(){
   Point point1(1,2);
   Point point2(5,6);
   Point point3=point1.operator+(point2);   // point1과 point2의 x,y가 각각 더해져서 point3의 xPos=6, yPos = 8
   //Point point3 = point2.operator+(point1);  // 똑같은 결과
}
```
- 위의 예시에서 봐야할 것은 operator+ 함수이다. 이렇게 보면 딱히 특별해보이지는 않는다.
- 하지만 Point point3 = point1.operator+(point2);는 Point point3 = point1 + point2; 이렇게 바꿀 수 있다. 객체와 객체끼리 +로 덧셈이 가능해졌다.
- 하지만 왜 저렇게 바꿀 수 있는걸까? 그것은 C++에서 'operator'와 '연산자'를 묶은 이름을 가진 함수는 연산자만으로도 함수를 호출할 수 있도록 약속했기 때문이다.
- 그러니 point1 - point2 이런 문장이 있으면 point1.operator-(point2) 이렇게 해석할 수 있다.
- 위에서는 operator를 멤버함수로 만들어서 오버로딩했는데, 전역함수로도 오버로딩할 수 있다.
    - 대신 전역함수는 point1.operator+(point2) 이런식으로 호출이 불가능하니, operator+(point1,point2) 이렇게 호출해야한다.
    - 물론 point1+point2 이렇게 쓸 수도 있다.

- tip) 오버로딩이 불가능한 연산자
    - . (멤버 접근 연산자)
    - :: (범위 지정 연산자)
    - sizeof (바이트 단위 크기 계산)
    - static_cast (형변환 연산자)
    - const_cast (형변환 연산자)
    - .* (멤버 포인터 연산자)
    - :? (조건 연산자)
    - typeid (RTTI 관련 연산자)
    - dynamic_cast (형변환 연산자)
    - reinterpret_cast (형변환 연산자)
- tip2) 멤버함수 기반으로만 오버로딩이 가능한 연산자
    - = (대입 연산자)
    - [] (배열 접근 연산자)
    - () (함수 호출 연산자)
    - -> (멤버 접근을 위한 포인터 연산자)
- tip3) 주의사항
    - 연산자 본래의 의도를 벗어난 기능을 최소화하자 ( +인데 기능은 -를 한다던지, A+B를 A에 B를 더한 값을 저장하도록 만든다던지)
    - 연산자의 우선순위는 바뀌지 않음 (+와 * 의 우선순위가 바뀌지 않는다는 뜻)
    - 매개변수의 디폴트 값 설정 불가능

## 2 단항 연산자 오버로딩
- 단항 연산자는 ++, -- 를 말한다. 이런 것은 어떻게 오버로딩 하는 것일까?
    - 다른 연산자와 같이 operator++ 함수를 오버로딩한다.
- 멤버 함수로 오버로딩되면 num.operator++(); 이렇게, 전역 함수로 오버로딩되면 operator++(num); 이렇게 해석될 것이다.
``` C++
#include<iostream>
using namespace std;

class Point{
private:
   int xPos,yPos;
public :
   Point(int x=0;i,int y=0) : xPos(x), yPos(y){}
   Point& operator++(){
      xPos +=1;
      yPos +=1;
      return *this;
   }
   friend Point& operator--(Point &ref);
};
Point& operator--(Point &ref){
   ref.xPos -=1;
   ref.yPos -=1;
   return ref;
}
int main(){
   Point pos(1,2);
   ++pos;    // pos의 xPos가 2, yPos가 3
   --pos;    // pos의 xPos가 1, yPos가 2

   ++(++pos);    // pos의 xPos가 4, yPos가 5
   --(--pos);    // pos의 xPos가 1, yPos가 2

   return 0;
}
```
- ++(++pos)가 가능한 이유는  Point클래스에  operator++()함수를 정의할 때 Point&를 반환하겠다고 정의했기 때문이다.
- return *this에서 this는 객체 자신을 뜻한다. 그러니 ++pos가 한번 연산된 후에 다시 ++(pos)를 연산해야하는 것이다.
- [++(++pos) -> ++(pos.operator++())]
- operator++는 멤버함수로 오버로드되었지만, operator--는 전역함수로 오버로드 되었다.
- --pos는 operator--(pos) 이렇게 해석할 수 있다. 그래서 operator++와 비교하면 다른점이 꽤 있다.
- 어쨋든 --(--pos)는 [--(operator--(pos)) -> operator--(pos의 참조 값)] 이렇게 해석할 수 있다.

- 그런데 단항 연산자같은 경우는 값의 앞뒤로 존재할 수 있다. ++num1, num1++ 이런식으로 말이다.
    - 위의 예시는 전위 연산자를 오버로드 한 예시이다. 그렇다면 후위 연산자는 어떻게 오버로드 해야할까?
    ``` C++
    #include<iostream>
    using namespace std;

    class Point{
    private:
        int xPos,yPos;
    public :
        Point(int x=0;i,int y=0) : xPos(x), yPos(y){}
        void ShowPosition() const{
            cout<<xPos << "/"<<yPos<<endl;
        }
        const Point operator++(int){
            const Point retobj(xPos,yPos);
            xPos +=1;
            yPos +=1;
            return retobj;
        }
        friend const Point operator--(Point &ref,int);
    };
    const Point operator--(Point &ref,int){
        const Point retobj(ref);
        ref.xPos -=1;
        ref.yPos -=1;
        return retobj;
    }
    int main(){
        Point pos(1,2);
        Point pos2;

        pos2 = pos++;
        pos2.ShowPosiiton();
        pos.ShowPosition();

        pos2 = pos--;
        pos2.ShowPosiiton();
        pos.ShowPosition();

        return 0;
    }
    ```
    ```
    1,2
    2,3
    2,3
    1,2
    ```
    - 후위연산자는 ++를 나중에 더해주기에 pos를 복사한 retobj를 반환하여 대입해주고 xPos,yPos는 따로 연산해준다.
    - 또한  operator 함수의 매개변수에 난데없이 int가 추가되었다
        - 이것은 연산자 함수가 후위 연산자라는 것을 명시해주기위해 만든 약속이다.
    - 마지막으로 함수에 const를 붙여준 이유는 operator 함수의 반환으로 생성되는 임시객체를 const 객체로 생성하기 위함이다.
    - 이러면 반환된 pos객체의 값을 변경할 수 없게되고, pos객체를 통해서는 const 함수만 호출이 가능하게 된다.
        - 그래서 (pos++)++, (pos--)-- 같은 문장은 컴파일 에러가 발생한다.
        - operator 함수가 const로 선언되지 않았고, operator--는 매개변수 ref가 const로 선언되지 않았기 때문이다.
    - 왜 굳이 이 문장이 에러가 나게 만들었냐 하면, 후위 연산자는 마지막에 연산을 하기 때문에 pos++가 한번 끝났는데 다시 ++를 할 수 없기 때문이다. 위의 예시에서 pos2 = pos++; 이것이 pos2 = (pos++)++; 이렇게 바뀌면 pos2에 무엇이 저장되겠는가.


## 3 교환법칙 문제
- 교환법칙이란 'A+B의 결과가 B+A와 같다'는 법칙이다. A와 B의 순서를 바꾸어도 값이 변하지 않는다는 뜻이다. -같은 경우에는 성립하지 않지만 +와 * 연산자의 경우 교환법칙이 성립해야한다.
``` C++
Point operator*(int times){
   Point pos(xPos*times, yPos * times);
   return pos;
}
```
- 그런데 위의 예시를 보자. pos1\*3 이런식으로 연산자를 사용할텐데, pos1.operator*(3) 이것은 성립하지만 3\*pos1 이렇게하면 3.operator*(pos1)이 되니, 말이 안된다.
- 그러니 이것을 구현해줘야한다. 전역함수로 말이다.
``` C++
class Point{
private:
   int xPos,yPos;
public:
   Point(int x=0,int y=0):xPos(x),yPos(y){}
   Point operator*(int times){
      Point pos(xPos*times,yPos*times);
      return pos;
   }
   friend Point operator*(int times,Point& ref);
};
Point operator*(int times,Point& ref){
   return ref*times;
}
```
- 이렇게 정의해주면 pos*3을 사용하든 3*pos를 사용하든 똑같이 잘 작동한다.


## 4 cout , cin, endl
- 전위 연산자를 공부할 때 ++(++(++pos))이런 형태가 가능한 것을 볼 수 있었다. 그런데 우리는 이미 이러한 형태를 사용하고있었다.
- cout,cin,endl을 사용할때, cout<<"Hello"<<"World"<<endl; 이렇게 연속적으로 다음 키워드를 사용할 수 있었던 것은 <<가 operator<< 함수 오버로딩을 통해서 객체를 반환하여 다음 연산을 할 수 있었기 때문이었다.
``` C++
#include<iostream>
namespace mystd{
   using namespace std;
   class ostream{
   public:
      ostream& operator<< (char*str){
         printf("%s",str);
         return *this;
      }
      ostream& operator<< (char str){
         printf("%c",str);
         return *this;
      }
      ostream& operator<< (int num){
         printf("%d",num);
         return *this;
      }
      ostream& operator<< (ostream& (*fp)(ostream &ostm)){
          return fp(this);
      }
   };
   ostream& endl(ostream & ostm){
      ostm<<'\n';
      fflush(stdout);
      return ostm;
   }
   ostream cout;
}
int main(void){
   using mystd::cout;
   using mystd::endl;
   cout<<3.14<<endl<<123<<endl;
}
​```
- <<와 >>가 연산자  오버로딩이 가능하다는 것을 알아냈으니 아까 Point같은 객체가 있으면 xPos와 yPos를 한번에 출력해주는 << 연산자를 오버로딩해줄수도 있을 것이다.