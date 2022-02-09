# C언어 기초 #15- 전처리기와 파일 분할 컴파일
## 전처리기
- C언어 기초 맨 처음에 #include와  #define을 설명하면서 전처리기에 대해 간단하게 설명했었다.
    - 컴파일 전에 먼저 처리를 해야 하는 것이라고 말이다.
    - 앞서 처리를 하는 장치라고 생각하면 된다.


- 이러한 전처리기 지시자의 종류는 다음과 같다.
    - #include   : 헤더 파일을 사용하겠다
        ``` C
        #include <stdio.h>   //printf, scanf같은거 사용 가능
        ```
    - #define     : 매크로 정의
        ``` C
        #include <stdio.h>
        #define PI 3.14
        int main(){
            double area, circum, radius;
            printf("반지름 입력 : ");
            scanf("%lf",&radius);
            
            area = PI * radius *radius;
            circum = 2 * PI * radius;

            printf("원 넓이 : %lf 원 둘레 : %lf",area,circum);
        }
        ```

- 매크로를 통해 함수를 정의할수도있다.
    ``` C
    #include <stdio.h>
    #define AREA (x) x*x
    int main(){
        double area, radius;
        printf("반지름 입력 : ");
        scanf("%lf",&radius);
        
        area = PI * AREA(radius);

        printf("원 넓이 : %lf ",area);
    }
    ```
    - 다만 함수랑은 조금 다른데, 매크로 함수는 그냥 문장을 바꿔치기한다는 느낌이다.
    - AREA(radius) 이것을 -> radius*radius 이렇게 바꾸는 것처럼 말이다.
    - 그래서 만약에 x+x 라고 정의한다면, PI * x + x가 되어서 PI * x^2가 아니라 PI*x +x가 될 것이다.


## #연산자와 ##연산자
- #연산자를 사용하면 매크로 함수의 인자를 문자열로 바꿀 수 있다.
``` C
#include <stdio.h>

#define OUTPUT1(a,b) a+b
#define OUTPUT2(a,b) #a "+" #b

int main(){
   printf("%d \n", OUTPUT1(12,34));
   printf("%s \n", OUTPUT2(12,34));
}
```
```
46
12+34
```

- ##연산자는 매크로 함수 안에서 토큰을 결합한다.
    - 토큰은 문법 분석의 단위를 의미한다.(숫자, 콤마, 연산자, 식별자 등)
``` C
#include <stdio.h>
#define OUTPUT(a,b,c) a ## b ## c
int main(){
   int a=2;
   printf("%d \n",a);
   printf("%d \n",OUTPUT(a,=,4));
   printf("%d \n",a);
}
```
```
2
4
4
```
- OUTPUT(a,=,4)를 통해 a=4가 실행되어서 두번째, 3번째 줄이 4로 출력된다.


## undef
- #undef      : 이미 정의된 매크로 해제
``` C
#include <stdio.h>
#define PI 3.14

int main(){
   printf("파이 값: %lf\n",PI);

   #undef PI

   #define PI 3.14159265

   printf("파이 값: %lf",PI);
}
```
```
파이 값 : 3.14
파이 값 : 3.14159265
```

## if
- #if, #elif, #else, #endif : 조건에 따라 컴파일
- #if는 if문과는 용도가 조금 다르다. 컴퓨터는 Linux, Window, Max처럼 다양한 운영체제가 있는데, 이러한 운영체제마다 제공하는 라이브러리나 함수 등이 다르다.
    - 그래서 한 운영체제에서 제대로 작동하는 것이 다른 운영체제에서 작동시켜보면 문제가 생기는 경우가 많다.
    - 이를 위해서 조건부 컴파일이 존재한다.
``` C
#include <stdio.h>
#define CODE 2
int main(){
   #if(CODE ==1)
      printf("윈도우");
   #elif(CODE ==2)
      prinf("안드로이드");
   #else
      printf("리눅스");
   #endif
}
```
```
안드로이드
```
- 위의 코드는 CODE를 2로 정의했기에 안드로이드가 출력된다.
- 임시로 CODE를 2로 정의했지만, 이것은 나중에 UNITY_EDITOR , ANDROID 이런 매크로로 상황에 맞게 바꾸면 된다.
- 보면 알겠지만, elif는 else if를 뜻하고, elif랑 else는 상황에따라 없어도 된다.

- #ifdef        : 매크로가 정의된 경우에 컴파일
- #ifndef      : 매크로가 정의되지 않은 경우에 컴파일
- #ifdef와 #infdef도 #if와 비슷하다.
``` C
#include <stdio.h>

#ifndef CODE
   #define CODE 2
#endif

int main(){
   #ifdef CODE
      printf("윈도우");
   #endif
}
```
- 위의 코드는 CODE의 값을 무엇으로 바꾸어도 무조건 "윈도우"가 출력된다.
- 그 이유는 #ifndef CODE를 통해 CODE가 없으면 CODE를 정의하도록 만든뒤에 main에서 CODE가 정의되어있으면 "윈도우"를 출력하도록 만들었기 때문이다.

​

## 파일 분할 컴파일
- 지금까지는 파일 하나로만 코드를 작성했었다. 그래서 프로그래밍을 처음 공부할 때 귀찮아서 파일을 나누지 않고 한 파일에만 코드를 다 작성해서 아주 복잡하고 더러워진 적이 많았다.
- 그리고 당연하게도, 프로그램은 코드 파일 하나만 사용하지 않고 여러 코드 파일을 연계해서 만들 수 있다.
- 파일을 분할하면 프로그램 생산성이 높아지고, 파일을 분할했기에 가독성이 높아지고, 유지보수가 용이하다.


- extern 키워드
    ``` C
    // test.c
    int num1 = 1;
    int num2 = 2;
    // test2.c
    #include <stdio.h>
    int main(){
        printf("%d ", num1+num2);
    }
    ```
    - 그렇다고 위의 예시처럼 무턱대고 다른 파일에 있는 데이터를 사용하려하면 에러가 생긴다.
    - 그래서 아래처럼 extern 키워드를 사용해서 외부에서 선언된 변수를 사용하겠다! 할 수 있다.
    ``` C
    // test.c
    int num1 = 1;
    int num2 = 2;
    // test2.c
    #include <stdio.h>
    extern int num1, num2;
    int main(){
        printf("%d ", num1+num2);
    }
    ```
    - 물론 함수도 외부에서 가져올 수 있다.
    ``` C
    // test.c
    void ADDNUM(int num1,int num2)
        printf("값 : ",num1+num2);
    // test2.c
    #include <stdio.h>
    extern void ADDNUM(int num1, int num2)
    int main(){
        printf("%d ", num1+num2);
    }
    ```
    - 만약에 extern키워드로 외부에서 사용할 수 없도록 막고싶다면, static으로 선언해주면 된다.


- 헤더파일
    - stdio.h같은 헤더파일을 직접 만들어서 #include하여 사용하면 된다.
    ``` C
    // myHeader.h
    extern double circle(int radius);
    // myHeader.c
    #define PI 3.14
    double circle(int radius){
        double result = 2 * PI * radius;
        return result;
    }
    // test.c
    #include <stdio.h>
    #include "myHeader.h"
    int main(){
        printf("원 둘레 : %lf ",circle(2));
    }
    ```