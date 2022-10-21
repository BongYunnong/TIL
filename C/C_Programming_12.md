# C언어 기초 #12- 문자열 표준 함수
- 표준함수는 선언을 안해도 사용할 수 있는, 내장된 함수를 뜻한다.

## 문자열 표준 함수
- gets() puts()
    ``` C++
    #include <stdio.h>
    int main(){
        char array1[10];
        gets(array);
        puts(array);
    }
    ```
    - gets를 쓰면 인자로 받은 주소에 사용자가 입력한 문자열을 저장할 수 있다.
    - 그리고 puts를 사용하면 해당 주소의 문자열을 출력한다.
    - 문자열을 위한 함수이니 당연히 gets를 통해서 입력받은 문자열의 마지막에는 NULL문자가 입력된다.

- strlen()
    - strlen()은 인자로 받은 문자열의 길이를 알려준다.
    - 물론 NULL문자는 뺀 길이이다.

- strcpy() strncpy()
    ``` C
    #include<stdio.h>
    #include<string.h>
    int main(){
        char array1[12]="Hello world";
        char array2[12];
        char array3[12];

        strcpy(array2,array1);
        strncpy(array3,array1, strlen(array1)+1);
    }
    ```
    - 위의 코드에서 strcpy는 array1의 문자열을 array2에 복사하고
    - strncpy는 2번째 인자 문자열을 1번째 인자 문자열에 복사하는데, 3번째 인자의 길이만큼 복사한다.
    - strncpy를 사용할때는 NULL문자를 빼먹지는 않았는지 잘 생각해보자.

- strcat() strncat()
    - 이어붙이기
    ``` C
    #include<stdio.h>
    #include<string.h>
    int main(){
        char array1[100];
        char array2[50];
        char array3[100];
        char array4[50];

        gets(array1);
        gets(array2);

        strcat(array1,array2);
        puts(array1);
        gets(array3);
        gets(array4);

        strncat(array3,array4,2);   // array4에서 2개의 문자만 합침
        puts(array3);
    }
    ```
    ```
    Hello
    World
    HelloWorld
    Hi
    World
    HiWo
    ```

- strcmp() strncmp()
    ``` C
    #include<stdio.h>
    #include<string.h>
    int main(){
        char array1[100]="HelloWorld";
        char array2[100]="HelloKorean";
        char array3[100]="HelloC";
        int result1, result2, result3;

        result1 = strcmp(array1,array2);//앞의 것이 더 작으면-1
        result2 = strcmp(array1,array2,5);//앞의 것과 뒤의 것의 5바이트까지가 같으면 0
        result3 = strcmp(array2,array2);//앞의 것이 더 크면 1
    }
    ​```
​

- strchr() strstr()
    ``` C
    char array1[10] = "Hello";

    strchr(array1, 'o');
    ```
    - -> array1의 문자열에서 o의 주소 찾아서 반환


    ``` C
    char array1[20] = "HelloWorld";

    char array2[20] = "World";

    strstr(array1,array2);
    ```
    - ->array1에서 array2의 주소 찾아서 반환


- strupr(), strlwr()
    - 문자열 대문자로 바꾸기, 소문자로 바꾸기


- sscanf() sprintf()
    ``` C
    #include<stdio.h>
    #include<string.h>
    int main(){
        char array1[50] = "100 3.14 helloWorld";
        char array2[50];
        int num1;
        double num2;
        char str[50];
        sscanf(array1, "%d %lf %s",&num1,&num2,&str); //num1에 100, num2에 3.14, str에 helloWorld 저장

        sprintf(array2, "%d, %lf, %s",num1,num2, str); //array2에 100 3.14 helloWorld저장
    }
    ```
    ​