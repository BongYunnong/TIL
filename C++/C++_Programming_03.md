# C++언어 기초 #3 - Bool 자료형, 참조자, new와 delete
## 1 Bool 자료형
- 최근에는 C언어에도 bool 자료형이 추가되었지만 원래 bool자료형은 C++에서 새롭게 추가된 자료형이다.
- bool은 boolean.의 약자로, 참과 거짓을 표현할 수 있는 자료형이다.
- 표현할 수 있는 가짓수가 참(1)과 거짓(0)밖에 없기 때문에 1바이트만 사용한다.
    - (1,0이라고 하긴 했지만 정수 1,0은 4바이트를 사용하기에 엄연히 다르다고 볼 수 있다.)

- 사용법
    ``` C++
    #include<iostream>
    using namespace std;
    bool Exceed5(int tmpNum){
        if(tmpNum > 5)
            return true;
        else
            return false;
    }
    int main(void){
        bool exceed5=false;
        int inputNum;   
        
        cin>>inputNum;
        exceed5 = Exceed5(inputNum);
        if(exceed5)
            cout<<"Exceeded 5"<<endl;
        else
            cout<<"Not exceeded 5"<<endl;
        return 0;
    }
    ​```

## 2 참조자
- 참조자는 이름에서 알 수 있듯이 어떠한 변수를 참조하여 사용할 수 있다는 것이다.
- 조금 더 쉽게 말하자면 변수에 별명을 붙여서 변수가 가진 메모리에 별명을 통해 접근할 수 있다.
    ``` C++
    #include<iostream>
    using namespace std;
    int main(void){
        int originalVal=10;
        int &NickVal = originalVal;

        cout<<originalVal<<" / "<<NickVal<<endl;  //똑같이 10이 출력
        cout<<&originalVal<<" / "<<&NickVal<<endl;//똑같은 주소가 출력
        return 0;
    }
    ```
    - 위처럼 NickVal이 originalVal의 별명 역할을 해서 두개의 값이 똑같이 나온다. 만약 NickVal = 20;이런 문장이 있었다면 똑같이 20이 출력되었을 것이다.

- &때문에 포인터와 주소가 생각나는데, 자세히보면 사용하는 방식이 조금 다르다. 변수이름 앞에 &를 붙이고, 값에는 따로 붙여지는 것이 없다. 아래 예제를 보고 구분을 해보자.
    ``` C++
    #include<iostream>
    using namespace std;
    int main(void){
        int num=10;
        int *num_p = &num;
        int **num_p_p = &num_p;

        int &ref = num;
        int *(&ref_p) = num_p;
        int **(&ref_p_p) = num_p_p;
    }
    ```
    - \*와 &의의 순서가 좀 헷갈리긴하지만  int형, int*형, int**형이라고 생각하면 이해가 좀 쉽다.

## <주의사항>
- 참조자로 상수를 참조할수는 없다. (const int &ref처럼 상수 참조자를 사용하면 가능)
- 선언과 동시에 참조해야한다.(참조할 대상을 바꾸는 것 불가)
- 그런데 참조자를 영어로하면 무엇인지 아는가? Reference이다. 어디서 많이 들어본 것 같다.
    - Call by Value와 Call by Reference 함수를 배울 때 사용했었다.
    - 이 참조자를 사용해서 Call by Reference 함수를 만들 수 있다.
    ``` C++
    #include <iostream>
    using namespace std;

    void Add10ByReference(int &ref){
        ref+=10;
    }
    int main(void){
        int num1=10;
        Add10ByReference(num1);  // Call by Reference함수를 통해 num1에 10이 더해짐
        cout<<num1<<endl;        // 20출력
        return 0;
    }
    ```
    - 포인터를 통해 Call by Reference함수를 만들었을때는 함수을 정의할때 int*를 사용하고 호출할 때 &를 사용해 주소를 넘겨주었지만 참조자를 사용하면 저렇게 함수를 정의할 때 &를 사용해주면 되기때문에 편리하다.
    - 하지만 편리하다고 다 참조자를 사용하여 함수를 만들면 나중에 큰일이 일어날 수 있다.
        - 위의 함수는 Add10ByReference라고 함수의 의미를 정확하게 알려주었지만 복잡한 프로그램의 경우에는 함수안에서 엄청난 일이 벌어질 수 있다. 그럴때 해당 함수가 그저 값만을 받아서 원래의 값을 변형시키지는 않는 것인지, 주소 자체를 받아서 원래의 값을 변형시킬 수 있는 것인지는 아주 엄청난 차이이다. 이러한 관점에서 참조자를 사용한 함수를 남용하면 위험할 수 있다.
        - 물론 int const &ref 이렇게 const를 사용하여 값을 변경하지 못한다고 명시할 수 있긴 하지만, 어차피 호출할때는 모르는 것이며 원래의 값을 변경할 수 있다는 참조자의 장점이 사라지는 것이기에 나는 그리 좋은 방법이라고는 생각하지 않는다.

- 추가적으로, 참조자를 반환할수도있다.
``` C++
int& ReturnReference(int &ref){
   ref+=10;
   return ref;
}
```
- ref가 그냥 int로 반환이 되었다면 값을 반환하는 것이겠지만 int&로 반환이 되었기 때문에 int& tmpNum = ReturnReference(myNum); 이런식으로 새로운 참조자를 만들 수 있다.


## 3 new , delete
- C언어에서는 동적으로 메모리를 할당,해제할 수 있는 malloc과 free가 있었다.
- C++에서는 malloc과 free를 개선한 new, delete가 있다.
``` C++
#include<iostream>
#include<string.h>
using namespace std;

char* MakeStrAdr(int length){
   char *str = new char[length];
   return str;
}

int main(void){
   char* str = MakeStrAdr(20);
   strcpy(str,"Hello World");
   cout<<str<<endl;
   delete []str;
   return 0;
}
```
- malloc과 free를 사용할때는 형변환도 해주고 할당할 메모리의 크기도 바이트로 계산해서 사용해주어야하는데 new와 delete를 사용하니 딱 봐도 깔끔해보인다.

​

​

