# C언어 기초 #10 - 구조체 1
- 변수가 아주아주 많을 때를 위해 우리는 배열이라는 것을 배웠다.
- 그런데 배열은 한계가 있다. 같은 자료형의 값만 저장할 수 있다는 점이다.
- 예를들어, 체력과 공격력, 이동속도를 가진 캐릭터를 저장하려면 어떻게 해야할까? 체력 배열, 공격력 배열, 이동속도 배열을 만들어야하나?
    - 그것보다는 캐릭터 배열을 만드는 편이 훨씬 좋다. 그리고 이것은 구조체를 사용하면 된다.

## 구조체
- 구조체는 여러개의 변수를 묶은 사용자가 직접 정의한 자료형이다. 즉 구조체를 만들면 int, float처럼 자료형으로 사용할 수 있다.

- 구조체를 정의하는 법은 간단하다.
    ``` C
    struct character_struct{
        int health;
        int damage;
        int speed;
    };
    ```
    - struct 키워드 뒤에 원하는 구조체의 이름을 쓰고 중괄호 안에 사용할 변수를 선언한 뒤 마지막에 세미콜론을 붙여주면 끝이다.

- 이렇게 만들어진 구조체는 다음과 같이 사용할 수 있다.
    ``` C
    #include<stdio.h>
    struct character{
        int health;
        int damage;
        int speed;
    };
    int main(){
        struct character player1,player2,player3;

        player1.health=10;
        player1.speed =5;
        player2.health =20;
        player2.damage =3;
    }
    ```
    - 구조체를 자료형으로 선언한 변수에 점(.)을 붙이고 구조체 안의 멤버변수를 쓰면 해당 구조체변수의 멤버변수에 접근할 수 있다.
    - 이때 점(.)을 접근 연산자라고 부른다.  점을 ~의 라고 해석하면 편하다.
- 그런데 위의 예제처럼 하나하나 다 접근해가며 초기화를 해주기는 귀찮으니 아래와같이 사용할수도있다.
    ``` C
    #include<stdio.h>
    struct character{
        int health;
        int damage;
        int speed;
    }player3;

    int main(){
        struct character player1={10,3,5};
        struct character player2={20,2,6};

        player3.health =20;
        player3.damage =3;
    }
    ```
    - player1과 2는 선언과 동시에 멤버변수를 초기화했고 player3은 구조체 정의와 동시에 선언을 해주었다.

- 구조체는 구조체끼리 사칙연산을 할수는 없지만 대입은 가능하다. 그래서 값을 복사하는 것은 편하다.
    ``` C
    #include<stdio.h>
        struct character{
        int health;
        int damage;
        int speed;
    };

    int main(){
        struct character player1={10,3,5};
        struct character player2={20,2,6};

        player1= player2;
        printf("%d \n",player1.health); //20출력
    }
    ```

## 구조체 중첩
- 반복문, 함수가 중첩이 가능한 것 처럼 구조체도 중첩이 가능한데 덕분에 복잡한 정보도 자료형으로 만들 수 있다.
    ``` C
    #include<stdio.h>
    struct characterStat{
        int health;
        int speed;
    };
    struct character{
        int characterID;
        struct characterStat stat;
    ];
    int main(){
        struct character player1;
        struct character player2 = {412421,{10,5}};

        player1.characterID = 2131412;
        player1.stat.health = 10;
    }
    ```
    - 중첩 구조체를 선언과 동시에 초기화 하려면 위와 같이 단계적으로 중괄호를 사용해주면 된다.

## typedef로 새로운 이름 만들기
- 그런데 자료형을 선언할때마다 앞에 struct를 붙여야 한다는 것이 너무나도 불편하고 귀찮지 않은가?
- 프로그래머들은 이런것을 못 참기 때문에 또 새로운 기능을 만들었다.
    ``` C
    #include<stdio.h>
    typedef struct characterStat{
        int health;
        int speed;
    }CHARACTERSTAT;

    struct character{
        int characterID;
        CHARACTERSTAT stat;
    ];

    typedef struct character CHARACTER;

    int main(){
        CHARACTER player1;
        CHARACTER player2 = {412421,{10,5}};

        player.characterID = 2131412;
        player.stat.health = 10;
    }
    ```
    - 구조체를 정의하면서 typedef를 쓰려면 구조체 정의 중괄호 뒤에 사용할 새 이름을 쓰고,
    - 이미 정의된 구조체에 typedef를 쓰려면 typedef struct character CHARACTER; 처럼 사용하면 된다.
    - 지금은 이것이 귀찮아보일수 있지만 만약 구조체 변수 100개를 선언해야한다면 오히려 typedef를 먼저 한번 써놓는 것이 훨씬 편하다.


## 구조체 배열
- 이제 구조체 배열을 배워보자. 배열은 정말 안 끼는 곳이 없는 것 같다.
    ``` C
    #include<stdio.h>
    typedef struct characterStat{
        int health;
        int speed;
    }CHARACTERSTAT;

    struct character{
        int characterID;
        CHARACTERSTAT stat;
    ];

    typedef struct character CHARACTER;

    int main(){
        CHARACTER players[3]={{1243512,{10,5}},
                                {5612464,{20,6}},
                                {1243156,{30,7}}};
        for(int i=0;i<3;i++)
            printf("%d %d\n",players[i].characterID,players[i].stat.health);
    }
    ```
    - 실행결과

        ``` C
        1243512 10
        5612464 20
        1243156 30
        ```
    - 특별할 것은 없고 그냥 다른 자료형 배열을 만드는 것 처럼 선언해주면 된다.

​

## 구조체 포인터
``` C
#include<stdio.h>

struct character{
   int health;
   int speed;
];

typedef struct character CHARACTER;

int main(){
   CHARACTER player1={10,5};
   CHARACTER* player_pointer=NULL;

   player_pointer = &player1;

   printf("%d %d\n", player1.health , players1.speed);
   printf("%d %d\n", (*player_pointer).health , (*player_pointer).speed);
   printf("%d %d\n", player_pointer->health, player_pointer->speed);
}
```
```
10 5
10 5
10 5
```
- 여기서 주의해서 봐야할 것은 아래에서 2,3번째 코드이다.
    - player_pointer는 struct character의 포인터 변수인데, 이 포인터를 활용해서 값에 접근하려면 *를 사용하여 player_pointer의 주소에 있는 값인 player1에 접근한 뒤 점(.)을 써서 값에 접근해야한다. 그런데 이것이 보기 힘들기에 구조체 포인터 변수에서 구조체의 값을 접근할때는 점(.)이 아닌 ->를 사용하도록 만들었다.
    - (*player_pointer).health == player_pointer->health라는 뜻이다.
- 주의할 점은 (*player_pointer).health에서 괄호를 빼면 안된다.
    - *보다 .이 우선순위가 높기 때문에 player_pointer.health를 먼저 계산하고 *를 계산하기 때문이다.