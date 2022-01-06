# Bezier Curve 유니티
- 유튜버 Sebastian Lague님의 튜토리얼 참고
## #01 : Introduction and Concepts
- lerp
    ```
    public static Vector2 Lerp(Vector2 a, Vector2 b, float t){
        return a + (b-a) * t;
    }
    ```
    - t가 0에서 1까지, 0이면 초기, 1이면 끝점에 도달
- Quadratic Curve
    ```
    public static Vector2 Lerp(Vector2 a, Vector2 b, float f){
        return a + (b-a) * t;
    }
    public static Vector2 QuadraticCurve(Vector2 a, Vector2 b, Vector2 c, float t){
        Vector2 p0 = Lerp(a,b,t);
        Vector2 p1 = Lerp(b,c,t);
        return Lerp(p0,p1,t);
    }
    ```
    - A에서 B로 Lerp, B에서 C로 Lerp하는 점을 기준으로 Lerp를 하면, A에서 C로 진행하되, B의 영향을 받는 곡선이 만들어진다.
    > (1-t)<sup>2</sup>A + 2(1-t)tB + t<sup>2</sup>C
- Cubic Curve
    ```
    public static Vector2 Lerp(Vector2 a, Vector2 b, float f){
        return a + (b-a) * t;
    }
    public static Vector2 QuadraticCurve(Vector2 a, Vector2 b, Vector2 c, float t){
        Vector2 p0 = Lerp(a,b,t);
        Vector2 p1 = Lerp(b,c,t);
        return Lerp(p0,p1,t);
    }
    public static Vector2 CubicCurve(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float t){
        Vector2 p0 = QuadraticCurve(a,b,c,t);
        Vector2 p1 = QuadraticCurve(b,c,d,t);
        return Lerp(p0,p1,t);
    }
    ```
    - A에서 D까지 진행하되, B와 C의 영향을 받는 곡선이 만들어진다.
    >  (1-t)<sup>3</sup>A + 3(1-t)<sup>2</sup>tB + 3(1-t)t<sup>2</sup>C + t<sup>3</sup>D
- 점이 지나는 point는 Anchor, 지나지는 않고 영향을 주는 point는 Control이라 하자
    - anchor가 3개라면, control은 4개가 필요(A 1개, B 2개, C 1개)
## #02 : Adding and Moving Points
```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
[System.Serializable]
public class Path{
    [SerializeField, HideInI]
}
```
![E02_points](./Unity/E02_points.png)