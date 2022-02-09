# C언어 기초 #9 - 포인터와 함수
## Call by Value와 Call by Reference
- 함수에는 두가지 방식이 있다. Call by Value와 Call by Referece 방식이다.
- Call by Value는 어떠한 값을 복사하여 함수를 호출하는 방법이고, Call by Referece는 주소를 참조해서 함수를 호출하는 것이다.

- 똑같은거 아닌가? 싶다면 다음 예제를 보자
    ``` C
    #include <stdio.h>

    int add2Func(int param){
        param += 2;
        return param;
    }
    int main(){
        int num1=1;

        printf("%d \n", add2Func(num1);
        printf("%d \n", num1);
    }
    ```
    ```
    3
    1
    ```
    - 간단하게 생각해보면 add2Func에서 값에 2를 더해주었으니까 num1을 출력할때도 3이 출력되어야한다.
    - 그런데 결과를 보면 원래 num1의 값인 1이 출력된다.
    - 그 이유는 함수가 num1자체를 참조한것이 아니라 num1의 값인 1만 복사해서 사용했기 때문이다.
    - 그래서 첫째줄은 1에 2를 더한 3이 출력되는 것이고 num1은 그대로 1이 출력되는 것이다.

- num1자체에도 함수의 효과를 적용시키고싶다면
    ``` C
    #include <stdio.h>

    int add2Func(int param){
        param += 2;
        return param;
    }
    int main(){
        int num1=1;
        num1 = add2Func(num1);
        printf("%d \n", num1);
    }
    ```
    - 이렇게 반환되는 값을 num1에 넣어주면 된다.
    - 하지만 이것은 너무나도 일차원적인 방법이라서 함수가 조금만 더 복잡해지면 사용할 수 없을 수 있다.

- 그래서 우리는 Call by Reference 방식을 배워야한다.
    ``` C
    #include <stdio.h>

    int add2Func(int* param){
        *param += 2;
        return *param;
    }
    int main(){
        int num1=1;

        printf("%d \n", add2Func(&num1);
        printf("%d \n", num1);
    }
    ```
    ```
    3
    3
    ```
    - 이렇게 매개변수를 포인터로 설정하고 변수의 주소를 넘겨주면 함수가 변수의 주소를 참조할 수 있기에 변수 자체의 값을 변경해줄 수 있다.
    - 생각을 해보면 우리가 값을 입력받을 때 scanf()를 사용했을때에도 &를 사용했었다. 주소를 넘겨주었기에 값 저장이 제대로 이루어졌던 것이다.

## 함수 활용
- 지금까지는 함수가 값만 반환해주었지만 당연히 주소를 반환할 수도 있다.
    ``` C
    #include <stdio.h>
    int* ReturnReference(){
        int num1;
        scanf("%d",&num1);
        return &num1;
    }

    int main(void){
        int* p = NULL;
        p = ReturnReference();
        printf("%d \n",*p);
        return 0;
    }
    ```
    - 위의 코드는 사용자가 입력한 숫자를 출력하기는 한다. 하지만 경고가 발생한다.
    - 왜냐하면 ReturnReference함수에서 num1의 주소를 넘겨주는데 num1은 지역변수라 returnReference가 종료되면 메모리가 소멸되기 때문이다. 이것은 분명 나중에 문제를 일으킬 것이다.
    - 이것을 해결하려면 함수가 종료되어도 num1의 메모리가 사라지지 않게 만들면 된다.

- 그리고 이것은 정적 변수로 선언을 하면 해결된다.
    ``` C
    #include <stdio.h>
    int* ReturnReference(){
        static int num1;
        scanf("%d",&num1);
        return &num1;
    }

    int main(void){
        int* p = NULL;
        p = ReturnReference();
        printf("%d \n",*p);
        return 0;
    }
    ```

## void형 포인터
- 우리가 함수를 만들 때 사용했던 void라는 키워드는 '공허'라는 뜻을 가지고있다. 즉, 아무것도 없다는 뜻이다.
- void형 포인터는 자료형이 없는 포인터라는 뜻이다. 그래서 어떤 자료형의 주소라도 저장할 수 있다.
``` C
#include<stdio.h>
int main(){
   int num1 = 10;
   char c = 'a';

   void* voidPointer1 = NULL;

   voidPointer1 = &c;
   printf("%x \n",voidPointer1);
   voidPointer1 = &num1;
   printf("%x \n",voidPointer1);


   printf("%d \n",*voidPointer1);
}
```
- 위의 코드를 실행해보면 num1과 c의 주소는 제대로 출력이 되지만 *를 사용해서 voidPointer1의 값을 출력하려고하면 에러가 발생한다.
    - 그 이유는 void 포인터가 모든 주소형의 주소를 다 저장할수는 있지만 값을 참조하는 것은 제한되어있기 때문이다.
    - 그러면 아무런 쓸모가 없는것 아닌가? 아니다. 강제 형변환을 사용하면 원하는대로 사용이 가능하다.
    ``` C
    #include<stdio.h>
    int main(){
        int num1 = 10;

        void* voidPointer1 = NULL;
        voidPointer1 = &num1;

        printf("%d \n",*(int*)voidPointer1);
        *(int*)voidPointer1 =20;
        printf("%d \n",*(int*)voidPointer1);
    }
    ```
    ```
    10
    20
    ```
    - 값을 참조할 때 void 포인터 이름 앞에 (int*)를 붙여주어 강제로 int포인터로 형변환을 했다.
    - 덕분에 값을 변경하는 것도, 출력하는 것도 가능하다.