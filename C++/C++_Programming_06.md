# C++언어 기초 #6 - 클래스
## 1 복사 생성자
- 지금까지 변수의 값을 복사하려면 int num2 = num1; 이런식으로 하면 됐다.
- 그런데 객체를 복사하려면 어떻게 해야할까?
``` C++
Character player2 = player1;
```
- 이렇게 하면 멤버 대 멤버 복사가 일어난다. player1의 health, speed값이 player2의 health, speed로 복사된다.
    - 이것은 객체에 '복사 생성자'가 있기에 가능하다.
``` C++
#include<iostream>
using namespace std;
class Character{
private:
   int health;
   int speed;
public:
   Character(int _h,int _s) : health(_h), speed(_s){
      //생성자
   }
   Character(const Character &copy) : health(copy.health), speed(copy.speed){
      //복사 생성자
   }
};
int main(){
   Character player1(100,10);
   Character player2 = player1;
}
```
- 위의 Character player2 = player1; 문장에서 Character클래스의 복사 생성자가 호출된다.
- copy라는 이름으로 Character객체를 참조하여 그 health와 speed값을 자신에게 복사한 것이다.
- 그런데 원래대로라면 Character player2(player1); 이렇게 써야하는 것 아닌가?
    - 그냥 Character player2 = player1;이라고 써도 되는 이유는 자동으로 Character player2(player1)로 변환이 되기 떄문이다.
    - 사실 우리가 int value1 = 10; 이렇게 사용하던 것도 int value1(10)이렇게 사용할 수 있다. 멤버 이니셜라이저를 사용할 때 처럼 말이다.
- 만약 Character palyer2 = player1; 이렇게 복사가 되는 것을 막고싶다면 복사 생성자 앞에 'explicit'이라는 키워드를 추가해주면 된다.
- 그러면 객체의 값을 복사하려면 항상 저렇게 복사 생성자를 만들어줘야할까? 그렇지도 않다.
    - 복사 생성자를 따로 만들어주지 않으면 '디폴드 복사 생성자'가 자동으로 만들어진다. 생성자가 있고 없고는 별개의 문제이다.

## 2 깊은 복사, 얕은 복사
- 그러면 복사 생성자가 자동으로 만들어지니 프로그래머가 따로 복사 생성자를 만들지 않아도 되겠네?
    - 그건 또 아니다. 왜냐하면 디폴트 복사 생성자는 '얕은 복사'만이 가능하기 때문이다.
``` C++
#include<iostream>
#include<cstring>
using namespace std;
class Character{
private:
   char* name;
   int level;
public:
   Character(char* _name, int _level){
      int len = strlen(_name)+1;
      name = new char[len];
      strcpy(name, _name);
      level = _level;
   }
   ~Character(){
      delete[] name;
      cout<<"소멸자"<<endl;
   }
};
int main(){
   Character player1("P1",10);
   Character player2=player1;
   return 0;
}
```
- 위의 코드를 실행하면 예상대로라면 "소멸자" 문장이 2번 찍혀야 한다. 하지만 결과는 1개만 나온다.
- 그 이유는 '얕은 복사'에서 찾을 수 있다. player2가 player1의 name과 level을 복사할 때, player2 name이 player1의 name의 글자만 복사해서 다른 메모리에 저장한 것이 아니라 해당 메모리를 참조하여 복사한 것이다.
    - 그래서 player2가 먼저 소멸되었다고 가정해보면, player2의 소멸자에서 name의 메모리를 해제하면 player1이 소멸될 때 이미 name의 메모리가 해제되어 문제가 발생한다.
    - 그러면 우리가 생각한대로 만들려면 어떻게 해야할까? '깊은 복사'를 하면 된다.
    ``` C++
    Character(const Character& copy){
       name = char[strlen(copy.name)+1];
       strcpy(name,copy.name);
       level = copy.level;
    }
    ```
    - 위처럼 복사 생성자를 따로 만들어서 객체를 복사할 때 객체의 name을 새로 만들어서 문자열만 복사하도록 만들어주면 된다.


## 3 복사 생성자 호출시점
- 이러한 복사 생성자는 언제 호출될까?
    1. 위처럼 새로운 객체를 만들어서 기존 객체의 멤버들을 복사할 때
    2. Call by Value방식의 함수에 인자로 객체를 전달할 때
    3. 객체를 참조형으로 반환하지 않고 그냥 반환할 때
- 우리가 주의깊게 봐야 할 곳은 2번과 3번이다.
``` C++
void MyFunction(Character myChar){
   //...
}
int main(){
   Character player1;
   MyFunction(player1);
}
mychar객체가 생성되면서 전달받은 player1을 복사한다.

mychar의 메모리가 할당되는 동시에 초기화한 것이다.

Character MyFunction(Character myChar){
   //...
   return mychar;
}
```
- 이 경우에, MyFunction을 호출하면 mychar객체가 생성되고, mychar을 반환할 때 객체가 생성된다.
- 반환을 할 때 왜 객체가 생성되는지 의아할수도 있는데, 값을 반환하려면 그 값을 위한 메모리공간이 할당되어서 저장된다.
- 반환할 때 만들어진 객체는 언제 소멸될까?
``` C++
#include<iostream>
using namespace std;
class Temporary{
private:
   int num;
public:
   Temporary(int n):num(n){
      cout<<"created "<<num<<endl;
   }
   ~Temporary(){
      cout<<"destroyed "<<num<<endl;
   }
   void ShowInfo(){
      cout<<"Num is : "<<num<<endl;
   }
};
int main(){
   Temporary(100);
   cout<<endl<<endl;
   Temporary(200).ShowInfo();
   cout<<endl<<endl;
   const Temporary &ref = Temporary(300);
   cout<<endl<<endl;
}
```
```
created 100
destroyed 100

created 200
Num is : 200
destroyed 200

created 300

destroyed 300
```
- 위에서 볼 수 있듯이 문장이 끝나면 임시객체는 바로 소멸된다. 하지만 문장이 끝나기 전 할 기능들은 다 하고 소멸된다.
- 그리고 참조자를 사용해서 참조하면 바로 소멸되지 않고 프로그램이 끝날 때 소멸된다.

​

​