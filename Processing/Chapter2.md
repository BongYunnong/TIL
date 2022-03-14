# Processing #2
## Conditional
- fading color
    ``` java
    float r = 0;
    float g = 0;
    float b= 0;
    void setup(){
        size(280,240);
    }
    void draw(){
        background(r,g,b);
        stroke(255);
        line(width/2,0,width/2,height);
        line(0,height/2,width,height/2);

        if(mouseX > width/2){
            r = r+1;
        }else{
            r = r-1;
        }
        if(mouseY > height/2){
            b = b+1;
        }else{
            b = b-1;
        }

        // 함수와 다르게 systemVariable로!
        if(mousePressed){
            g = g+1;
        }else{
            g = g-1;
        }

        /*
        if(r>255){
            r=255;
        }else if(r<0){
            r=0;
        }
        */
        r = constrain(r,0,255);
        g = constrain(g,0,255);
        b = constrain(b,0,255);
    }
    ```
- button
    ``` java
    boolean clicked=false;
    int x=100;
    int y=100;
    int width=100;
    int height = 50;

    void setup(){
        size(480,240);
    }
    void draw(){
        if(mouseX > x && mouseX < x+w 
            && mouseY > y && mouseY < y+h 
            && mousePressed){
            button = true;
        }else{
            button =false;
        }
        if(button){
            background(255);
            stroke(0);
        }else{
            background(0);
            stroke(255);
        }
        fill(100);
        rect(x,y,w,h);
    }

    /* 아래로 하면 switch가 됨
    void mousePressed(){
        if(mouseX > x && mouseX < x+w 
            && mouseY > y && mouseY < y+h){
            button = true;
        }else{
            button =false;
        }
    }
    */
    ```

- Bouncing ball
    ``` java
    float x=0;
    float y=0;
    float xSpeed=2;
    float ySpeed=2;
    float gravity = 0.1; 
    void setup(){
        size(480,240);
    }
    void draw(){
        background(255);
        x = x+xSpeed;
        y = y+ySpeed;
        if((x>width) || (x<0)){
            xSpeed = xSpeed * -1;
        }
        if((y>height) || (y<0)){
            ySpeed = ySpeed * -1;
        }
        ySpeed = ySpeed+gravity;


        stroke(0);
        fill(175);
        ellipse(x,y,32,32);
    }
    ```

## Loop
- While
    ```java
    int x=50;
    int y=50;
    int spacing = 10;
    int length = 20;
    int endLegs = 480;

    void setup(){
        size(480,480);
    }
    void draw(){
        background(0);
        stroke(100);
        x=0;
        spacing = constrain(mouseX/2,4,width);
        while(x<=endLegs){
            line(x,y,x,y+length);
            x = x+spacing;
        }
    }
    ```

- For
    ``` java
    size(480,240);
    background(255);
    int y=80;
    int spacing = 10;
    int length = 20;
    for(int x=50;x<=150;x+=spacing){
        line(x,y,x,y+length);
    }
    ```

- loop line
    ``` java
    int y=0;
    void setup(){
        size(480,240);
        background(255);
        // 프레임 단위를 5로 만들어버림
        frameRate(5);
    }
    void draw(){
        stroke(0);
        line(0,y,width,y);
        y+=10;
        if(y>height){
            y=0;
        }
    }
    ```

- Gradient
    ``` java
    void setup(){
        size(480,240);
    }
    void draw(){
        background(0);
        int i=0;
        while(i<width){
            noStroke();
            // abs는 absolute - 절댓값
            float distance = abs(mouseX-i);
            fill(distance);
            rect(i,0,10,height);
            i+=10;
        }
    }
    ```