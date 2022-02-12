# C++언어 기초 #7 - Friend, Static, Const
## 1 Const
- const로 상수화된 객체는 const 멤버 함수만 호출이 가능하다. 왜냐하면 멤버 함수중에 데이터를 수정하는 함수가 있을 수 있기 때문이다.
- const 멤버 함수는 같은 이름의 멤버 함수와 오버로딩이 가능하다.
``` C++
#include<iostream>
using namespace std;
class Character{
private:
   int level;
public:
   Character(int _l) : level(_l){}
   void PrintLevel(){
      cout<<"Level : "<<level<<endl;
   }
   void PrintLevel const(){
      cout<<"Const Level : "<<level<<endl;
   }
};
void CallPrintConst(const Character &p){
   p.PrintLevel();
}
int main(){
   Character player1(2);
   const Character player2(4);

   player1.PrintLevel();
   player2.PrintLevel();

   CallPrintConst(player1);
   CallPrintConst(player2);
}
```
```
Level : 2
Const Level : 4
Const Level : 2
Const Level : 4
```
- const함수를 오버로딩하면, const 객체를 통해 호출된 함수는 const 함수가, const가 아닌 객체를 통해 호출된 함수는 const가 아닌 함수가 호출된다는 것을 알 수 있다.

## 2 Friend
- Friend(친구)가 되면 자신의 속마음을 내비추기 마련이다. friend가 되면 private 멤버 함수에 접근이 가능하다.
- 대신 A라는 클래스가 B를 친구로 선언했다고 해서 B도 A를 친구로 생각하는 것은 아니다.
``` C++
#include <iostream>
using namespace std;

class B; //A가 A의 뒤에서 정의된 B를 friend로 만들고 싶어하니 먼저 B라는 클래스가 있다고 알려줌

class A{
private:
   int level;
public:
   A(int _l) : level(_l){}
   void PrintFriendLevel(const B &b){
      cout<<"Friend's level is "<<b.level<<endl;
   }
};
class B{
private:
   int level;
   friend class A;
public:
   B(int _l) : level(_l){}
};
int main(){
   B b1(10);
   A a1(12);
   a1.PrintFriendLevel(); //Friend's level is 10 출력
}
```
- 위의 코드는 B가 A를 friend로 선언한 예시이다. A는 B에게서 friend로 인정받았기에 B의 level에 접근할 수 있지만, B는 A의 정보를 알 수 없다. 
- 만약 B도 A의 private 멤버에 접근하고싶으면 다음과 같이 코드를 작성하면 된다.
``` C++
#include <iostream>
using namespace std;

class B; //A가 A의 뒤에서 정의된 B를 friend로 만들고 싶어하니 먼저 B라는 클래스가 있다고 알려줌

class A{
private:
   int level;
   friend class B;
public:
   A(int _l) : level(_l){}
   void PrintFriendLevel(const B &b){
      cout<<"Friend's level is "<<b.level<<endl;
   }
};
class B{
private:
   int level;
   friend class A;
public:
   B(int _l) : level(_l){}
   void PrintFriendLevel(const A &a){
      cout<<"Friend's level is "<<a.level<<endl;
   }
};
int main(){
   B b1(10);
   A a1(12);
   a1.PrintFriendLevel(); //Friend's level is 10 출력
   b1.PrintFriendLevel(); //Friend's level is 12 출력
}
```
- 이렇게 하면 A도 B의 친구이고, B도 A의 친구가 되어 서로 private 멤버들에 접근할 수 있다.
- friend는 함수에도 적용이 가능하다.
``` C++
#include <iostream>
using namespace std;
class B;
class A{
private:
   int level;
public:
   A(int _l) : level(_l){}
   void PrintFriendLevel(const B &b){
      cout<<"Friend's level is "<<b.level<<endl;
   }
};
class B{
private:
   int level;
public:
   B(int _l) : level(_l){}
   friend void A::PrintFriendLevel(const B&);
   friend void AddLevelToB(B&);  //이 문장에 이미 함수 선언이 포함되어있어서 따로 위에 선언할 필요 없음
};
void AddLevelToB(B &b){
   b.level ++;
   cout<<"B Level :"<<b.level<<endl;
}
int main(){
   B b1(10);
   A a1(12);
   a1.PrintFriendLevel(); //Friend's level is 10 출력
   AddLevelToB(b); // B Level : 11 출력
}
```
- 이처럼 B가 A클래스 자체를 friend로 선언하지 않고 A의 함수만 friend로 설정하여 자신의 정보에 접근 가능하도록 만들수도 있다.
- 또한 굳이 클래스 내부의 멤버 함수가 아니라 다른 함수도 friend로 설정하면 private 데이터에 접근이 가능하다.
- 와! 모두 private에 접근할 수 있구나! 그런데 그럴거면 public으로 만들면 되지 않을까?
    - private로 만든 이유는 정보은닉을 위한 것인데, 그러면 friend는 정보은닉을 파괴하는 기능 아닐까?
    - 여러가지 생각이 들어서 혼란스럽지만, friend도 결국 필요하기에 만들어진 것이다. 하지만 남용하면 정보은닉을 파괴하는 것 또한 맞다. 그러니 적절하게, 때에 맞게 사용해야만 한다.

​
## 3 Static
- 우리가 C에서 배운 static의 의미는 아래와 같다.
    1. 전역변수로 선언되었을 때, 선언된 파일 내에서 참조를 허용
    2. 함수 내에서 선언되었을 때, 한번만 초기화되고 프로그램이 종료될때 소멸된다.
``` C++
#include<iostream>
using namespace std;
class Character{
private:
   static int playerCount;
public:
   Character(){
      playerCount++;
      cout<<"현재 Character 수 :"<<playerCount<<endl;
   }
};
int Character::playerCount=0;
int main(){
   Character player1;
   Character player2;
   Character player2;
}
```
```
현재 Character 수 :1
현재 Character 수 :2
현재 Character 수 :3
```
- 위처럼 playerCount변수가 Character라는 클래스 내에서 한번 초기화 된 뒤 공유가 되어 Chracter수에 맞게 값이 증가하는 것을 볼 수 있다.
- 이 때 Character클래스 외부에서 0으로 초기화해준 이유는 playerCount가 객체가 생성될때마다 초기화되면 안되기 때문이다.
- 그런데 위에서는 static 변수를 private로 선언했는데, 이것을 public으로 선언하면 어떻게 될까?
    - public으로 선언된 static변수는 해당 클래스의 이름을 통해 다른 곳에서도 접근이 가능하다.
    ``` C++
    #include<iostream>
    using namespace std;
    class Character{
    public:
        static int playerCount;
        Character(){
            playerCount++;
        }
    };
    int Character::playerCount=0;
    int main(){
        Character player1;
        Character player2;
        Character player2;

        cout<<"현재 Character 수 :"<<Character.playerCount<<endl; //현재 Character 수 :3 출력
        cout<<"현재 Character 수 :"<<player2.playerCount<<endl; //똑같은 문장을 출력하지만, 이 코드보다는 위의 코드를 사용하자.
    }
    ​```
- static 키워드는 함수에도 적용이 가능하다.
``` C++
#include<iostream>
using namespace std;
class Character{
private:
   int password;
   static int playerCount;
public:
   Character(){
      playerCount++;
   }
   static void InfoPrinter(){
      //cout<<"Pass : "<<password<<endl; //이 문장은 에러 발생
      cout<<"현재 Character 수 :"<<playerCount<<endl;
   }
};
int Character::playerCount=0;
int main(){
   Character player1;
   Character player2;
   Character player2;

   Character::InfoPrinter(); // 현재 Character 수 : 3 출력
}
```
- 주의할 점이 있는데, InfoPrinter안의 cout<<"Pass : "<<password<<endl; 이 문장처럼, static 함수 안에 static이 아닌 멤버변수가 있으면 에러가 발생한다.
- static은 객체가 생성되기도 전에 호출이 가능한데, 객체가 없는데 멤버 변수가 있을리 만무하며, 객체가 만들어진 후에 호출되더라도 어떠한 객체에 접근을 해야 할 지 알 수 없기 떄문이다.
    - 그러니 const처럼 static 함수 안에는 static 멤버변수와 static 멤버 함수만 호출하도록 하자.

## 4 Mutable
- mutable은  '변할 수 있는'이라는 뜻을 가진 키워드이다.
    - 말 그대로 const(상수)를 파괴할 수 있다는 의미이다.
- mutable은 아주 위험한 키워드라서 많이 사용하지는 않지만 어떠한 기능을 하는지 간단하게 알아보자.
``` C++
#include<iostream>
using namespace std;
class Character{
private:
   int level;
   mutable int health;
public:
   Character(int _l,int _h) : level(_l), health(_h){}
   void PrintInfo() const{
      coust<<level<<" , "<<health<<endl;
   }
   void AddHealth() const{
      health+=10;
   }
};
int main(){
   Character player1(1,90);
   player1.PrintInfo(); // 1 , 90 출력
   player1.AddHealth();
   player1.PrintInfo(); // 1, 100 출력
}
```
- 위처럼 const함수인 AddHealth가 health의 값을 변화시키려 하는데도 에러가 없이 실행이 가능하다.
- 어떻게보면 아주 강력할수도 있겠지만 그만큼 위험한 키워드이다. 상황에 알맞게 사용하되, 되도록이면 쓰지 않도록 하자.