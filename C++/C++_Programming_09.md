# C++언어 기초 #9 - 다형성
## 1 객체 포인터
- 객체도 나름의 변수이니 객체 포인터도 존재한다.
``` C++
class Character{
   //...
};

int main(){
   Character* character_p;        //Character객체 포인터
   character_p = new Character(); //동적으로 할당
}
```
- 그런데 여기서 놀라운 점은, 객체 포인터는 자식 클래스도 가리킬 수 있다는 것이다.
``` C++
class Character{
   //...
};
class Warrior: public Character{
   //...
};
class SwordMaster: public Warrior{
   //...
};
int main(){
   Character* character_p;        //Character객체 포인터
   character_p = new Warrior(); //Character의 자식 객체인 Warrior도 가리킴

   Character* character_p2;
   character_p2 = new SwordMaster(); // Warrior의 자식 객체인 SwordMaster도 Character를 통해 가리킬 수 있다.
}
```
- 이것이 가능한 이유는 Warrior도, SwordMaster도 Character라는 범주에 들어갈 수 있기 때문이다.
- 반대로 Warrior* warrior_p; 이렇게 만들어놓고 warrior_p = new Character();라고 하면 안된다.
    - warrior가 character일수는 있지만, character가 warrior일수는 없기 때문이다. 포함관계를 생각해보면 편하다.
    - (아니면 Warrior의 멤버에 접근하고싶을 때 Character가 Warrior의 멤버를 모두 가지고있지 않다는 사실을 이해해보자.)

## 2 함수 오버라이딩
- 이쯤에서 함수 오버라이딩을 배워보자. 이름이 아마 어디서 본거같을텐데, 함수 오버로드와는 전혀 다른 것이다. 헷갈리면 안된다.
    - 함수 오버로드는 같은 이름의 함수에서 인자를 바꾸어서 다양하게 활용 가능하도록 만드는 것이었고,
    - 함수 오버라이딩은 B가 A를 상속했을 때, A에 있는 함수의 이름, 형태와 같은 함수를 B에서 수정하여 사용할 수 있게 만들어준다.
``` C++
class Character{
   //...
public:
   void PrintInfo(){
      cout<<"Character"<<endl;
   }
};
class Warrior: public Character{
   //...
public:
   void PrintInfo(){
      Character::PrintInfo();
      cout<<"Warrior"<<endl;
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
Character
Warrior
```
- 우선 1번째 줄과 3번째 줄을 보면 character_p의 PrintInfo()와 Warrior_p의 PrintInfo가 호출된 것을 볼 수 있다.
- 여기서 2번째 Character가 출력된 이유는 내가 Warrior클래스의 PrintInfo함수에 Character::PrintInfo(); 문장을 넣었기 때문이다.
- 이렇게 [부모 클래스의 이름 :: 원하는 함수 이름()]을 사용하면 부모 클래스의 오버라이딩된 함수를 호출할 수 있다.
``` C++
class Character{
   //...
};
class Warrior: public Character{
   //...
public:
   void PrintInfo(){
      Character::PrintInfo();
      cout<<"Warrior"<<endl;
   }
};
int main(){
   Character* warrior_p = new Warrior();

   warrior_p ->PrintInfo();
}
```
- 그러면 위의 코드는 정상적으로 작동할까? 당연히 될거같지만 그렇지는 않다.
    - 우리가 Warrior객체를 동적으로 Character 객체 포인터에 할당했는데, 결과적으로는 Character라는 박스에 넣은 것이므로 Character가 아니라 Warrior 고유의 멤버는 호출할 수 없다.
    - 같은 맥락으로, Character* warrior_p = new Warrior(); 이렇게 정의해놓고 Warrior* warrior_p2 = warrior_p; 이렇게 코드를 작성해도 에러가 생긴다. 이미 warrior_p는 Character 객체라고 인식이 된 상태이기에, 이것을 다시 Warrior객체로 받아들일수가 없는 것이다.
    - 반대로 Warrior * warrior_p = new Warrior(); 이렇게 정의하고 Character* character_p = warrior_p; 이렇게 작성하는 것은 문제없다.
    - 그러니 어떠한 형태의 포인터에 객체를 저장할 지 적당히 고민해봐야 할 것이다.

## 3 가상함수
- 그런데 우리가 함수 오버라이딩을 통해서 해당 클래스에 맞게 함수를 수정해주었는데, 결국 객체를 저장하는 포인터 변수의 형태에 따라서만 사용할 함수가 결정된다는 것은 조금 이상하다.
- 이런 문제를 해결할 수 있는 것이 가상함수이다.
``` C++
class Character{
   //...
public:
   void virtual PrintInfo(){
      cout<<"Character"<<endl;
   }
};
class Warrior: public Character{
   //...
public:
   void virtual PrintInfo(){ // virtual 키워드를 굳이 쓰지 않아도 virtual함수가 됨
      cout<<"Warrior"<<endl;
   }
};
int main(){
   Character* character_p;
   character_p = new Warrior();

   Warrior* warrior_p;
   warrior_p = new Warrior();

   character_p->PrintInfo();
   warrior_p ->PrintInfo();
}
```
```
Warrior
Warrior
```
- Character포인터 변수인 character_p에서 PrintInfo를 호출했는데  Warrior가 출력되었다.
- 즉, 가상함수를 사용하면 포인터변수의 형태에 따라서 사용할 함수가 정해지는 것이 아니라, 그곳에 저장된 객체의 형태에 따라서 사용할 함수가 정해진다.
- 저장된 객체의 형태에 따라 사용할 함수가 정해지기에, 기초 클래스로 묶인 배열에 일괄적으로 함수를 호출하기에 매우 편리하다.
- 이것은 C++의 객체지향의 특성인 "다형성"을 만들어주는 아주 중요한 개념이다. 똑같은 모습의 코드도 경우에 따라서 결과를 다르게 할 수 있다는 장점은 프로그래밍을 하면서 만나는 다양한 문제들을 해결할 수 있다.​
- 여기서 조금 추가하자면, virtual 키워드가 필요한 대상이 하나 더 있다. 그건 바로 소멸자이다.
    - Character* character_p = new Warrior(); 이렇게 작성하고, 나중에 delete character_p; 한다면 Character 포인터 변수로 저장이 되었으니 Character의 소멸자가 호출되어 Warrior의 소멸자가 호출될 수 없다.
    - 그러니 virtual ~Character(){...} 이렇게 가상함수로 만들어주어서 저장된 객체의 형태에 따라 소멸자가 호출되게 만들어주면 된다.
    - 이렇게 만들어주면 해당 소멸자가 호출된 후에도 부모 클래스의 소멸자가 순차적으로 호출될 것이다. 


## 4 추상 클래스
- 그런데 상속 클래스를 만들다보면 기초 클래스를 객체로 생성할 일이 없어질때가 있다.
- 직업이 전사,마법사,궁수 이렇게 3개가 있고, 애초부터 직업을 정할 수 있도록 한다면 그 상위 클래스인 "인간" 클래스는 따로 객체를 생성할 필요가 없다. 이러한 상황에서 인간 클래스는 추상 클래스로 만들 수 있다.
``` C++
class Character{
   //...
public:
   void virtual PrintInfo() const = 0; //순수 가상함수
};
class Warrior: public Character{
   //...
public:
   void virtual PrintInfo(){ // virtual 키워드를 굳이 쓰지 않아도 virtual함수가 됨
      cout<<"Warrior"<<endl;
   }
};
int main(){
   Warrior* warrior_p;
   warrior_p = new Warrior();
   warrior_p ->PrintInfo();
}
```
- 위의 코드에서 Character의 PrintInfo()는 순수 가상함수로, 함수인데도 몸통 부분이 정의되지 않았다.
- 0을 대입하는 이유는 명시적으로 몸통 부분을 정의하지 않았다는 것을 알리기 위함이다.
- 이렇게 정의된 Character를 객체로 만들려고 Character* character_p = new Character();라고 코드를 작성하면 컴파일 에러가 발생한다.
    - 덕분에 쓸데없이 가상함수를 객체로 만들 일이 없어진다! 이렇듯 가상함수는 실수를 막을 수 있는 장점이 있다.
    - 또한 PrintInfo함수는 virtual 함수로의 기능을 톡톡히 할 수 있기에 더욱 좋다.
- 정리하자면 추상 클래스(abstract class)는 완전하지 않은, 객체 생성이 불가능한 클래스이다.

​
## 5 참조자
- 지금까지는 포인터와 상속의 관계에 대해 알아보았는데, 포인터를 참조자로 바꾸면 그대로 적용이 된다.
``` C++
class Character{
   //...
public:
   void virtual PrintInfo(){
      cout<<"Character"<<endl;
   }
   void CharacterFunc(){
      cout<<"CharacterFunc"<<endl;
   }
};
class Warrior: public Character{
   //...
public:
   void virtual PrintInfo(){ // virtual 키워드를 굳이 쓰지 않아도 virtual함수가 됨
      cout<<"Warrior"<<endl;
   }
};
int main(){
   Warrior warrior_p;
   
   Character& characterRef = warrior_p;
   characterRef.CharacterFunc();
   characterRef.PrintInfo();
}
```
```
CharacterFunc
Warrior
```
- Character 형태의 참조자이지만 virtual 함수이기에 Warrior클래스의 PrintInfo가 호출된 것을 볼 수 있다.