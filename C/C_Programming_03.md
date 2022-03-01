# C언어 기초 #3 - 데이터 형식, 자료형
## 자료형이란?
- 서식문자를 배울 때 이미 정수형, 실수형, 문자형 이라는 키워드를 봤을 것이다.
- 이전에 설명할 때는 그저 값의 형태라고만 말했었는데, 이것이 바로 자료형이다.

- 자료형 [형태 : 메모리 / 표현 가능 범위 ]
    - char(문자) : 1바이트 / -128~+127
    - short(정수) : 2바이트 / -32768~+32767
    - int(정수) : 4바이트 / -2147483648~+2147483647
    - long(정수) : 4바이트 / -2147483648~+2147483647
    - float(실수) : 4바이트 / 1.2E-38~3.4E+38 (소수점 이하 6)
    - double(실수) : 8바이트 / 2.3E-308~1.7E+308 (소수점 이하 15)
    - long double(실수) : 10바이트 / 3.4E-4932~1.1E+4932 (소수점 이하 19)

- 자료형이 세분화된 이유
    - 이렇게 자료형이 다양한 이유는 프로그래머가 표현하고싶은 값의 범위가 다 다르기 때문이다.
    - 예를 들어 정수 100을 표현하는데에는 4바이트(int)의 메모리를 할당하면 되는데 8바이트(double)를 사용하는 것은 낭비이다.

- sizeof()함수
    - 각 자료형의 크기를 알고싶으면 sizeof()함수를 사용하면된다.
    - 괄호 안에 char,int같은 자료형 이름이나 선언된 변수 이름을 넣으면 그에 맞는 자료형의 크기가 반환된다.

- signed와 unsigned
    - 자료형들은 보통 양수, 0, 음수를 다 표현할 수 있는데, 이것은 자료형 앞에 signed 라는 키워드가 생략되었기 때문이다.
    - 이와 반대로 unsigned를 자료형앞에 붙여주면 정수형의 음수 표현을 제한하는 대신 양수 표현 범위를 2배로 늘려준다.

- 오버플로우,언더플로우
    - 이렇게 표현 범위를 위한 기능들이 많은데 만약 표현 범위를 넘어가면 어떻게 되는 것일까?
    - 표현 범위를 초과하는 값은 오버플로우, 표현 범위 미만의 값은 언더플로우를 발생시킨다.
    - 만약 char 자료형에서  128(최댓값+1)을 표현하려하면 -128(최솟값)이 되고, 129(최댓값+2)의 값을 표현하려하면 -127(최솟값+2)이 된다.
    - 언더플로우는 반대로 생각하면 된다. -129(최솟값-1)을 표현하려하면 127(최댓값)이 되는 것 처럼 말이다.

- 문자형을 처리하는 방법
    - 그런데 char은 문자를 표현한다면서 왜 표현 범위가 -128~+127일까?
    - 그것은 컴퓨터가 문자를 바로 처리하지 못하고 0과 1로 처리하기 때문이다.
    - 숫자에 문자를 대입시켜서 컴퓨터가 문자를 처리할 수 있게 해야하는데, 그것이 ASCII 코드이다.
    - 인터넷에 ASCII 코드라고 검색해보면 어떤 숫자가 어떤 문자와 연결되어있는지 알 수 있다.

​
## 자료형의 변환
- 프로그래밍을 하다보면 정수형에서 실수형으로 변환하거나 문자형에서 정수형으로 변환하는 등 값의 형태를 변환해야 할 때가 많다.
- 이 자료형 변환에는 두가지 종류가 있는데, 하나는 '자동 형변환'이고, 다른 하나는 '강제 형변환'이다.

- 자동 형변환
    - 자동 형변환은 이름에서 예측할 수 있듯이 컴퓨터가 자동으로 자료형 변환을 해주는 것이다.
    - 아까 예시로 들었던 것을 다시 생각해보자. 정수 1과 실수 2.3을 더한다면 3.3이 나와야 한다. 이 떄 정수 1이 실수 1.0으로 자동 형변환이 된다. float형 변수에 정수 값을 대입하려 해도 정수가 실수로 자동 형변환이 된다.
    - 그런데 만약 실수 값을 int같은 정수형 변수에 담으면 어떻게 될까?
        - 3.14 를 int 자료형에 넣으면 .14가 손실되어 3만 저장이된다. 그래서 프로그래밍을 할 때 손실되는 값이 없는지 꼼꼼하게 체크해봐야한다.

- 강제 형변환
    - 그럼 컴퓨터가 자동으로 자료형을 변환해주는데, 프로그래머가 강제로 형변환을 왜 해야하는 것일까?
    - 예를 들어서 5 나누기 2를 해보자. 결과가 2.5가 되어야하는데, int형인 5와 2의 값을 계산해서 실수형 변수에 저장해보면 결과가 2가된다. 5/2에서 이미 0.5가 손실된 상태로 2가 실수형 변수에 저장되는 것이다.
    - 이럴 때 5나 2를 담은 변수 앞에 (double)을 붙여서 강제로 형변환을 해준다.
    ``` C
    int num1=5;
    int num2=2;
    double result;
    int main(){
        result = (double)num1/num2;
        //num1/(double)num2도, (double)num1/(double)num2도 가능하다
        return 0;
    }
    ```
    - 위의 코드에서 num1 하나에만 (double)을 붙여준 이유는 정수형과 실수형의 연산을 하면 정수형이 자동으로 실수형으로 형변환이 되기 떄문이다.