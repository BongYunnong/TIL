# C언어 기초 #13- 입출력
## 스트림
- 스트림(stream)은 데이터를 입력하고 출력할 때 입력장치와 출력장치, 프로그램을 연결해준다.
- 키보드에서 프로그램으로 입력을 할때는 표준 입력 스트림, 프로그램에서 모니터로 출력할때는 표준 출력 스트림이 사용된다.

- 스트림의 예시로는 stdin, stdout, stderr이 있다.

- stdin은 input 즉, 입력에 사용되고 stdout은 output, 출력에 사용되며 stderr은 error이므로 에러를 담당한다.
    - #include<stdio.h>에서 stdio가 standard input output을 뜻하는 것처럼 말이다.

- 이러한 스트림은 프로그램이 시작할 때 생성되고 종료될 때 소멸된다.

## 버퍼
- 우리가 흔히 버퍼링이 걸린다고 할 때 그 버퍼이다. 버퍼는 처리할 데이터를 임시로 저장한다.
- 데이터 생성 속도와 데이터 처리 속도가 다를 때 속도 차이를 메울 수 있다.
- 아까 스트림이 키보드에서 프로그램으로, 프로그램에서 모니터로 연결해준다고 했는데, 사실은 키보드에서 입력 버퍼로, 출력 버퍼에서 모니터로 데이터가 이동된다.

​
## 콘솔 입출력
- 콘솔 표준 입출력 함수
    - 콘솔 표준 입출력 함수는 우리가 이미 써보았다.
    - #include<stdio.h>라는 문장을 통해 표준 입출력 함수를 사용할 수 있다.
    1. int getchar(void)
    2. int putchar(int c)
    3. char* gets(char* s)
    4. int puts(chat* str)
    5. int scanf(const char* format, ...)
    6. int printf(const char* format, ...)
- 여기서 반환형들이 int인 이유는 함수 사용에 에러가 발생하면 EOF(파일의 끝)을 의미하는 -1을 반환하기 때문이다.

- 콘솔 비표준 입출력 함수
    - 콘솔 비표준 입출력 함수는 버퍼를 사용하지 않는다.
    - 그리고 #include<conio.h>문장을 통해 conio헤더파일을 include해야 사용가능하다.
    1. int getch(void)      //키보드로부터 한 문자 입력받음 (화면에 입력문자가 안 보임)
    2. int getche(int c)    //키보드로부터 한 문자 입력받음 (화면에 문자 보임)
    3. int putch(int c)     //모니터에 한 문자 출력
    4. int kbhit(void)      //키보드의 키가 눌렸는지 체크(눌렀을 때는 0이 아닌 수 반환)


## 파일 입출력
- 지금까지의 입출력은 키보드와 모니터로 이루어진 입출력이었다. 그런데 이것은 프로그램을 종료하면 아무런 의미가 없어진다.
- 그런 점 때문에 프로그램에서 생성된 데이터를 저장하려면 파일로 저장하고 불러와야한다.

- 파일은 2가지 유형이 있다.
    1. 텍스트 파일 : 문자열로 이루어진 데이터
    2. 바이너리 파일(이진 파일) : 이진 형식으로 이루어진 데이터. 텍스트 파일로 열면 이해할 수 없도록 되어있다.

- 파일 입출력은 콘솔 입출력보다 조금 더 복잡한 과정을 거친다.
    - [파일 스트림 생성 -> 파일 열기 -> 파일 입출력 -> 파일 닫기]

- 파일의 접근 모드
    - r: 읽기 전용
    - w : 쓰기 전용
        - 지정 파일이 존재 : 파일 내용 지우고 새로 만들기
        - 지정 파일이 존재 X : 새로운 파일 생성
    - a : 추가 쓰기전용
        - 지정한 파일이 있으면 파일의 끝에서부터 내용 추가
    - r+ : 파일 읽고 쓰기
        - 파일 존재 : 덮어쓰기
        - 파일 존재 X : 새로운 파일 생성
    - w+ : 파일 읽고 쓰기
        - 파일 존재 : 파일 내용 지우고 새로운 파일 생성
        - 파일 존재 X : 새 파일 생성
    - a+ : 파일 읽고 추가 쓰기
        - 파일 존재 : 파일의 끝에서부터 내용 추가
    - 나머지는 r+와 같음

- 파일 입출력 모드
    - t : 텍스트 파일 모드
    - b : 바이너리 파일 모드 


- fgetc() fputc()
    ``` C
    #include<stdio.h>
    int main(){
        FILE* stream;
        int file_state;
        int input;

        stream = fopen("textFile.txt","w");
        if(stream == NULL)
            printf("파일 열기 에러\n");

        while(input != EOF){
            input = fgetc(stdin);
            fputc(input,stream);
        }

        file_state = fclose(stream);
        if(file_state == EOF)
            printf("파일 닫기 에러\n");
    }
    ```
    - FILE포인터를 통해 textFile.txt파일을 쓰기 모드로 열고 저장한다.
    - 그리고 fgetc()함수를 통해 키보드로 문자를 입력받아서 input에 저장한다.
    - 그리고 fputc를 통해 input을 stream(textFile.txt)에 저장한다. 작업이 다끝나면 fclose()로 파일을 닫아준다.

- fgets() fputs()
    ``` C
    #include<stdio.h>
    int main(){
        FILE* stream;
        char input[100];

        stream = fopen("textFile.txt","w");
        if(stream == NULL)
            printf("파일 열기 에러\n");

        fgets(input, sizeof(input),stdin);
        fputs(input, stream);

        fclose(stream);
    }
    ```
    - 위의 코드는 fgetc()가 아닌 fgets()와 fputs()를 사용했다.
    - fgets()함수를 통해 키보드로 입력받은 문자열을 input에 저장하고 fputs()로 출력한다.

​

​

- fprintf(), fscanf()
    ``` C
    int scanf(FILE* stream, const char * format,...);

    int printf(FILE* stream, const char * format,...);

    #include<stdio.h>
    int main(){
        FILE* stream;
        char name[10];
        int kor, eng, total;
        printf("1.이름 입력 :");
        fscanf(stdin, "%s", name);
        printf("2.국어점수, 영어점수 입력 :");
        fscanf(stdin, "%d %d",&kor, &eng);
        total = kor +eng;
        stream = fopen("textFile.txt","w");
        fprintf(stream, "%s, %d, %d, %d \n",name, kor, eng, total);
        fclose(stream);
    }
    ​```

- feof()
    - 파일의 끝 확인 ( 파일 끝에 도달했으면 0이 아닌 값 반환, 도달안했으면 0반환)
    - fgetc() : EOF(-1)
    - fgets() : NULL(0)
    - fscanf() : EOF(-1)
    - 위와 같이 파일 끝에서 반환되는 값을 일일이 기억하는 것 불편
        - ->해결책 : feof()를 사용

- fflush()
    - 버퍼를 비우는 함수
    ``` C
    #include<stdio.h>
    int main(){
        char cData1;
        char cData2;
        printf("문자를 입력 : ");
        scanf("%c", &cData1);
        printf("문자를 한번 더 입력 : ");
        scanf("%c",&cData2);
        printf("문자값 :  %c %c \n",cData1,cData2);
    }
    ```
    - 위의 코드를 입력하면 한번 입력된 문자만 2번 출력하고 프로그램이 종료된다.
    - 그 이유는 엔터를 치는 순간 \n이 버퍼에 남기 때문이다.
    - !!! 원래는 fflush(stdin)으로 버퍼에 남은 것은 지워야 하지만 2013버전까지만 사용 가능
        - -> getchar()을 통해 버퍼 없애자

    - getchar이용하기
        ``` C
        #include<stdio.h>
        int main(){
            char cData1;
            char cData2;
            printf("문자를 입력 : ");
            scanf("%c", &cData1);
            getchar();
            printf("문자를 한번 더 입력 : ");
            scanf("%c",&cData2);
            printf("문자값 :  %c %c \n",cData1,cData2);
        }
        ```

- fwrite(), fread()
    - fread()
        - 파일로부터 바이너리에 데이터를 받아 buffer입력
        - 호출 성공 : count(반복 횟수) 반환
        - 호출 실패 : count보다 작은 값 반환
        ``` 
        size_t fread(void* buffer, size_t size, size_t,count,FILE* stream);
        ```
        1. buffer : 파일로부터 입력받은 데이터를 저장하는 버퍼를 가리키는 포인터
        2. size : 한번에 입력 받은 데이터의 바이트 크기
        3. count : 입력 횟수
        4. stream : 파일 입력 스트림
        - tip) buffer가 void*인 이유 : 어떤 유형의 buffer 사용할 지 자유롭게 선택
    - fwrite()
        - 파일로부터 바이너리에 데이터를 받아 buffer입력
        - 호출 성공 : count(반복 횟수) 반환
        - 호출 실패 : count보다 작은 값 반환
        ```
        size_t fwrite(void* buffer, size_t size, size_t,count,FILE* stream);
        ```
        1. buffer : 출력 데이터를 저장한 버퍼를 가리키는 포인터
        2. size : 한번에 출력할 데이터의 바이트 크기
        3. count : 입력 횟수
        4. stream : 파일 출력 스트림

- tip) size_t는 unsigned int를 typedef한 것이다.
    - 다른 점은, unsigned int는 32비트, 64비트 체제에 따라 변하지 않고 32비트인데, size_t는 32비트에서는 32비트, 64비트 환경에서는 64비트가 될 수 있다.
    - 요약 : 플랫폼에 따라 달라진다.