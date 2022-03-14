# Processing #4
## Array
``` java
int[] arr1 = new int[5];
int[0]=1;
int[1]=10;
int[2]=100;
int[3]=1000;
int[4]=10000;

float[] arr2 = {1.2, 3.4, 5.6};

void setup(){
    int index=0;
    while(index<5){
        arr1[index] = random(0,200);
        index++;
    }

    for(int i=0;i<3;i++){
        arr2[i] = random(0,10.0);
    }
}
```

- Mouse History
    ``` java
    int[] xPoses = new int[50];
    int[] yPoses = new int[50];
    void setup(){
        size(480,240);
        for(int i=0;i<xPoses.length;i++){
            xPoses[i]=0;
            yPoses[i]=0;
        }
    }
    void draw(){
        background(255);
        for(int i=0;i<xPoses.length-1;i++){
            xPoses[i] = xPoses[i+1];
            yPoses[i] = yPoses[i+1];
        }
        xPoses[xPoses.length-1] = mouseX;
        yPoses[yPoses.length-1] = mouseY;

        for(int i=0;i<xPoses.length;i++){
            noStroke();
            fill(255-i*5);
            ellipse(xPoses[i],yPoses[i],i,i);
        }
    }
    ```

- Interactive Objects
    - interactiveObjects.pde
        ``` java
        Stripe[] stripes = new stripe[10];

        void setup(){
            size(480,240);
            for(int i=0;i<stripes.length;i++){
                stripes[i] = new Stripe();
            }
        }
        void draw(){
            background(100);
            for(int i=0;i<stripes.length;i++){
                stripes[i].Rollover(mouseX,mouseY);
                stripes[i].Move();
                stripes[i].Display();
            }
        }
        ```
    - Strip.pde
        ``` java
        class Stripe{
            float x;
            float speed;
            float w;

            boolean mouse;

            Stripe(){
                x=0;
                speed = random(1);
                w = random(10,30);
                mouse = false;
            }
        }
        void Display(){
            if(mouse){
                fill(255);
            }else{
                fill(255,100);
            }
            noStroke();
            rect(x,0,w,height);
        }
        void Move(){
            x+=speed;
            if(x>width + 20)
                x = -20;
        }
        void Rollover(int _x,int _y){
            if(_x > x && _x < x+w){
                mouse = true;
            }else{
                mouse = false;
            }
        }
        ```

- Append
    - arrayAppend.pde
        ``` java
        Ball[] balls = new Ball[1];
        float gravity = 0.1;
        void setup(){
            size(480,240);
            balls[0] = new Ball(50,0,24);
        }
        void draw(){
            background(255);
            for(int i=0;i<balls.length;i++){
                balls[i].Gravity();
                balls[i].Move();
                balls[i].Display();
            }
        }
        void mousePressed(){
            Ball b = nwe Ball(mouseX,mouseY,24);
            balls = (Ball[])append(balls,b);    // (reassign하려는 배열, 추가하려는 요소)
        }
        ```
    - Ball.pde
        ``` java
        class Ball{
            float x;
            float y;
            float speed;
            float w;
            Ball(float tempX, float tempY, float tempW){
                x = tempX;
                y = tempY;
                w = tempW;
                speed=0;
            }
            void Gravity(){
                speed = speed + gravity;
            }
            void Move(){
                y = y+speed;
                if(y > height){
                    speed = speed * -0.95;
                    y = height;
                }
            }
            void Display(){
                fill(101);
                stroke(0);
                ellipse(x,y,w,w);
            }
        }
        ```

## Algorithm
- Intersection
    - instersection.pde
        ``` java
        Ball ball1;
        Ball ball2;
        void setup(){
            size(480,240);
            ball1 = new Ball(64);
            ball2 = new Ball(32);
        }
        void draw(){
            background(255);
            ball1.Move();
            ball2.Move();
            if(ball1.intersect(ball2)){
                ball1.Highlight();
                ball2.Highlight();
            }
            ball1.Display();
            ball2.Display();
        }
        ```
    - Ball.pde
        ``` java
        class Ball{
            float r;
            float x,y;
            float xSpeed,ySpeed;
            color c = color(100,50);

            Ball(float tempR){
                r =tempR;
                x = random(width);
                y = random(height);
                xSpeed = random(-5,5);
                ySpeed = random(-5,5);
            }
            void Move(){
                x+=xSpeed;
                y+=ySpeed;
                if(x>width || x<0){
                    xSpeed *= -1;
                }
                if(y>height || y<0){
                    ySpeed *= -1;
                }
            }
            void Highlight(){
                c - color(0,150);
            }
            boolean Intersect(Ball b){
                float tmpDist = dist(x,y,b.x,b.y);
                if(tmpDist < r + b.r){
                    return true;
                }else{
                    return false;
                }
            }
        }
        ```

- Timer
    ``` java
    int savedTime;
    int totalTime = 5000;
    void setup(){
        size(240,240);
        background(0);
        savedTime = millis();
    }
    void draw(){
        int passedTime = millis() - savedTime;
        if(passedTime > totalTime){
            println("5 seconds passed");
            background(random(255));
            savedTime = millis();
        }
    }
    ```

- Timer 객체
    - OOP_Timer.pde
        ``` java
        Timer timer;
        void setup(){
            size(240,240);
            background(0);
            timer = new Timer(5000);
            timer.Start();
        }
        void draw(){
            if(timer.IsFinished()){
                background(random(255));
                timer.Start();
            }
        }
        ```
    - Timer.pde
        ``` java
        class Timer{
            int savedTime;
            int totalTime;
            Timer(int tempTotalTime){
                totalTime = tempTotalTime;
            }
            void Start(){
                savedTime = millis();
            }
            boolean IsFinished(){
                int passedTime = millis()-savedTime;
                if(passedTime > totalTime){
                    return true;
                }else{
                    return false;
                }
            }
        }
        ```

- Rain Catcher Game
    - rainCatcherGame.pde
        ``` java
        Catcher catcher;
        Timer timer;
        Drop[] drops;
        int totalDrops = 0;
        void setup(){
            size(480,240);
            catcher = new Catcher(32);
            drops = new Drop[1000];
            timer = new Timer(300);
            timer.Start();
        }
        void draw(){
            background(255);
            catcher.SetLocation(mouseX,mouseY);
            catcher.Display();

            if(timer.IsFinished()){
                drops[totalDrops] = new Drop();
                totalDrops++;
                if(totalDrops >= drops.length){
                    totalDrops = 0;
                }
                timer.Start();
            }
            for(int i=0;i<totalDrops;i++){
                drops[i].Move();
                drops[i].Display();
                if(catcher.Intersect(drops[i])){
                    drops[i].Caught();
                }
            }
        }
        ```
    - Catcher.pde
        ``` java
        class Catcher{
            float r;
            color col;
            float x,y;
            Catcher(float _r){
                r = _r;
                col = color(50,10,10,150);
                x=0;
                y=0;
            }
            void SetLocation(float _x, float _y){
                x=_x;
                y=_y;
            }
            void Display(){
                stroke(0);
                fill(col);
                ellipse(x,y,r*2,r*2);
            }
            boolean Intersect(Drop drop){
                float distance = dist(x,y,drop.x,drop.y);
                if(distance < r + drop.r){
                    return true;
                }else{
                    return false;
                }
            }
        }
        ```
    - Drop.pde
        ``` java
        class Drop{
            float x,y;
            float speed;
            color c;
            float r;
            Drop(){
                r= 8;
                x =random(width);
                y = -r*4;
                speed = random(1,5);
                c = color(50,100,150);
            }
            void Move(){
                y+=speed;
            }
            boolean ReachedBottom(){
                if(y>height + r*4){
                    return true;
                }else{
                    return false;
                }
            }
            void Display(){
                fill(c);
                noStroke();
                for(int i=2; i<r;i++){
                    ellipse(x,y+i*4,i*2,i*2);
                }
            }
            void Caught(){
                speed =0;
                y = -1000;
            }
        }
        ```
    - Timer
        ``` java
        class Timer{
            int savedTime;
            int totalTime;
            Timer(int tempTotalTime){
                totalTime = tempTotalTime;
            }
            void Start(){
                savedTime = millis();
            }
            boolean IsFinished(){
                int passedTime = millis()-savedTime;
                if(passedTime > totalTime){
                    return true;
                }else{
                    return false;
                }
            }
        }
        ```

- Random Distribution
    ``` java
    float[] randomCounts;
    void setup(){
        size(480,240);
        randomCounts = new float[width/20];
    }
    void draw(){
        background(255);
        int index = int(random(randomCounts.length));
        randomCounts[index]++;

        stroke(0);
        fill(175);
        for(int x=0;x<randomCounts.length;x++){
            rect(x*20,0,19,randomCounts[x]);
        }
    }
    ```

- Noise
    ``` java
    float time =0.0;
    float increment = 0.01;
    void setup(){
        size(200,200);
    }
    void draw(){
        background(255);

        float n = noise(time)*width;
        time += increment;
        fill(0);
        ellipse(width/2,height/2,n,n);
    }
    ```

- Map
    ``` java
    void setup(){
        size(480,240);
    }
    void draw(){
        // mouseX에서 0까지의 값을 0~255로 remapping
        float r = map(mouseX,0,width,0,255);
        float b = map(mouseY,0,height,255,0);
        background(r,0,b);
    }
    ```

- Sin, Cos
    - Polar Cartesian
        ``` java
        float r=100;
        float theta = 0;
        void setup(){
            size(480,240);
            background(255);
        }
        void draw(){
            float x = r*cos(theta);
            float y = r*sin(theta);
            noStroke();
            fill(0);
            ellipse(x + width/2, y +height/2,16,16);
            theta += 0.01;
        }
        ```
    - Oscillation
        ``` java
        float theta = 0.0;
        void setup(){
            size(480,240);
        }
        void draw(){
            background(255);

            float x = (sin(theta)+1)*width/2;
            theta += 0.05;

            fill(0);
            stroke(0);
            line(width/2,0,x,height/2);
            ellipse(x,height/2,32,32);
        }
        ```
    - Wave
        ``` java
        float theta = 0.0;
        void setup(){
            size(480,240);
        }
        void draw(){
            background(255);
            theta+=0.02;
            noStroke();
            fill(0);
            float angle = theta;
            for(int x=0;x<=width;x+=10){
                float y = map(sin(angle),-1,1,0,height);
                ellipse(x,y,16,16);
                angle+=0.1;
            }
        }
        ```

- Recursion
    ``` java
    void setup(){
        size(480,240);
    }
    void draw(){
        background(255);
        stroke(0);
        noFill();
        drawCircle(width/2,height/2,300);

        void drawCircle(float x, float y, float radius){
            ellipse(x,y,radius,radius);
            if(radius>2){
                drawCircle(x+radius/2,y,radius/2);
                drawCircle(x-radius/2,y,radius/2);
            }
        }
    }
    ```

- 2D array
    ``` java
    size(200,200);
    int cols = width;
    int rows = height;

    int[][] myArray = new int[cols][rows];
    for(int i=0;i<cols;i++){
        for(int j=0;j<rows;j++){
            myArray[i][j] = int(random(255));
        }
    }
    for(int i=0;i<cols;i++){
        for(int j=0;j<rows;j++){
            stroke(myArray[i][j]);
            point(i,j);
        }
    }
    ```

- Grid Cells
    - gridCells.pde
        ``` java
        Cell[][] grid;
        int cols = 32;
        int rows = 18;
        void setup(){
            size(320,180);
            grid = new Cell[cols][rows];
            for(int i=0;i<cols;i++){
                for(int j=0;j<rows;j++){
                    grid[i][j] = new Cell(i*10,j*10,10,i+j);
                }
            }
        }
        void draw(){
            background(0);
            for(int i=0;i<cols;i++){
                for(int j=0;j<rows;j++){
                    grid[i][j].Oscillate();
                    grid[i][j].Display();
                }
            }
        }
        ```
    - Cell.pde
        ``` java
        class Cell{
            float x,y;
            float w,h;
            float angle;
            Cell(float _x, float _y, float _w, float _h,float _angle){
                x= _x;
                y= _y;
                w= _w;
                h= _h;
                angle = _angle;
            }
            void Oscillate(){
                angle+=0.02;
            }
            void Display(){
                stroke(255);
                float bright = map(sin(angle),-1,1,0,255);
                fill(bright);
                rect(x,y,w,h);
            }
        }
        ```