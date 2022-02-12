# C++언어 기초 #4 - OOP
- C++에는 Class라는 강력한 기능이 있다. 그런데 class를 이해하려면 우선 struct(구조체)부터 이해하는 것이 편하다.
- 구조체는 C언어에서 이미 공부했지만 C의 구조체와 C++의 구조체는 다른 점이 또 있으니 한번 짚어보고 class를 공부해보자.

## 1 Struct
``` C
#include<stdio.h>
struct character{
   int health;
   int damage;
   int speed;
};
int main(){
   struct character player1,player2;

   player1.health=10;
   player1.speed =5;
   player2.health =20;
   player2.damage =3;

   printf("Player1 : "+player1.health+" / "+player1.speed+"\n";
   printf("Player2 : "+player2.health+" / "+player2.speed+"\n";
}
```
- C에서 우리는 이런식으로 구조체를 사용했다. 이것을 C++로 가져와보면 아래처럼 만들 수 있다.
``` C++
#include<iostream>
struct character{
   int health;
   int damage;
   int speed;
   
   void PrintInfo(){
      std::cout<<"Player : "<<health<<" / "<<speed<<std::endl;
   }
};
int main(){
   character player1;
   character player2;

   player1.health=10;
   player1.speed=5;
   player2.health=20;
   player2.damage = 3;

   player1.PrintInfo();
   player2.PrintInfo();
}
```
- 주목할만한 점은 player1,2를 선언할 때 struct character player1 이렇게 선언한게 아니라 character player1 이렇게 선언했다는 것이다.
    - struct라는 키워드를 빼기 위해서 C에서는 typedef를 사용하곤했는데, C++에서는 그러지 않아도 된다.
- 그리고 구조체 안에 함수를 만들어서 사용할 수 있다! 원래대로라면 구조체 값에 하나하나 .를 사용하여 접근한뒤 출력해야했지만 구조체 안에 함수가 있으니 매우 간편하면서도 생산적인 코드가 되었다.
- 그리고 원한다면 함수를 구조체 밖에서 정의할수도있다. namespace처럼 말이다.
    ``` C++
    #include<iostream>
    struct character{
        int health;
        int damage;
        int speed;
        
        void PrintInfo();
    };
    void character::PrintInfo(){
        std::cout<<"Player : "<<health<<" / "<<speed<<std::endl;
    }
    int main(){
        character player1;
        character player2;

        player1.health=10;
        player1.speed=5;
        player2.health=20;
        player2.damage = 3;

        player1.PrintInfo();
        player2.PrintInfo();
    }
    ```
    - 함수가 밖에서 정의되었는데도 character.health 이런식으로 접근하는 것이 아니라  health 이렇게 접근이 가능한 것을 볼 수 있다.
        - 대신 함수 이름 앞에 꼭 ::로 영역을 지정해주자
    - 추가적으로, 함수를 구조체 안에서 정의하면 함수를 inline으로 처리한다는 의미를 가지게 되는데, 함수를 밖으로 빼내면 그 의미가 사라지게된다. 그래서 만약 함수를 빼놓더라도 inline의 의미를 지키고싶다면 inline void character::PrintInfo(){...} 이렇게 inline함수라는 것을 명시적으로 넣어줘야한다.

## 2 Class
- 사실 위에서 만든 구조체는 C++의 class의 일종이다. 위의 struct키워드를 class로 바꾸면 구조체가 아니라 클래스가 된다. 
- 혼란스러울텐데, class와 struct의 차이점을 알아보자.
``` C++
#include<iostream>
struct character{
   int health;
   int damage;
   int speed;
};
int main(){
   character player1={10,3,5};
   character player2={20,2,6};
}
```
- 구조체는 이런식으로 선언과 동시에 구조체 내부의 값을 초기화할 수 있다. 하지만 여기서 struct를  class로 바꾸면 에러가 생긴다.
    - 그 이유는 class의 값에 접근제어 지시자가 붙지 않아 'private' 상태이기 때문이다.
    - 접근제어지시자는 public, private, protected가있다.
        - public : 모두에게 접근 허용
        - private : 클래스 내에서만 접근 허용
         -protected : 상속관계에 있는 자식클래스에서만 접근 허용 (상속은 나중에 배울것이니 패스)
    - 그러면 이제 값을 초기화 해보자.
``` C++
#include<iostream>
class character{
private :
   int health;
   int damage;
   int speed;
public :
   void InitializeCharacter(int _health,int _damage,int _speed);
   void PrintInfo();
};
void character::InitializeCharacter(int _health,int _damage,int _speed){
   health = _health;
   damage = _damage;
   speed = _speed;
}
void character::PrintInfo(){
      std::cout<<"Player : "<<health<<" / "<<speed<<std::endl;
}
int main(){
   character player1;
   character player2;

   player1.InitializeCharacter(50,10,3);
   player2.InitializeCharacter(100,50,1);

   player1.PrintInfo();
   player2.PrintInfo();
}
```
- health, damage, speed가 private로 선언이 되었기에 player1.health 이렇게 값에 접근할수가 없다.
    - 대신 클래스 내에 함수를 만들고 public으로 지정해서 클래스 밖에서도 클래스 내부의 값에 영향을 줄 수 있도록 만든 것이다.
- struct는 접근제어지시자가 없어도 구조체 내부의 값에 접근이 가능한데, class는 public이라고 명시해주지 않으면 접근이 불가능하다.
    - 즉, struct는 기본적으로 public으로, class는 기본적으로 private로 선언된다는 차이점이 있다.
    - 그런데 struct처럼 그냥 다 public으로 만들면 편하지 않을까? 뭐하러 구분을 해서 일을 더 귀찮게 만든걸까?
        - 이것은 C++에서도, 기본적으로 프로그래밍을 할때도 매우 중요한 문제 때문이다. 프로그램이 매우 복잡해지고 다른 프로그래머들과 협업을 해야한다면 어떤 매우 중요한 값은 변하지 않았으면, 다른곳에서 접근하거나 볼 수 없었으면 하는 경우가 생긴다. 그래서 private로 접근제어 지시자를 설정하고, const를 사용하고, namespace를 사용하는 것이다.

## 3 객체 지향 프로그래밍(OOP)
- C와 C++의 가장 큰 차이점은 C는 '절차 지향'이고 C++은 '객체 지향'이라는 특징이다.
- C는 위에서 아래로 쭉 훑어나가는 방식이라면, C++은 '객체(Object)'가 일련의 행동들을 해나가는 방식이라고 생각할 수 있다.
- 객체라는 것은 하나 이상의 정보를 가지고 하나 이상의 행동을 할 수 있는 묶음이다.
    - 자판기는 돈을 받으면 음료수를 반환하는 객체이고, 사람은 돈을 낼 수 있으며 음료수를 취득할 수 있는 객체이며, 음료수는 여러가지 영양소(정보)를 가지고있는 하나의 객체이다.
- 클래스 내부에 선언된 변수와 함수를 각각 '멤버 변수', '멤버 함수'라고 한다. 클래스를 구성하는 요소이기때문에 member라는 이름이 꼭 들어맞는다.


## 4 파일 분할
- 보통 C++에서 파일을 분할할때, 헤더파일에는 클래스의 최소한의 정보만을 남기고 cpp파일에서 클래스를 정의한다.
    - 이렇게하면 다른 파일에서 해당 클래스에 접근할 때 헤더파일의 '최소한의 틀'만을 보고도 접근이 가능한지 불가능한 지 알 수 있다.
    - 덕분에 체계적으로 클래스를 정리하여 나중에 코드가 매우 복잡해졌을때 어디가 문제인지 보다 확실하게 판단할 수 있다.

- !주의) inline함수는 cpp파일이 아니라 클래스의 선언이 있는 헤더파일에서 같이 정의하자.
    - -> 그 이유는 inline함수의 몸통 부분으로 아예 대체 되어야하기 때문에 컴파일러가 바로 inline함수의 몸통을 참조해야하기 때문이다. 
        - (컴파일러는 파일 단위로 컴파일을 하기에 A.cpp를 컴파일 할 때 B.cpp를 참조할 수 없다.)