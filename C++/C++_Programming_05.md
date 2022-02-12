# C++언어 기초 #5 - 클래스
## 1 정보은닉
- 저번에 클래스를 공부하면서 private, public같은 접근제어 지시자에 대해서 배웠다.
- 굳이 private를 사용하는 이유는 수정되지 않았으면 하는 값이 있기 때문이라 했는데, 잘 와닿지 않을 수 있으니 예제를 보면서 이해해보자.
``` C++
#include<iostream>
class userInfo{
public:
   int userIndex;
   int userPassword;
};
int main(){
   userInfo user1 = {1,-2412};
   userInfo user2 = {2,4241};
}
```
- userIndex와 password를 저장하기위한 클래스를 만들었는데, main에서 초기화 한 것을 보면 좀 이상하다.
    - user1의 password는 -2412가 된다. 비밀번호가 음수인 것도 있을 수 없는 일인데 말이다.
    - 하지만 에러가 뜨지 않을 것이다. 왜냐하면 아무런 제약이 없기때문이다.
    - 그래서 프로그래밍에는 제약이 필요하다. 에러가 생기는 것은 어떻게보면 잘못된 부분을 짚어주는, 고마운 일이라고 볼 수 있다.
    ``` C++
    #include<iostream>
    using namespace std;
    class userInfo{
    private:
        int userIndex;
        int userPassword;
    public:
        bool InitializeUser(int _index,int _pass){
            if(_pass <0)
                return false;
            userIndex = _index;
            userPassword = _pass;
            return true;
        }
        int GetIndex() const{
            return userIndex;
        }
        int GetPassword() const{
            return userPassword;
        }
        bool SetIndex(int _index){
            userIndex = _index;
            return true;
        }
        bool SetPassword(int _pass){
            if(_pass <0)
                return false;
            userPassword = _pass;
            return true;
        }
    };
    int main(){
        userInfo user1;
        if(user.InitializeUser(1,-4214))
            cout<<"잘못된 정보 입력"<<endl;
        else
            cout<<"정보 입력 완료"<<endl;
    }
    ```
    - 이렇게 멤버변수를 private로 선언하고 해당 변수를 수정하거나, 사용하는 함수를 따로 정의해주는 것을 '정보은닉'이라고 한다.
    - 그리고 Get~(), Set~() 같은 함수들을 액세스 함수라고한다. 
    - GetIndex(), GetPassword()를 보면 const로 정의되었는데, const함수는 함수 내에서 멤버변수에 저장된 값을 변경하지 않겠다는 것을 의미한다. 혹시라도 멤버변수 값을 변경하려하면 에러가 발생한다.
        - 게다가 const 함수 내에서 호출된 함수또한 const 함수이어야한다. 말 그대로 값을 변경할 여지를 아예 차단한 것이다.
        - 물론 처음에 const함수로 선언하는 것은 귀찮겠지만 그만큼 나중에 귀찮아질 일이 없어질 것이다.

## 2 캡슐화
- 객체지향 프로그래밍에서 정보은닉과 함께 중요한 원칙으로 받아들여지는 것이 '캡슐화'이다.
- 캡슐화는 말 그대로 비슷한 특성을 가진 기능들을 묶는 것을 의미한다. 예를 들면 이런 것이다.
- Player가 공격을 당하면 1)카메라가 흔들리고, 2)이펙트를 생성하고, 3)소리를 재생시킨다. 라고 할 때, 3가지의 기능을 따로따로 호출하기보다는 공격을 당했을 때 3개가 묶여서 호출되는 편이 좋다.
``` C++
#include<iostream>
using namespace std;
class Camera{
public:
   void Action() const {cout<<"Shake Camera"<<endl;}
};
class Effect{
public:
   void Action() const {cout<<"Create Effect"<<endl;}
};
class Sound{
public:
   void Action() const {cout<<"Play Sound"<<endl;}
};
class Player{
private:
   Camera cam;
   Effect effect;
   Sound sound;
public:
   void Attacked() const{
      cam.Action();
      effect.Action();
      sound.Action();
   }
};
int main(){
   Player p1;
   p1.Attacked();
}
```
- 실제로 이런식으로 하지는 않겠지만 대충 감을 잡기 위한 예제이다. 원래는 player가 공격받을 때마다 camera.Action(), effect.Action(), sound.Action() 이렇게 호출을 해줬어야겠지만 Player에서 Attacked()함수로 3개의 함수를 묶어주었기에 다음부터는 Attacked()함수만 호출하면 된다.
- 어떻게 보면 아주 간단한, 기초적인 기법이라고 볼 수 있겠는데, 캡슐화는 정말 어렵다. 어떨때는 CameraShake만 빠져야 할 때도 있고, 소리만 안 들려야 할 경우도 있을 것이다. 그런 상황에서 저렇게 Attacked에 3개의 기능을 다 넣은 것은 무용지물이 되어버린다. 그래서 캡슐화가 완벽하기는 정말 어렵다. 이것은 계속 프로그래밍을 해보면서 감을 익혀나가야 길러지는 역량이다.


## 3 생성자, 소멸자
- 지금까지 정보은닉을 위해서 멤버변수를 private로 만들고 초기화 하는 함수를 따로 만들어서 사용했는데, 이것은 많이 불편하다. 구조체처럼 선언과 동시에 초기화를 할 수 있었으면 참 좋을텐데 말이다.
- 그래서 클래스에는 생성자와 소멸자가 있다.
``` C++
#include<iostream>
using namespace std;

class UserInfo{
private:
   int userIndex;
   int userPassword;
public:
   UserInfo(int _index,int _pass){
      userIndex=  _index;
      userPassword = _pass;
   }
};

class Player{
private:
   int health;
   int power;
   UserInfo info;
public:
   Player(){
      health=100;
      power = 10;
   }
   Player(int _health){
      health= _health;
      power = 10;
   }
   Player(int _health, int _index, int _pass) : info(_index,_pass)
   {
      health= _health;
      power = 10;
   }
   ~Player(){
      cout<<"소멸자 호출"<<endl;
   }
};
int main(){
   Player p1;
   Player p2(200);
   Player p3(300,30);
}
```
- 위에 public으로 만들어낸 함수들이 '생성자'이다. 기본 함수랑 비슷하면서도 다른 점이 있는데, 클래스의 이름과 함수의 이름이 똑같고, 반환형이 없다는 것이 특징이다. 이러한 생성자는 객체가 생성될 때 한 번 실행된다. 생성되면서 private영역의 멤버변수들을 초기화시켜주며, 함수 오버로딩도 가능하기에 초기화가 매우 간편해졌다.
- 그런데 우리가 생성자를 몰랐을 때에도 클래스를 만들었었는데, 그때는 생성자가 없는 클래스를 만든것일까?
    - 그건 아니다. 생성자를 만들어주지 않으면 '디폴트 생성자'라는 생성자가 자동으로 만들어지고 호출이된다.
- Player(int _index, int _pass) : info(_index,_pass) 이것은 다른 생성자와 다르게 :뒤에 추가되는 것이 있는데, 이것은 'Member Initializer'라고 한다. 멤버변수 info를 Player를 생성하는 동시에 초기화시킬 수 있는 좋은 기능이다.
    - 굳이 멤버변수가 객체가 아니라도 사용 가능하다. int형 value1 이라는 멤버변수를 초기화하고싶다면 : value1(213) 이렇게 추가해주면 될 일이다.
    - 그런데 몸체에서 초기화를 하면 되지, 굳이 memeber initializer를 쓰는 이유가 있을까? 그것은 성능적으로 더 좋고, const 변수도 초기화가 가능하기 때문이다. const변수는 선언과 동시에 초기화가 이루어져야 하기 때문에 생성자에서 변경이 불가한데, initializer를 사용하면 선언과 동시에 초기화가 되기에 const 변수라도 초기화가 가능하다. ( 똑같은 과정으로, 참조자 또한 초기화가 가능하다.)
- 생성자랑 다르게 앞에 ~가 붙은 함수는 '소멸자'이다. 생성자가 클래스가 생성될 때 호출되는 것 처럼 소멸자는 클래스가 소멸할 때 호출된다.
    - 생성자와 같이 따로 소멸자를 만들지 않으면 디포트 소멸자가 생성된다.
    - 클래스가 소멸할 때 특별한 일을 처리하거나 클래스가 소멸할 때 메모리 공간을 해제해주기 위해서 사용하기도 한다.

​