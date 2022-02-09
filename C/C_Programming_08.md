# C언어 기초 #8 - 포인터와 배열
## 포인터와 배열
- 이번에는 포인터와 배열을 연결지어보자.
- 포인터는 주소를 저장하고, 배열의 이름은 배열의 시작주소라 했다. 이 특징을 잘 조합하면 배열과 포인터를 연결지을 수 있다.

- 아래 예제를 보자.
    ``` C
    #include<stdio.h>
    int main(){
        int array[3] = {10,20,30};
        int* array_p = NULL;
        array_p = array;

        printf("%d %d %d %d \n", *array_p, *(array_p+0), *(array_p+1), *(array_p+2));

        printf("%d %d %d \n", sizeof(*array_p), sizeof(*(array_p+0)), sizeof(*&array_p[0]));
        
        return 0;
    }
    ```
    ```
    10 10 20 30
    4 4 4
    ```
    - *array_p를 출력할 때 array_p는 array 배열의 시작주소와 같은 의미이기에 당연히 0번째 값인 10이 출력된다.
    - 그리고 array_p+0은 &(array_p[0])과 똑같은 의미이기 때문에 앞에 *를 붙이면 array의 0번째 값인 10이 출력되고 , 
    - *(array_p+1)은 20, *(array_p+2)는 30이 출력된다.
    - 그리고 아래 4 4 4가 출력되는 것은 주소에 저장된 값을 참조하기때문에 int형의 크기인 4가 출력되는 것이다.


- 여기에서 아주 신기한 것이 있다. 포인터에 +-연산자를 사용해보자. 
    ``` C
    #include<stdio.h>
    int main(){
        int array[3] = {10,20,30};
        int* array_p = NULL;

        array_p = array;
        printf("%d %d %d\n", array_p[0], array_p[1], array_p[2]);

        array_p = array+1;
        printf("%d %d %d\n", array_p[-1], array_p[0], array_p[1]);
        
        array_p = array+2;
        printf("%d %d %d\n", array_p[-2], array_p[-1], array_p[0]);

        return 0;
    }
    ```
    ```
    10 20 30
    10 20 30
    10 20 30
    ```
    - 위의 예제에서 볼 수 있듯이 포인터에 가감산을하면  array_p[-1], array_p[-2]처럼 대괄호 안에 -값을 넣는 신기한 일을 할 수 있다.
    - 따지고보면 array_p[-1]은 *(array_p-1)을 뜻하고, array_p는 array+1이니 *(array+1-1) == *(array)가 되는 것이다.
    - 이처럼 포인터를 사용하면 유동적으로 값을 참조할 수 있다는 것이 큰 장점이다.

## 포인터와 2차원 배열
- 먼저 2차원 배열 예시를 보자.
    ``` C
    #include<stdio.h>
    int main(){
        int array[3][2] = {{10,20},{30,40}{50,60}};
        int* array_p = NULL;

        array_p = array;
        printf("%d %d\n", array_p[0], array_p[1]);
        printf("%d %d\n", array_p[2], array_p[3]);
        printf("%d %d\n", array_p[4], array_p[5]);

        return 0;
    }
    ```
    ```
    10 20
    30 40
    50 60
    ```
    - 배열의 첫번째 대괄호에는 행의 개수가 들어가기에 array는 행이 3개이고 열이 2개인 2차원 배열이다.
    - 그런데 어떻게 array_p[4]처럼 배열의 크기를 넘어가는 index를 넣고도 오류가 나지 않을까?
    - array_p[4]는 *(array_p+4)을 뜻한다. 배열의 시작주소에서 4번 주소를 옮긴 값을 참조한다. 그래서 2차원 배열을 왼쪽 위에서부터 차례대로 읽었을 때 4번째 값인 50이 정상적으로 출력된다.

- 그러면 당연히 평소에 2차원 배열의 값에 접근했던 것 처럼 array_p[0][1] 이렇게 접근하면 되겠지?
    - 그렇지 않다.
    ``` C
    #include<stdio.h>
    int main(){
        int array[3][2] = {{10,20},{30,40}{50,60}};
        int* array_p = NULL;

        array_p = array;
        printf("%d %d\n", array_p[0][0], array_p[0][1]);  //에러
        printf("%d %d\n", array_p[1][0], array_p[1][1]);  //에러
        printf("%d %d\n", array_p[2][0], array_p[2][1]);  //에러

        return 0;
    }
    ```
    - 이러면 에러가 생긴다. array_p는 1차원 포인터 변수이기때문에 2차원 배열처럼 접근할 수 없다.
    - 그렇다면 array_p를 int**를 사용하여 2차원 포인터로 만들면 될까?
        - 이것도 에러가 생긴다.
        - 왜냐하면 2차원 포인터는 1차원 포인터 변수의 주소를 저장할 때 사용되기 때문이다.
        - 그래서 포인터로 2차원배열처럼 접근하려면 다음과 같이 사용해야한다.
        ``` C
        #include<stdio.h>
        int main(){
            int array[3][2] = {{10,20},{30,40}{50,60}};
            int (*array_p)[2] = NULL;

            array_p = array;

            printf("%d %d\n", array_p[0][0], array_p[0][1]);
            printf("%d %d\n", array_p[1][0], array_p[1][1]);
            printf("%d %d\n", array_p[2][0], array_p[2][1]);

            return 0;
        }
        ```
        - array_p[2][1]은 *(array_p[2]+1)를 뜻하고, *(*(array_p+2)+1)과 같으며, (*(array_p+2))[1]이 된다.
        - 즉, array_p는 array의 행 시작 주소를 저장하니, 2번째 행의 1번째 값을 참조하게되고, 이는 60을 출력하게된다.
        - 이처럼 배열을 가리키는 포인터 변수를 "배열 포인터 변수"라고한다.


- 그리고 이제 "포인터 배열"을 배울 차례이다.
    ``` C
    #include<stdio.h>
    int main(){
        int num1 = 10, num2 = 20, num3 = 30;
        int* p_array[3] = {NULL,NULL,NULL};

        p_array[0] = &num1;
        p_array[1] = &num2;
        p_array[2] = &num3;

        printf("%d %d %d \n", *p_array[0],*p_array[1],*p_array[2]);
        printf("%d %d %d \n", **(p_array+0),**(p_array+1),**(p_array+2));

        return 0;
    }
    ```
    ```
    10 20 30
    10 20 30
    ```
    - 포인터 배열은 말 그대로 포인터를 저장하는 배열이기 때문에 p_array[0]는 포인터를 참조하는 것이고, 해당 포인터의 값을 참조하려면 앞에 *를 붙여줘야한다.

## 문자열
- 지금까지 우리는 문자를 변수에 저장할 때 char과 ''를 사용해서 한 문자씩 저장했었다. 하지만 이것은 너무나도 귀찮은 작업이다. 그것을 보완한 것이 문자열이다.
- 이미 문자열을 사용했는데, printf("%d %d \n")여기에서 큰 따옴표로 묶어진 "%d %d \n"이 문자열이다.

- 문자열은 문자의 배열이라고 생각하면 된다. 각 문자들이 주소를 가지고있어서 포인터로도 접근이 가능하다.

- 주의해야할 점이 있는데, 문자열은 문자열이 끝났다는 것을 알려주기위해 맨 마지막에 '\0'라는 문자가 삽입되어있다. 이것을 종료 문자라고 부르고, 널(Null) 문자라 칭한다.

``` C
#include<stdio.h>
int main(){
   char array[] ="ABCD";

   printf("%c%c%c%c\n",array[0],array[1],array[2],array[3],array[4]);
   printf("%s\n",array);
   printf("문자열 크기 : %d \n",sizeof(array));

   return 0;
}
```
```
ABCD
ABCD
5
```
- array[4]가 출력은 되지 않았지만 에러가 생기지 않고, array의 size를 체크했을때 5가 나오는 것을 통해 Null문자의 존재를 확인할 수 있다.

- 문자 배열을 초기화할 때 큰따옴표로 묶으면 자동으로 Null문자가 저장되지만 작은따옴표로 하나씩 저장을 할때는 사용자가 직접 '\0'를 저장해주어야하니 잊지 말도록 하자.
    - 만약 널 문자를 저장하지않으면 데이터를 문자열이 아닌 문자로 인식해서 이상한 값을 출력할 것이다.


- 이제는 포인터와 문자열을 섞어보도록 하자.
    ``` C
    #include<stdio.h>
    int main(){
        char* pointer ="ABCD";

        printf("%s\n",pointer);
        printf("%s\n",pointer+1);
        printf("%s\n",pointer+2);
        printf("%s\n",pointer+3);

        return 0;
    }
    ```
    ```
    ABCD
    BCD
    CD
    D
    ```
    - 위처럼 몇번째 문자부터 출력하는 것도 가능하다.

- 그런데 char* pointer ="ABCD"; 이 문장이 맞는 문장인가? 포인터는 값이 아니라 주소를 저장하지 않았나?
    - "ABCD"는 문자열 상수로, 메모리에 저장되고 주소가 있다. 그래서 포인터로도 접근이 가능하다.
    - 대신 위와같이 초기화를 하면 상수를 초기화하는 것이 되기 때문에 문자열의 값을 변경할 수 없다.
    - 문자열의 값을 변경하고싶으면 문자 배열에 문자열을 저장한 뒤에 index를 사용해서 값을 변경하면 된다.