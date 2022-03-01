# C++언어 기초 #2 - 함수, 네임스페이스
- 프로그래밍 공부를 시작하면 어느 언어를 선택했든 "Hello World"라는 문장을 출력해보라 한다.
- 아무래도 출력이 가장 기본적이면서도 중요한 기능이기 때문에 맨 처음에 배우는 것 같다.
- 하지만 프로그래밍은 기본 지식이 없으면 이 간단한 문제도 해결할 수 없다. 그림판처럼 아무것도 몰라도 쓱쓱 그림을 그려낼 수 있는, 그런 종류의 기술이 아니다. 그래서 프로그래밍을 처음 배우는 사람이라면 소스코드를 그대로 베껴 써서 눈과 손이 익숙해진 뒤 나중에 코드를 하나하나 해석해 보는 것이 도움이 된다.

## 1 함수 오버로딩
- 함수 오버로딩은 함수의 이름은 같게 하되, 전달되는 인자를 다르게 하여 함수의 사용범위를 확장시키는 것을 말한다.
``` C++
#include <iostream>
void Print1(int a){
   std::cout<<"Print "<<a<<std::endl;
}
void Print1(int a,int b){
   std::cout<<"Print "<<a<<" "<<b<<std::endl;
}
int main(void){
   Print1(1);
   print1(1,2);
}
```
```
Print 1
Print 1 2
```
- 위의 예시를 보면 동일한 이름의 함수를 2개 정의하여 정상적으로 사용된 것을 볼 수 있다.
- 이것은 C에서는 불가능한데, 그 이유는 C++는 사용할 함수를 찾을 때 '함수의 이름'과 '매개변수'를 통해 함수를 찾지만 C는 그저 함수의 이름으로만 함수를 찾기 때문이다.


## 2 매개변수의 기본 값
- C++에서는 매개변수에 기본 값을 설정할 수 있다.
``` C++
#include <iostream>
void Print1(int a=10){
   std::cout<<"Print "<<a<<std::endl;
}
int main(void){
   Print1();  //Print 10 출력
}
```
- 예시를 보면 Print1의 매개변수에 int a=10 이렇게 설정이 되어있다. 이것은 Print1() 이런 식으로 인자를 전달하지 않으면 기본적으로 설정된 10을 전달하겠다는 의미이다. 그래서 결과적으로 Print10이 출력된다.
    - 이것은 그저 기본 값이기 때문에 만약 Print1(5)처럼 함수를 호출할 때 값을 전달해주면 정상적으로 Print5가 출력된다.
    - 매우 편한 기능이지만 주의할 점이 있다.
    ``` C++
    #include <iostream>
    void Print1(int a=10, int b){
        std::cout<<"Print "<<a<<" "<<b<<std::endl;
    }
    int main(void){
        Print1(,3);  //에러
    }
    ```
    - 이렇게 앞의 매개변수에 기본 값을 설정해놓으면 Print(,3)처럼 괴상하게 함수를 사용해야한다. 아니, 애초에 사용할수도 없다.
    - 제대로 값을 전달하기위해서는  '매개변수 값은 왼쪽부터 채워지고 디폴트(기본)값은 오른쪽부터 설정 가능하다'라고 알고있으면 된다.
    ``` C++
    #include <iostream>
    void Print1(int a, int b=5,int c=10){
        std::cout<<"Print "<<a<<" "<<b<<" "<<c<<std::endl;
    }
    int main(void){
        Print1(1);      //Print 1 5 10
        Print1(1,3);    //Print 1 3 10
        Print1(1,3,6);  //Print 1 3 6
    }
    ```
    - 음, 그런데 문제가 있다. 함수 오버로딩을 통해 함수를 다양하게 만들 수 있었는데, 그것과 충돌할수도 있지 않을까?
    ``` C++
    #include <iostream>
    void Print1(int a, int b=5,int c=10){
        std::cout<<"Print "<<a<<" "<<b<<" "<<c<<std::endl;
    }
    void Print1(int a, int b){
        std::cout<<"Print "<<a<<" "<<b<<std::endl;
    }
    int main(void){
        Print1(1,3);
    }
    ```
    - 이 상황에서, Print1(1,3)이 첫번째 Print1을 호출한 것인지, 두번째 Print1을 호출한 것인지 모르기에 에러가 발생한다.
    - 그러니 좋다고 막 쓰지 말고 찬찬히 생각해보고 쓰자

## 3 인라인 함수
- C++에서는 '인라인 함수'라는 것이 있는데, 매크로 함수처럼 함수를 호출하면 아예 함수의 내용으로 대체되는 것이다.
- 그럼 매크로 함수와 어떤 점이 다른걸까?
    - 매크로 함수는 #define MUL(x) ((x)*(x)) 이런식으로 정의를 했지만 인라인 함수는 일반 함수처럼 정의한다.
    ``` C++
    #include <iostream>
    inline int MUL(int x){
        return x*x;
    }
    int main(void){
        std::cout<<MUL(2)<<std::endl;   //4출력
    }
    ```
    - 앞에 inline만 적어주면 간단하게 만들 수 있다.
    - 하지만 단점이 있는데, 매크로 함수의 경우에는 자료형을 크게 신경쓰지 않아도 되지만 인라인 함수는 일반 함수처럼 자료형을 지정해야한다. 물론 아까 배운 함수 오버로딩으로 어느정도는 커버가 되겠지만 단점은 확실히 단점이다.

## 4 네임 스페이스
- 소프트웨어가 발전할수록 협업을 해야 할 일은 많아졌다. 그러다보니 혼자서 개발할때는 상관이 없지만 여러 프로그래머들이 하나의 프로그램을 개발할 때 꽤나 심각한 문제가 생겼다.
- A라는 사람이 MyFunction()이라는 함수를 만들었는데, B라는 사람도 MyFunction()이라는 함수를 만들어서 두 코드를 합친 것이다. 그냥 이름을 바꾸면 되지 않나? 싶기도 하지만 한 100명이 참여한 프로젝트에서 100명이 다 똑같은 이름의 함수, 변수를 만들어서 합치려 한다면 분명 머리아픈 문제가 확실하다.
- 이러한 문제를 해결할 수 있는 것이 '네임 스페이스'이다. 우리말로 하면 '이름 공간'인데, 쉽게 말해서 그 코드를 만든 사람이 누구인지 명시하는 것이다.
``` C++
#include <iostream>
namespace A{
   void MyFunction(){
      std::cout<<"A가 최고"<<endl;
   }
}
namespace B{
   void MyFunction(){
      std::cout<<"B가 최고"<<endl;
   }
}
int main(){
   A::MyFunction();
   B::MyFunction();
}
```
- 이렇게 네임 스페이스로 부분을 나누어 묶어주면 명확하게 누구의 어떤 함수인지 알고 사용할 수 있다.
- 우리가 std::cout을 쓸 때 처럼 ::(범위 지정 연산자)를 사용하면 된다.
``` C++
#include <iostream>
namespace A{
   void MyFunction(void);
}
int main(){
   A::MyFunction();
}
void A::MyFunction(){
   std::cout<<"A가 최고"<<endl;
}
```
- namespace안에 함수의 선언만 두고싶다면 위와 같이 함수를 정의할 때 A::를 붙여서 정의해주면 된다.
- 그런데 A, B 이렇게 만들어진 네임 스페이스도 엄청 큰 프로젝트에서는 중첩이될 수 있지 않을까? 동명이인이 있을수도 있지 않은가.
    - 그러면 네임 스페이스를 중첩해서 사용하면 된다. 

- 그런데 함수를 사용할 때마다 네임스페이스의 이름과 ::를 붙여야 한다는 사실이 너무나도 귀찮지 않은가?
    - 프로그래머들은 그런 것을 못 참기 때문에 또 해결방법을 만들었다.
    ``` C++
    #include <iostream>
    namespace A{
        void MyFunction(void);
    }
    int main(){
        using A::MyFunction;
        MyFunction();
    }
    void A::MyFunction(){
        std::cout<<"A가 최고"<<endl;
    }
    ```
    - 위와 같이 A의 MyFunction을 사용하겠다고 선언해주면 바로 MyFunction();이라 작성해도 정상적으로 실행된다.
    - 즉, std::cout 이렇게 사용하던 것도 using std::cout; using std::cin, using std::endl 이렇게 써주면 바로 cout, cin, endl 이렇게 사용할 수 있다는 것이다.
    - 하지만 이것도 함수 하나하나마다 using 문장을 써줘야 하니 귀찮을 수 있다.
    - 그럴때는 그냥 using namespace std; 이렇게 작성해주면 std네임스페이스 안에 있는 모든 것을 바로 사용할 수 있다.
        - 하지만 이렇게 하면 애초에 네임스페이스를 사용한 의미가 없어지기 때문에 잘 판단해서 사용하자.

- Tip) ::를 사용할 수 있는 방법이 하나 더 있는데, 똑같은 이름의 전역변수와 지역변수가 있는데 전역변수를 사용하려할때이다.
    ``` C++
    int val=1;
    int main(){
        int val=2;
        std::cout<<val<<std::endl;   //2 출력 (지역변수 val)
        std::cout<<::val<<std::endl; //1 출력 (전역변수 val)
    }
    ```
    - 위처럼 ::를 변수이름 앞에 붙여주면 전역변수 val을 사용할 수 있다.