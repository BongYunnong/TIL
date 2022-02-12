# C++언어 기초 #10 - 가상함수, 다중상속
## 1 가상함수 테이블
- 잠깐 저번에 만든 가상함수 예시를 보자.
``` C++
class Character{
   //...
public:
   void virtual PrintInfo(){
      cout<<"Character"<<endl;
   }
   void virtual CharacterFunc(){
      cout<<"CharacterFunc"<<endl;
   }
};
class Warrior: public Character{
   //...
public:
   void virtual PrintInfo(){
      cout<<"Warrior"<<endl;
   }
   void virtual WarriorFunc(){
      cout<<"WarriorFunc"<<endl;
   }
};
int main(){
   Character* character_p;
   character_p = new Character();

   Warrior* warrior_p;
   warrior_p = new Warrior();

   character_p->PrintInfo();
   warrior_p ->PrintInfo();
}
```
```
Character
Warrior
```
- character_p는 Chracter형이기에 Character클래스의 PrintInfo()를 실행하고, warrior_p는 Warrior형이기에 Warrior클래스의 PrintInfo()를 실행했다. 즉, 저장된 객체의 형태에 따라서 알맞은 함수를 찾아 실행했다.
- 그런데 컴퓨터가 어떻게 알맞은 함수를 찾아준 것일까?
    - 한개 이상의 가상함수를 포함한 클래스가 있으면 컴파일러가 '가상함수 테이블'이라는 것을 만든다.
    - 가상함수의 위치 정보를 저장하는 테이블인데, 아래의 표를 통해 이해해보자.

- [Character 클래스의 가상함수 테이블]
    | Key | Value |
    |:--:|:--:|
    |void Character::PrintInfo()|0x1024|
    |void Character::CharacterFunc()|0x2048|
- [Warrior 클래스의 가상함수 테이블]
    |Key|Value|
    |:-:|:-:|
    |void Warrior::PrintInfo()|0x3072|
    |void Character::CharacterFunc()|0x2048|
    |void Warrior::WarriorFunc()|0x4096|
- 이러한 테이블의 key와 value값을 통해서 character_p->PrintInfo()를 호출했을 때 0x1024에 있는 Character::PrintInfo()가 호출된다.
- warrior_p->PrintfInfo()를 호출하면 Character::PrintInfo()가 Warrior::PrintInfo()로 오버라이딩 되었기 때문에 0x1024의 PrintInfo가 아니라 0x3072의 PrintInfo()가 호출된다.
- 이러한 가상함수 테이블은 같은 클래스끼리 공유하고, 클래스의 멤버함수 또한 주소가 똑같다는 것을 통해 클래스끼리 공유된다는 것을 알 수 있다.


## 2 다중상속
- 지금까지는 상속을 하나의 객체에서 하나의 객체로만 하는것을 봐왔는데, 둘 이상의 클래스를 다중상속할 수 있다.
- 하지만 다중상속은 그 사용에 있어서 프로그래머들의 의견이 분분하다. 다중상속이 다양한 문제들을 가져올 수 있기 때문이다.
- 문제가 많다고는 하지만 그래도 배우기는 해야하니 아래 예시를 보자.
``` C++
class Character{
   //...
public:
   void CharacterFunc(){
      cout<<"Character"<<endl;
   }
};
class Player{
   //...
public:
   void PlayerFunc(){
      cout<<"Playable Character"<<endl;
   }
};
class Warrior: public Character, public Player{
   //...
public:
   void WarriorFunc(){ 
      CharacterFunc();
      PlayerFunc();
   }
};
int main(){
   Warrior* warrior_p;
   warrior_p = new Warrior();

   warrior_p ->WarriorFunc();
}
```
```
Playable Character
Character
```
- 딱히 더 배울게 없는게, 그냥 ,(컴마)를 사용해서 상속하고싶은 클래스를 연이어 집어넣어주면 된다.
- 이렇게 보면 엄청 편하고 좋은 기능인거 같은데 왜 문제가 많다고 하는 것일까?
    - 우선 위의 예시에서 Character와 Player의 CharacterFunc, PlayerFunc함수가 이름이 달라서 WarriorFunc에서 바로 호출할 수 있었는데,
    - Character와 Player 모두에게 PrintInfo라는 이름을 가진 함수가 있었다고 가정해보면 WarriorFunc에서 PrintInfo가 Character의 것인지, Player의 것인지 알 수 없다. 그래서 Character::PrintInfo(), Player::PrintInfo() 이렇게 어떠한 클래스의 함수인지 명시해줘야만한다.
    - 이것은 '모호성'을 띈다는 점에서 문제가 된다.
- 그리고 다음 예시를 보자
``` C++
class GameObject{
   //...
public:
   void GameObjectFunc(){
      cout<<"GameObject"<<endl;
   }
}
class Character : public GameObject{
   //...
public:
   void CharacterFunc(){
      GameObjectFunc();
      cout<<"Character"<<endl;
   }
};
class Player : public GameObject{
   //...
public:
   void PlayerFunc(){
      GameObjectFunc();
      cout<<"Playable Character"<<endl;
   }
};
class Warrior: public Character, public Player{
   //...
public:
   void WarriorFunc(){ 
      CharacterFunc();
      PlayerFunc();
      GameObjectFunc();
   }
};
int main(){
   Warrior* warrior_p;
   warrior_p = new Warrior();

   warrior_p ->WarriorFunc();
}
```
- 달라진 점은 GameObject라는 최상위 클래스를 만들어서 Character와 Player가 GameObject를 상속받도록 만든 것이다.
- 그러면 Warrior는 Character와 Player를 상속하니까 GameObject를 2번 상속받는것이 된다. 그러면 WarriorFunc에서 GameObjectFunc는 Character가 상속받은 GameObject의 GameObjectFunc인지, Player가 상속받은 GameObjectFunc인지 알수가 없다.
- 이처럼 다중상속을 사용하면 말도안되는 상황이 생긴다.
- 이를 해결하기 위해서는 '가상 상속'개념을 알아야한다.
``` C++
class GameObject{
   //...
public:
   void GameObjectFunc(){
      cout<<"GameObject"<<endl;
   }
}
class Character : virtual public GameObject{
   //...
public:
   void CharacterFunc(){
      GameObjectFunc();
      cout<<"Character"<<endl;
   }
};
class Player : virtual public GameObject{
   //...
public:
   void PlayerFunc(){
      GameObjectFunc();
      cout<<"Playable Character"<<endl;
   }
};
class Warrior: public Character, public Player{
   //...
public:
   void WarriorFunc(){ 
      CharacterFunc();
      PlayerFunc();
      GameObjectFunc();
   }
};
int main(){
   Warrior* warrior_p;
   warrior_p = new Warrior();

   warrior_p ->WarriorFunc();
}
```
- 여기서 추가해준 부분은 Character와 Player가 GameObject를 상속받을 때 virtual 키워드를 추가했다는 것이다.
- 이렇게 가상 상속을 해주면 Character와 Player가 동시에 GameObject를 상속하고 Warrior가 Character와 Player를 상속해도 결과적으로 하나의 GameObject만 상속되도록 할 수 있다.
- 만약 이 방법이 싫다면
    - WarriorFunc에서 GameObjectFunc(); 이렇게 호출하지 말고 아래처럼 접근할 클래스를 명시해주고 호출해주면 된다.
    ``` C++
    Character::GameObjectFunc();

    Player::GameObjectFunc();
    ```
    - 대신 가상상속을 하지 않으면 Warrior가 GameObject를 결과적으로 2번 상속하고 GameObject의 생성자도 2번 호출될 것이다.