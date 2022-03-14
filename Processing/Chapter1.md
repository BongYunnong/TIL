# Processing #1
## 기본 그리기
- size(x,y) : 실행 창 크기
    - width, height -> 창 크기
- background(color) : 바탕 색(흑~백 0:검정, 255:흰색)
- stroke(color) : 선 색(흑~백)
- fill(color) : 채우기 색(흑~백)
- noFill() : 채우지 않음

- color같은 경우는 인자 1개는 흑~백
    - 3개는 r,g,b
    - 4개는 r,g,b,a(투명도 255->100%)

- rect(x,y,width,height) : 왼쪽 위 기준으로 x,y좌표, 너비, 높이 사각형
![image](https://user-images.githubusercontent.com/11372675/158145496-6b523c29-50ea-475a-bf37-a834795d6d68.png)

- ellipse(x,y,width,height) : 왼쪽 위 기준으로 x,y,좌표, 너비, 높이 타원
![image](https://user-images.githubusercontent.com/11372675/158146027-305c17f4-e87c-43a4-8c90-16c9260b262a.png)

- ellipseMode(CENTER), rectMode(CENTER);
    - 원래 왼쪽 위 기준으로 그렸던 도형을 중심을 기준으로 그릴 수 있게 됨

- line(x1,y1, x2,y2);

- println(string) : 문자열 Console에 출력


## Setup, Draw
``` java
// 처음 시작할 때 한 번 실행
// size는 항상 setup에서 결정되어야한다.
void setup(){
    size(480,240);
    ...
}
// draw는 지속적으로 실행된다.
void draw(){
    ...
}
```

## Interaction
- MousX,MouseY
    - 마우스를 따라다니는 정사각형 그리기
        ``` java
        void draw(){
            // 만약 background가 없으면? 정사각형을 연속적으로 그리는 모습을 보여줌
            background(255);
            stroke(0);
            fill(100);
            rectMode(CENTER);
            rect(mouseX, mouseY, 50, 50);
        }
        ```
    - 선 그리기
        ``` java
        void draw(){
            stroke(0);
            // pmouseX,Y는 이전의 마우스 위치
            line(pmouseX,pmouseY,mouseX,mouseY);
        }
        ```
- MousePressed , KeyPressed
    ``` java
    void mousePressed(){
        stroke(0);
        fill(175);
        rectMode(CENTER);
        rect(mouseX,mouseY,16,16);
    }
    void keyPressed(){
        background(255);
        // key를 통해 입력된 키 확인 가능
        println(key);
    }
    ```
- Translate
    ``` java
    void setup(){
        size(480,240);
    }
    void draw(){
        background(255);
        rectMode(CENTER);
        rectMode(CENTER);
        // 화면 자체를 mouseX,mouseY를 기준으로 움직임
        translate(mouseX,mouseY);
        stroke(0);
        fill(175);
        rect(0,0,20,100);

        ellipse(50,40,50,20);
    }
    ```

## Variables
- 변수 선언
    ``` java
    int i=0;
    char c = 'a';
    double d = 123.45;
    boolean b = false;
    float f = 4.0;
    float ff = f+5.0;
    float fff =f*ff+1.0;

    void setup(){
        size(480,240);
    }
    void draw(){
        // 위에서 아래로 내려오는 타원
        f = f+1;
        ellipse(ff,f,50,50);
    }
    ```
## System Variables
- System variable
    ``` java
    void setup(){
        size(480,240);
    }
    void draw(){
        background(50);
        stroke(255);
        fill(framecount/2);
        rectMode(CENTER);
        rect(width/2,height/2,mouseX+10,mouseY+10);
    }
    void keyPressed(){
        println(key);
    }
    ```
    - framecount
    - CENTER
    - width, height
    - mouseX, mouseY
    - key

## Random 
- Random paiting dots
    ``` java
    float r,g,b,a;
    float diameter,x,y;
    void setup(){
        size(480,240);
        background(255);
    }
    void draw(){
        r = random(255);
        g = random(255);
        b = random(255);
        a = random(255);
        diameter = random(20);
        x = random(width);
        y = random(height);

        noStroke();
        fill(r,g,b,a);
        ellipse(x,y,diameter,diameter);
    }
    ```
    - random : 일정 범위 내의 특정 값 반환
