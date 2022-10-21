# C언어 기초 #11 - 구조체 2
## 자기 참조 구조체와 외부 참조 구조체
- 이름에서 알 수 있듯이 자기 참조 구조체는 자기 자신을 참조하고, 외부 참조 구조체는 외부에서 구조체를 참조한다.
- 그런데 이게 무엇을 뜻하는지는 잘 모르겠다. 한번 예시를 보자.
- 자기참조 구조체
    ``` C
    //자기 참조 구조체
    #include<stdio.h>
    struct character{
        int ID;
        int level;
        struct character* character_p;
    };
    int main(void){
        struct character player1={21312,1,NULL};
        struct character player2={51251,2,NULL};

        player1.character_p = &player2;

        printf("%d %d \n%d %d\n",
            player1.ID,
            player1.level,
            player1.character_p->ID,
            player1.character_p->level);
        return 0;
    }
    ```
    ```
    21312 1
    51251 2
    ```
    - 구조체 안에 구조체 자신의 포인터가 있다. 이것을 보면 게임을 만들 때 적팀이나 파티원의 정보를 참조할 때 쓸 수 있지 않을까 싶다.

- 외부 참조 구조체
    ``` C
    //외부 참조 구조체
    struct character{
        int ID;
        int level;
        struct character_Stat* character_P;
    };
    struct character_Stat{
        int damage;
        int health;
    };
    int main(){
        struct character player1 = {21312,1,NULL};
        struct character player2 = {51251,2,NULL};
        struct character_Stat stat1 = {10,100};
        struct character_Stat stat2 = {15,150};

        player1.character_P = &stat1;
        player2.character_P = &stat2;

        printf("%d %d %d\n",
            player1.ID,
            player1.character_P->damage,
            player1.character_P->health);
        printf("%d %d %d\n",
            player2.ID,
            player2.character_P->damage,
            player2.character_P->health);
        return 0;
    }
    ```
    ```
    21312 10 100
    51251 15 150
    ```
    - 이것은 중첩 구조체같은 느낌이다. 하지만 안쪽의 구조체를 바깥으로 내보내서 더욱 동적인 프로그래밍이 가능해진다.

## 구조체와 함수
- 구조체를 매개변수로 전달하기
    ``` C
    #include <stdio.h>
    struct stat{
        int damage;
        int health;
    };

    void printStat(struct stat _tmpStat){
        _tmpStat.damage += 1;
        _tmpStat.health += 10;
        printf("%d %d \n",_tmpStat.damage,_tmpStat.health);
    }

    int main(void){
        struct stat stat1 = {10,100};
        printStat(stat1);
        printf("%d %d \n",stat1.damage,stat1.health);
        return 0;
    }
    ```
    ```
    11 110
    10 100
    ```
    - 당연하지만 구조체도 하나의 자료형처럼 사용할 수 있기에 함수에 매개변수로 값을 주고받을 수 있다.
    - 하지만 위의 방법은 값에 의한 함수 호출이기때문에 말 그대로 값을 복사했을 뿐 실제 stat1에게는 영향을 주지 못 한다.

- 값을 바꾸고싶다면 아래처럼 하면 된다.
    ``` C
    #include <stdio.h>
    struct stat{
        int damage;
        int health;
    };

    void printStat(struct stat* _tmpStat){
        _tmpStat->damage += 1;
        _tmpStat->health += 10;
        printf("%d %d \n",_tmpStat->damage,_tmpStat->health);
    }

    int main(void){
        struct stat stat1 = {10,100};
        printStat(&stat1);
        printf("%d %d \n",stat1.damage,stat1.health);
        return 0;
    }
    ```
    ```
    11 110
    11 110
    ```

- 구조체를 반환하기
    ``` C
    #include <stdio.h>
    struct stat{
        int damage;
        int health;
    };

    struct stat printStat(void){
        struct stat tmpStat = {10,100};
        return tmpStat;
    }

    int main(void){
        struct stat stat1;
        stat1 = printStat();
        printf("%d %d \n",stat1.damage,stat1.health);
        return 0;
    }
    ```
    - 다음과 같이 구조체도 반환할 수 있다.

## 공용체
- 공용체는 그룹으로 묶인 여러개의 멤버 변수들 중에 가장 큰 메모리 공간을 공유해서 사용하는 것을 의미한다.
- 구조체의 경우에는 멤버 변수들이 따로따로 메모리를 할당하지만
- 공용체는 가장 큰 메모리를 가지는 변수의 메모리공간을 공유한다
``` C
#include <stdio.h>
union stat{
   int damage;
   int health;
};

struct stat_struct{
   int damage;
   int health;
};

int main(void){
   printf("%d %d \n", sizeof(union stat),sizeof(struct stat_struct);

   union stat stat1;
   stat1.damage =10;

   printf("%d %d",stat1.damage,stat1.health);

   return 0;
}
```
```
4 8
10 10
```
- sizeof로 구조체와 공용체의 크기를 비교해보면 구조체는 8이지만 공용체는 4인 것을 볼 수 있다.
- 이것은 공용체에서 int가 2개 있기 때문에 4바이트를 공유하기 때문이다. 덕분에 stat1의 damage만 바꿨는데도 health값이 바뀌었다.

​
## 열거형
``` C
#include<stdio.h>
enum state {IDLE,WALK=2,ATTACK};
int main(){
   enum state s1,s2,s3;

   s1= IDLE;
   s2=WALK;
   s3=ATTACK;
   printf("%d %d %d %d\n",s1,s2,s3,ATTACK);
}
```
```
0 2 3 3
```
- 열거형은 보는 것 처럼 값에 의미있는 이름을 붙일 수 있다. 원래같으면 0,1,2 이렇게 state를 지정해야했겠지만 열거형을 사용하면

- IDLE, WALK, ATTACK처럼 한눈에 봐도 알아볼 수 있도록 만들 수 있다.

- 그리고 WALK=2라고 한 것 처럼 초기화도 할 수 있다. 이렇게 하면 WALK뒤에 있는 ATTACK은 자동적으로 3이된다.