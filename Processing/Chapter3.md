# Processing #3
## Function
- using function
    ``` java
    int x=0;
    int speed=1;
    void setup(){
        size(480,240);
    }
    void draw(){
        background(255);
        Move();
        Bounce();
        Display();
        println(distance(width/2,height/2,mouseX,mouseY));
    }
    void Move(){
        x+=speed;
    }
    void Bounce(){
        if((x>width) || (x<0)){
            speed = speed * -1;
        }
    }
    void Display(){
        stroke(0);
        fill(175);
        ellipse(x,height/2,32,32);
    }
    float distance(float x1,float y1,float x2, float y2){
        float distX = x1-x2;
        float distY = y1-y2;
        float dist = sqrt(distX*distX + distY*distY);
        return dist;
    }
    ```

## Object
- Single Object
    ``` java
    class Box{
        color myColor;
        float xPos;
        float yPos;
        float xSpeed;
        float ySpeed;

        Box(){
            myColor = color(100);
            xPos = width/2;
            yPos = height/2;
            xSpeed=1;
            ySpeed=1;
        }
        void Display(){
            ellipseMode(CENTER);
            stroke(0);
            fill(myColor);
            ellipse(xPos,yPos,20,20);
        }
        void Move(){
            xPos = xPos + xSpeed;
            if(xPos > width){
                xPos = 0;
            }
            yPos = yPos + ySpeed;
            if(yPos > height){
                yPos = 0;
                xPos += 30;
            }
        }
    }
    Box box;
    void setup(){
        size(480,240);
        box = new Box();
    }
    void draw(){
        background(255);
        box.Move();
        box.Display();
    }
    ```
- Two Objects
    ``` java
    class Box{
        color myColor;
        float xPos;
        float yPos;
        float xSpeed;
        float ySpeed;

        Box(color _color, float _x, float _y, float _speed){
            myColor = _color;
            xPos = _x;
            yPos = _y;
            xSpeed=_speed;
            ySpeed=_speed;
        }
        void Display(){
            ellipseMode(CENTER);
            stroke(0);
            fill(myColor);
            ellipse(xPos,yPos,20,20);
        }
        void Move(){
            xPos = xPos + xSpeed;
            if(xPos > width){
                xPos = 0;
            }
            yPos = yPos + ySpeed;
            if(yPos > height){
                yPos = 0;
                xPos += 30;
            }
        }
    }
    Box box1;
    Box box2;
    void setup(){
        size(480,240);
        box1 = new Box(color(40),10,20,5);
        box2 = new Box(color(150),50,80,2);
    }
    void draw(){
        background(255);
        box1.Move();
        box1.Display();
        box2.Move();
        box2.Display();
    }
    ```