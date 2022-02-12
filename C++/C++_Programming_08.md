# C++언어 기초 #8 - 상속
## 1 상속
- 상속은 친족 관계가 있는 사람들 사이에서 재산이라던가, 권리, 의무 등을 물려받는 제도이다.
- 그런데 C++에서도 이 상속관계가 존재한다.
- 저번에 '객체'에 대해서 배웠는데, 이 객체에 상속 관계가 있다. 라고 생각하면 편하다.
   - 기능의 처리를 실제로 담당하는 클래스를 가리켜 '컨트롤 클래스' 또는 '핸들러 클래스'라고 한다.
- 이런 상속 관계를 프로그래밍에서 어떻게 사용한다는 것일까? 예시를 들어보자.
   - 게임에 전사 캐릭터와 몬스터가 있다고 하자. 두개의 객체는 분명 다른 객체이기에 따로 만들어줘야한다.
   - 그런데 막상 게임을 만들다보면 귀찮은 점이 있는데, 캐릭터와 몬스터 둘 다 "공격","피격" 기능이 있어야 한다는 것이다. 또한  health,damage같은 변수들도 공통적으로 필요할 것이다.
   - 물론 만들어야 할 객체가 전사와 몬스터뿐이라면 괜찮겠지만, 도적, 마법사, 궁수 같이 직업이 다양해진다거나 몬스터의 종류가 많아진다고 하면 그때마다 객체를 처음부터 새로 만들어야할까? 공통적인 부분을 따로 빼내서 공유할수는 없을까?

- 그것을 가능하게 하는 것이 상속이다.
``` C++
#include<iostream>
using namespace std;

class Character{
private:
   int health;
   int damage;
public:
   Character(int _h,int _d) :  health(_h),damage(_d){}
   void Attacked(int _d){
      health-=_d;
      cout<<"Health :"<<health<<endl;
   }
};
class Warrior : public Character{
private:
   int swordIndex;
public:
   Warrior(int _h, int_d, int _l):Character(_h,_d){
      swordIndex= _l;
   }
   void AttackOfWarrior(){
      cout<<"Warrior의 Attack"<<endl;
   }
};
class Archer : public Character{
private:
   int bowIndex;
public:
   Archer(int _h, int_d, int _l):Character(_h,_d){
      bowIndex= _l;
   }
   void AttackOfArcher(){
      cout<<"Archer의 Attack"<<endl;
   }
};
int main(){
   Warrior warrior1(200,10,3);
   warrior1.Attacked(10);
   warrior1.AttackOfWarrior();

   Archer archer1(100,20,4);
   archer1.Attacked(20);
   archer1.AttackOfArcher();
}
```
- 위의 예시에서 나는 Character객체를 만들고  Warrior와 Archer가 Character를 상속받도록 만들었다.
- Character에는 Warrior와 Archer가 공통적으로 가져야 할 health, damage같은 멤버 변수와 Attacked같은 멤버 함수가 있다.
- Warrior와 Archer가 Character를 상속받은 덕분에 warrior1와 archer1을 통해 Character의 Attacked()함수를 호출할 수 있게되었다.
- 거기에 추가적으로 AttackOfWarrior, AttackOfArcher같은 함수를 통해 객체마다 특수한 기능을 하도록 만들었다.
   - 와 그러면 warrior1.health+=100; 이렇게 할수도 있겠네요? 그렇지는 않다.
   - Character에서 health, damage는 private로 선언이 되었기에 Character를 상속받은 Warrior, Archer에서 함부로 접근할 수 없다.
   - 대신 Character의 Attacked처럼 public함수를 통해 간접적으로 접근은 가능하다.
   - 근데 아무리 private라지만 자식 클래스에서도 접근이 불가능한 것은 너무 불편하지않나? 그것을 위해 protected 키워드가 있다.
      - 저번에 접근 제한 지시자에 private, public, protected가 있다 했었다. protected는 private처럼 클래스 외부에서 접근을 못하도록 하지만 해당 클래스를 상속한 클래스에서는 접근이 가능하다. 위의 예시에서 health, damage가 private가 아닌 protected로 선언이 되었다면 warrior1, archer1를 통해 접근이 가능했을 것이다.
   - 그리고 Warrior의 생성자에 Character의 생성자를 이니셜라이저로 호출했는데, 상속받은 자식 클래스에서 따로 Character생성자를 호출하지 않으면 부모 클래스의 void 생성자가 자동으로 호출된다. 즉, 자식 클래스를 선언하면 부모 클래스의 생성자가 무조건 호출된다.
      - 그리고 당연하게도 부모 클래스의 생성자가 먼저 호출되고 자식 클래스의 생성자가 호출된다.
      - 소멸자는 자식 클래스가 먼저 소멸되고 부모 클래스가 다음으로 소멸된다.(이건 당연하지는 않다. 하지만 부모클래스{자식클래스{ } } 이렇게 생각하면 좋다.
   - 그런데 우리가 warrior와 archer를 만들 때 뒤에 : public character 를 붙였다. 이것을 public으로 상속되었다고 말한다.
      - 여기서 public은 private와 protected로도 바꿀 수 있다.
      - 이건 좀 헷갈릴수도 있는데, protected로 상속하면 public으로 선언된 멤버들이 protected로 바꿔서 상속된다.
      - 그래서 만약 charcter에 public으로 int level; 이렇게 한 변수가 선언되었다고 하면, warrior에서 level을 protected로 상속받기에 main에서 warrior.level 이렇게 접근하려하면 에러가 발생한다. level이 protected여서 외부에서 접근할 수 없기 때문이다.
         - (부모 클래스에서 private로 선언된 멤버는 애초에 상속된 클래스에서 접근할수도 없다.)
      - 이와 같이 private로 상속하면 protected와 public으로 선언된 멤버들이 private로 바뀌어서 상속된다.
         - 이렇게하면 상속받은 멤버들이 warrior 클래스 내에서만 접근이 가능하도록 만들 수 있다.

​

​