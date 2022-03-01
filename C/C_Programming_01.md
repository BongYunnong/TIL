# C언어 기초 #1
## 1. printf("Hello World!");
- 프로그래밍을 처음 배울 때 시작하기 가장 좋은 언어가 C이다.
- 여러 분야에서 자주 쓰이는 C++이 C언어의 확장판이기도 하고, 기초를 탄탄하게 다지기에도 좋은 언어이기 때문이다.
- C, C++ 같은 것을 언어라고 칭하는 이유는 인간이 컴퓨터와 의사소통을 하기 위한 도구로 사용되기 때문이다. 컴퓨터는 0과 1로 만 되어있는데 우리가 011110100010 이런 거를 능숙하게 읽을 수가 없으니, 이것을 대신하기 위해 개발된 것이 프로그래밍 언어이고 C, C++,Python 같은 것이 프로그래밍 언어라고 칭해지는 것이다.
- 그렇다면 이 프로그래밍 언어를 컴퓨터가 어떻게 이해하는 것일까?
   - 그것은 "컴파일러"를 통해 이루어진다.
   - "컴파일러"는 C 같은 프로그래밍 언어로 작성된 코드를 컴퓨터가 이해할 수 있도록 기계어(0101010110)로 변환해 준다.
- 컴파일러의 변환이 끝나면 오브젝트 파일(.obj)이 생성되는데, 이것은 "Linker"에서 오브젝트 파일과 라이브러리 함수를 연결하여 실행파일(.exe)을 생성한다.
- 실행파일을 실행할 때는 주 기억장치에 "로더"가 로딩을 함으로써 CPU가 실행파일을 실행하도록 도와준다.

## 프로그램이 실행되기까지의 과정

1. 사람이 프로그램을 작성한다.
   - 소스 파일 생성
2. 컴파일러가 소스파일을 컴파일한다.
   - 오브젝트 파일 생성
3. 링커가 obj 파일과 라이브러리 함수 연결
   - 실행 파일 생성
4. 로더가 실행파일 로딩
   - 실행

## Hello World! 출력
- "Hello World!"라는 문장을 출력하는 것은 어떤 프로그래밍 언어를 배우던 볼 수 있는 아주 기본적인 과제이다.
- 하지만 프로그래밍을 모르는 사람에게는 이런 기본적인 과제도 아주 막막한 과제가 될 수 있다. 그러니 처음에는 그냥 코드를 그대로 따라서 써보고 나중에 하나하나 해석을 해보면 프로그래밍 언어에 익숙해지면 된다.

``` C
#include<stdio.h>
int main(){
   printf("Hello World!");
   return 0;
}
```
- 위의 코드가 C언어로 "Hello World"라는 문자열을 출력하는 코드이다. 이제 한 줄씩 해석을 해보자.
   - 첫 줄의 #include<stdio.h>는 stdio.h라는 헤더 파일을 사용하겠다는 의미이다.
   - .h라는 확장자는 Header file을 뜻하며, 표준 라이브러리 함수들을 정리해 놓은 파일이라고 이해하면 된다.
   - stdio.h는 standard Input Output의 줄임말로, 입출력을 가능하게 하는 함수들을 포함하고 있다. ex) printf()
   - #include에서 #은 "전처리기"를 뜻하며, 컴파일 전에 먼저 처리를 해야 하는 문장이라는 의미이다. 그리고 include는 <>안에 있는 헤더 파일을 사용하겠다!라는 뜻이다.
      - 그냥 간단하게 입출력 함수를 쓰겠다고 이해하면 된다.
   - 아래의 int main(){ ... }는 프로그램이 실행될 때 가장 먼저 호출되는 함수이다. main이라는 이름처럼 가장 중심이 되는 함수로, 이 함수가 없으면 실행이 안 된다.
   - printf() 함수는 괄호 안에 있는 값을 출력하는 함수이다.  그래서 위의 코드가 Hello World!를 출력하게 된다.
   - 그러면 맨 끝에 있는 세미콜론(;)은 왜 있는 것일까? C언어에서는 문장이 끝났다는 것을 알리기 위해서 세미콜론을 붙인다. 프로그래밍 초보자들이 이 세미콜론을 붙이는 것을 까먹어서 오류가 뜨는 경우가 많으니 주의해야 한다.
   - 마지막의 return 0; 문장은 0을 반환하고 프로그램을 끝내라는 뜻이다.

## Printf 심화
- 위에서 printf() 함수가 출력을 하는 함수라고 설명을 했다. 그런데 괄호 안에 있는 것이 무엇이든 그냥 출력을 해주는 것이 아니기도 하고, 여러 가지 기능을 추가할 수도 있다.
- 위의 코드를 실행하면 Hello World가 출력은 되긴 하는데,
   ```
   Hello World!Press any key to Continue...
   ```
   - 이런 식으로 "Press any key to Continue"가 바로 뒤에 붙어서 출력된다.
   - 이것을 보기 좋게 만들어주기 위해서는 Hello World! 뒤에  '\n'을 붙여주면 된다. printf("Hello World!\n") 이런 식으로 말이다.
   ```
   Hello World!
   Press any key to Continue...
   ```
   - 그러면 이런 식으로 Press any key to continue 부분이 개행된다. 
   - 특수문자 \n이 문자열에서 '개행' 기능을 해준 것이다.

- 이런 특수문자는 여러 개가 있는데, 그것은 아래와 같다.
   - \n : 개행
   - \t : 수평 탭
   - \v : 수직 탭
   - \\' : 작은따옴표
   - \\" : 큰따옴표
   - \\\\ : \\
   - \\b : 백스페이스
   - \a : 경고음
   - \f : 폼피드
   - \r : 캐리지 리턴


- 그런데 printf() 함수로 숫자를 출력하려면 어떻게 해야 할까?
   - 그것은 printf(3+5) 이것처럼 괄호 안에 숫자로 이루어진 값을 넣어주면 된다.
- 하지만 숫자와 문자를 함께 출력하려면?
   - 그럴 때 사용하는 것이 "서식 문자"이다.
   ``` C
   printf("%s : %d","값 ",10+4);
   ```
   - 위의 코드를 실행하면 아래와 같이 출력이 된다.
   ```
   값 : 14
   ```
   - %s에 "값 :"이라는 문자열이, %d에 10+4 (14)라는 정수형 값이 대입되었다.
   - 이처럼 %s,%d 같은 서식 문자를 통해 값들을 대입하여 더욱 다채로운 문자열을 출력할 수 있다.
   - 주의해야 할 점은 콤마(,)로 순서를 구분하여 차례대로 대입이 된다는 점이다.

- 서식 문자의 종류는 다음과 같다.
   - %d, %i : 10진수 정수
   - %x : 16진수 정수(양수)
   - %u : 10진수 정수(양수)
   - %o : 8진수 정수(양수)
   - %f, %lf : 10진수 실수
   - %c : 문자
   - %s : 문자열  
   - %e : e 표기법 실수
   - %E : E 표기법 실수
   - %g : 소수점 이하 자리 수에 따라 %f, %e 둘 중 하나를 선택
   - %G : 소수점 이하 자리 수에 따라 %f, %E 둘 중 하나를 선택
   - %% : % 기호 출력

- 위에 있는 특수문자와 같이 처음부터 다 외울 필요는 없다. 자주 사용하는 것은 %d, %f, %lf, %c, %s 이런 것들이다.


## Scanf로 입력받기
- 출력을 해봤으니 이제 입력을 배워보자. 입력은 printf()처럼 stdio.h에 있는 scanf()를 사용하면 된다.
- 그런데 scanf를 본격적으로 배우기 전에 변수에 대해 알 필요가 있다.
- 값을 저장하려면 메모리가 필요한데, 이를 위해 만든 임시 메모리 공간이 변수이다.
- 변수의 선언은 이렇게 하면 된다.
   ``` C
   int num1 =1;
   float num2 = 2.1f;
   char character1 = 'a';
   ```
- 이렇게 선언된 변수에는 값이 할당될 수 있고, 값을 변화시킬 수 있다.(더하기, 빼기 등등)
- 또한 값이 할당되었기 때문에 나중에 재사용이 가능하다.


- 하지만 변수를 선언할 때는 어떠한 규칙을 따라서 선언을 해야 한다.
   1. 함수 내에서 변수를 선언할 때, 가장 위에 변수를 선언해야 한다.
      - C가 위에서부터 아래로 실행하는 절차 지향 언어이기 때문에 가장 위에 변수를 선언해 줘야 한다.
   2. 특정한 문자를 변수 이름으로 사용해서는 안 된다.
      - 변수의 이름 맨 앞에 숫자를 사용하거나 특수 기호, 공백 문자를 사용하면 안 된다.
      - C언어에서 사용되는 키워드(if, int, float, for, else, ...)를 변수 이름으로 사용하면 안 된다.
   3. Tip
      - 변수의 이름은 최대한 의미를 알 수 있도록 지어야 한다.
      - 변수의 이름은 대소문자를 구분한다.


- 그리고 값의 형태가 다양하기에 변수의 형태도 여러 가지가 있다.
- 변수의 형태 [형태 : 메모리 / 표현 가능 범위 ]
   - char(문자) : 1바이트  /   -128~+127
   - short(정수) : 2바이트  /   -32768~+32767
   - int(정수) : 4바이트  /   -2147483648~+2147483647
   - long(정수) : 4바이트  /   -2147483648~+2147483647
   - float(실수) : 4바이트  /   1.2E-38~3.4E+38  (소수점 이하 6)
   - double(실수) : 8바이트  /   2.3E-308~1.7E+308  (소수점 이하 15)
   - long double(실수) : 10바이트  /   3.4E-4932~1.1E+4932 (소수점 이하 19)
- tip) unsigned가 앞에 붙으면 양수만 표현할 수 있는 대신 양수 부분에서는 더 많은 숫자를 표현할 수 있다.

 
- 그럼 이제 scanf를 사용해서 입력을 받아보도록 하자. 
   ``` C
   #include<stdio.h>
   int main(){
      int num1;
      printf("값을 입력하세요 :");
      scanf("%d",&num1);
      printf("값 : %d\n",num1);
      return 0;
   }
   ```
   - num1이라는 int형 변수를 선언하고, scanf("%d",&num1); 문장에서 앞에 &를 붙인 채로 사용되었다.
   - scanf 괄호 안에 있는 "%d"는 입력받은 값의 형태를 지정하는 서식 문자이고, &num1은 입력받은 값을 num1 변수에 저장하겠다는 뜻이다.
   - 나중에 더 자세하게 배우겠지만 변수 앞에 &가 오면 그것은 "변수의 주소"를 뜻한다. 변수는 값을 저장하기 위한 메모리 공간이라고 했는데, 그 공간의 주소라고 보면 된다.
   - 어쨌든 위의 코드는 num1에 사용자의 입력값을 저장해서 출력하는 코드이다.
   ```
   값을 입력하세요 : 3
   값 : 3
   press any key to continue...
   ```
   - 결과값은 이렇게 나오는데, 저 3은 사용자가 입력한 숫자이다.
   - 사용자가 3을 입력하면 num1 변수에 3이 저장되고, 그 아래 printf()에서 %d 서식 문자에 의해 num1의 값인 3이 출력된 것이다.

​
## 입출력 끝
- 이렇게  C언어의 기본인 입출력에 대해 알아보았다. 한 번에 너무 많은 것을 배워서 이해가 힘들 수도 있다.
- 하지만 아까 말했던 것처럼 처음에 헷갈리는 것은 어쩔 수 없다. 답은 익숙해지는 것 밖에 없다. 한 번에 모든 것을 외우고, 이해하려 하지 말고 천천히 여러 예제들을 보면서 감각을 키워나가도록 하자. 그러다 보면 어느샌가 자신도 모르게 직접 코드를 작성하고 있는 스스로를 발견할 것이다.