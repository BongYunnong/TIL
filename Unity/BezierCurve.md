# Bezier Curve 유니티
- 유튜버 Sebastian Lague님의 튜토리얼 참고
- https://github.com/SebLague/Curve-Editor
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
![E02_points](https://user-images.githubusercontent.com/11372675/148381037-ff78cad6-0b94-4c42-bb34-2826ed3c2043.png)
> p<sub>3</sub> + (p<sub>3</sub>-p<sub>2</sub>) = 2 * p<sub>3</sub> - p<xub>2</sub>

> (p<sub>4</sub> + p<sub>6</sub>)/2
- Path
    ```
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
    [System.Serializable]
    public class Path
    {
        [SerializeField, HideInInspector]
        List<Vector2> points;
        public Path(Vector2 centre)
        {
            points = new List<Vector2>
            {
                centre+Vector2.left,
                centre+(Vector2.left+Vector2.up)*0.5f,
                centre+(Vector2.right+Vector2.down)*0.5f,
                centre+Vector2.right
            };
        }
        public Vector2 this[int i]
        {
            get
            {
                return points[i];
            }
        }
        public int NumPoints
        {
            get
            {
                return points.Count;
            }
        }
        public int NumSegments
        {
            get
            {
                return (points.Count - 4) / 3 + 1;
            }
        }
        public void AddSegment(Vector2 anchorPos)
        {
            points.Add(points[points.Count - 1] * 2 - points[points.Count - 2]);
            points.Add((points[points.Count - 1] + anchorPos) * 0.5f);
            points.Add(anchorPos);
        }

        public Vector2[] GetPointsInSegment(int i)
        {
            return new Vector2[] { points[i * 3], points[i * 3 + 1], points[i * 3 + 2], points[i * 3 + 3] };
        }
        public void MovePoint(int i, Vector2 pos)
        {
            Vector2 deltaMove = pos - points[i];
            points[i] = pos;
            if (i % 3 == 0)
            {
                // anchor가 움직일 때 control도 함께 움직이도록
                if (i + 1 < points.Count)
                {
                    points[i + 1] += deltaMove;
                }
                if (i - 1 >= 0)
                {
                    points[i - 1] += deltaMove;
                }
            }
            else
            {
                // control이 움직이면 반대편에 있는 control도 함꼐 움직이도록
                bool nextPointIsAnchor = (i + 1) % 3 == 0;
                int correspondingControlIndex = (nextPointIsAnchor) ? i + 2 : i - 2;
                int anchorIndex = (nextPointIsAnchor) ? i + 1 : i - 1;
                if (correspondingControlIndex >= 0 && correspondingControlIndex < points.Count)
                {
                    float dst = (points[anchorIndex] - points[correspondingControlIndex]).magnitude;
                    Vector2 dir = (points[anchorIndex] - pos).normalized;
                    points[correspondingControlIndex] = points[anchorIndex] + dir * dst;
                }
            }
        }
    }
    ```
- PathCreator
    ```
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class PathCreator : MonoBehaviour
    {
        [HideInInspector]
        public Path path;

        public void CreatePath()
        {
            path = new Path(transform.position);
        }
    }
    ```
- PathEditor
    ```
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
    using UnityEditor;
    [CustomEditor(typeof(PathCreator))]
    public class PathEditor : Editor
    {
        PathCreator creator;
        Path path;
        private void OnSceneGUI()
        {
            Input();
            Draw();
        }
        void Input()
        {
            // Shift키를 누르고 마우스를 함께 누르면 segement 추가
            Event guiEvent = Event.current;
            Vector2 mousePos = HandleUtility.GUIPointToWorldRay(guiEvent.mousePosition).origin;

            if(guiEvent.type == EventType.MouseDown && guiEvent.button == 0 && guiEvent.shift)
            {
                Undo.RecordObject(creator, "Add Segement");
                path.AddSegment(mousePos);
            }
        }
        void Draw()
        {
            // Anchor-Control 사이의 Line, Bezier Curve Line 그리기
            for(int i = 0; i < path.NumSegments; i++)
            {
                Vector2[] points = path.GetPointsInSegment(i);
                Handles.color = Color.black;
                Handles.DrawLine(points[1], points[0]);
                Handles.DrawLine(points[2], points[3]);
                Handles.DrawBezier(points[0], points[3], points[1], points[2], Color.green, null, 2);
            }
            // Anchor 그리기
            Handles.color = Color.red;
            for(int i = 0; i < path.NumPoints; i++)
            {
                // Anchor는 Handle로, 움직일 수 있음
                Vector2 newPos =  Handles.FreeMoveHandle(path[i], Quaternion.identity, 0.5f, Vector2.zero, Handles.CylinderHandleCap);
                if(path[i] != newPos)
                {
                    Undo.RecordObject(creator, "Move point");
                    path.MovePoint(i, newPos);
                }
            }
        }
        private void OnEnable()
        {
            creator = (PathCreator)target;
            if (creator.path == null)
            {
                creator.CreatePath();
            }
            path = creator.path;
        }
    }
    ```
## #03 : Closed path and auto-controls
- path
    ```
    ...
    [SerializeField, HideInInspector]
    bool isClosed;
    [SerializeField, HideInInspector]
    bool autoSetControlPoints;
    ...
    public bool AutoSetControlPoints{
        get{
            return autoSetControlPoints;
        }
        set{
            if(autoSetControlPoints != value){
                autoSetControlPoints = value;
                if(autoSetControlPoints){
                    AutoSetAllControlPoints();
                }
            }
        }
    }
    public int NumSegments{
        get{
            //return (points.Count-4)/3 +1 + ((isClosed)?1:0);
            return points.Count/3;
        }
    }
    public void AddSegment(Vector2 anchorPos)
    {
        points.Add(points[points.Count - 1] * 2 - points[points.Count - 2]);
        points.Add((points[points.Count - 1] + anchorPos) * 0.5f);
        points.Add(anchorPos);

        if (autoSetControlPoints)
        {
            AutoSetAllAffectedControlPoints(points.Count - 1);
        }
    }
    ...
    public Vector2[] GetPointsInSegment(int i){
        //return new Vector2[] { points[i * 3], points[i * 3 + 1], points[i * 3 + 2], points[i * 3 + 3] };
        return new Vector2[] { points[i * 3], points[i * 3 + 1], points[i * 3 + 2], points[LoopIndex(i * 3 + 3)] };
    }
    public void MovePoint(int i, Vector2 pos)
    {
        Vector2 deltaMove = pos - points[i];

        if (i % 3 == 0 || !autoSetControlPoints)
        {
            points[i] = pos;

            if (autoSetControlPoints)
            {
                AutoSetAllAffectedControlPoints(i);
            }
            else
            {
                if (i % 3 == 0)
                {
                    // anchor가 움직일 때 control도 함께 움직이도록
                    if (i + 1 < points.Count || isClosed)
                    {
                        points[LoopIndex(i + 1)] += deltaMove;
                    }
                    if (i - 1 >= 0 || isClosed)
                    {
                        points[LoopIndex(i - 1)] += deltaMove;
                    }
                }
                else
                {
                    // control이 움직이면 반대편에 있는 control도 함꼐 움직이도록
                    bool nextPointIsAnchor = (i + 1) % 3 == 0;
                    int correspondingControlIndex = (nextPointIsAnchor) ? i + 2 : i - 2;
                    int anchorIndex = (nextPointIsAnchor) ? i + 1 : i - 1;
                    if (correspondingControlIndex >= 0 && correspondingControlIndex < points.Count || isClosed)
                    {
                        float dst = (points[LoopIndex(anchorIndex)] - points[LoopIndex(correspondingControlIndex)]).magnitude;
                        Vector2 dir = (points[LoopIndex(anchorIndex)] - pos).normalized;
                        points[LoopIndex(correspondingControlIndex)] = points[LoopIndex(anchorIndex)] + dir * dst;
                    }
                }
            }
        }
    }
    public void ToggleClosed(){
        isClosed = !isClosed;
        if (isClosed)
        {
            // 닫혀있다면, points에 마지막것과 첫번째 것을 연결해줘야함
            points.Add(points[points.Count - 1] * 2 - points[points.Count - 2]);
            points.Add(points[0] * 2 - points[1]);
            if (autoSetControlPoints)
            {
                AutoSetAnchorControlPoints(0);
                AutoSetAnchorControlPoints(points.Count-3);
            }
        }
        else
        {
            // 닫혀있지 않다면, 마지막 2개(닫기 위해 존재하는 points)는 삭제 
            points.RemoveRange(points.Count - 2, 2);
            if (autoSetControlPoints)
            {
                AutoSetStartAndEndControls();
            }
        }
    }
        void AutoSetAllAffectedControlPoints(int updatedAnchorIndex)
    {
        for(int i= updatedAnchorIndex - 3; i <= updatedAnchorIndex + 3; i += 3)
        {
            if(i>=0 && i<points.Count || isClosed)
            {
                AutoSetAnchorControlPoints(LoopIndex(i));
            }
        }
        AutoSetStartAndEndControls();
    }
    void AutoSetAllControlPoints()
    {
        for(int i = 0; i < points.Count; i+=3)
        {
            AutoSetAnchorControlPoints(i);
        }
        AutoSetStartAndEndControls();
    }

    void AutoSetAnchorControlPoints(int anchorIndex)
    {
        Vector2 anchorPos = points[anchorIndex];
        Vector2 dir = Vector2.zero;
        float[] neighbourDistances = new float[2];

        if (anchorIndex - 3 >= 0 || isClosed)
        {
            Vector2 offset = points[LoopIndex(anchorIndex - 3)] - anchorPos;
            dir += offset.normalized;
            neighbourDistances[0] = offset.magnitude;
        }
        if (anchorIndex + 3 >= 0 || isClosed)
        {
            Vector2 offset = points[LoopIndex(anchorIndex + 3)] - anchorPos;
            dir -= offset.normalized;
            neighbourDistances[1] = -offset.magnitude;
        }
        dir.Normalize();
        for(int i = 0; i < 2; i++)
        {
            int controlIndex = anchorIndex + i * 2 - 1;
            if(controlIndex >= 0 && controlIndex < points.Count || isClosed)
            {
                points[LoopIndex(controlIndex)] = anchorPos + dir * neighbourDistances[i] * 0.5f;
            }
        }
    }
    void AutoSetStartAndEndControls()
    {
        if (!isClosed)
        {
            points[1] = (points[0] + points[2]) * 0.5f;
            points[points.Count - 2] = (points[points.Count - 1] + points[points.Count - 1]) * 0.5f;
        }
    }
    public int LoopIndex(int i){
        return (i+points.Count)%points.Count;
    }
    ```
- open
    - 4/3 -> 1
    - 7/3 -> 2
    - 10/3 -> 3
- closed
    - 6/3 -> 2
    - 9/3 -> 3
    - 12/3 -> 4
- path Editor
    ```
    ...
    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();

        EditorGUI.BeginChangeCheck();
        if (GUILayout.Button("Create new"))
        {
            Undo.RecordObject(creator, "Create New");
            creator.CreatePath();
            path = creator.path;
        }

        if (GUILayout.Button("Toggle closed"))
        {
            Undo.RecordObject(creator, "Toggle closed");
            path.ToggleClosed();
            SceneView.RepaintAll();
        }
        bool autoSetControlPoints = GUILayout.Toggle(path.AutoSetControlPoints, "Auto Set Control Points");
        if(autoSetControlPoints != path.AutoSetControlPoints){
            Undo.RecordObject(creator, "Toggle auto set controls");
            path.AutoSetControlPoints = autoSetControlPoints;
        }
        if(EditorGUI.EndChangeCheck()){
            SceneView.RepaintAll();
        }
    }
    ...
    ```
## #04 : Inserting and Deleting Points
- 어떠한 Anchor를 삭제하려면 보통의 경우는 i-1, i, i+1 point를 삭제해야한다.
    - i가 0일 경우에는 0,1,2를 삭제해야한다.
    - i가 마지막일 경우에는 count-1,count-2,count-3을 삭제해야한다.
- 그런데 닫혀있는 경우에는, 0번째 점을 삭제하면 다음 anchor의 앞 control이 0번째가 되어버린다.
    - 0번 anchor의 -1 control을 1번 anchor의 -1 control로 이동시키고, 0번 anchor와 1 controll을 삭제하면 된다.
- path
```
public void DeleteSegment(int anchorIndex){
        if(NumSegments > 2 || !isClosed && NumSegments>1){
        if(anchorIndex==0){
            if(isClosed){
                points[points.Count-1] = points[2];
            }
            points.RemoveRange(0,3);
        }else if(anchorIndex == points.Count-1 && !isClosed){
            points.RemoveRange(anchorIndex-2,3);
        }else{
            points.RemoveRange(anchorIndex-1,3);
        }
    }
}
```
- PathEditor
```
void Input(){
    ...
    if(guiEvent.type==EventType.MouseDown && guiEvent.button==1){
        float minDstToAnchor = 0.05f;
        int closestAnchorIndex = -1;
        for(int i=0;i<path.NumPoints;i++){
            float dst = Vector2.Distance(mousePos,path[i]);
            if(dst<minDstToAnchor){
                minDstToAnchor = dst;
                closestAnchorIndex = i;
            }
        }
        if(closestAnchorIndex != -1){
            Undo.RecordObject(creator,"Delete segment");
            path.DeleteSegment(closestAnchorIndex);
        }
    }
}
```
- toggle Closed 삭제하고 property로 전환
- path
```
    public bool IsClosed
    {
        get
        {
            return isClosed;
        }
        set
        {
            if(isClosed != value)
            {
                isClosed = value;
                if (isClosed)
                {
                    // 닫혀있다면, points에 마지막것과 첫번째 것을 연결해줘야함
                    points.Add(points[points.Count - 1] * 2 - points[points.Count - 2]);
                    points.Add(points[0] * 2 - points[1]);
                    if (autoSetControlPoints)
                    {
                        AutoSetAnchorControlPoints(0);
                        AutoSetAnchorControlPoints(points.Count - 3);
                    }
                }
                else
                {
                    // 닫혀있지 않다면, 마지막 2개(닫기 위해 존재하는 points)는 삭제 
                    points.RemoveRange(points.Count - 2, 2);
                    if (autoSetControlPoints)
                    {
                        AutoSetStartAndEndControls();
                    }
                }
            }
        }
    }
```
- Path Editor
```
...OnInspectorGUI()...
        bool isClosed = GUILayout.Toggle(path.IsClosed, "Closed");
        if (isClosed != path.IsClosed)
        {
            Undo.RecordObject(creator, "Toggle closed");
            path.IsClosed = isClosed;
        }
```
- 새 anchor 삽입하기
```
    public void SplitSegment(Vector2 anchorPos, int segmentIndex)
    {
        points.InsertRange(segmentIndex * 3 + 2, new Vector2[] { Vector2.zero, anchorPos, Vector2.zero });
        if (autoSetControlPoints)
        {
            AutoSetAllAffectedControlPoints(segmentIndex * 3 + 3);
        }
    }
```
- Path Editor
```
    const float segmentSelectDistanceThreshold = 0.1f;
    int selectedSegmentIndex = -1;
    ...
    ...Input()...
    if(guiEvent.type == EventType.MouseDown && guiEvent.button == 0 && guiEvent.shift)
    {
        if (selectedSegmentIndex != -1)
        {
            Undo.RecordObject(creator, "Split Segement");
            path.SplitSegment(mousePos, selectedSegmentIndex);
        }
        else if(!path.isClosed)
        {
            Undo.RecordObject(creator, "Add Segement");
            path.AddSegment(mousePos);
        }
    }
    ...
    if (guiEvent.type == EventType.MouseMove)
    {
        float minDstToSegment = segmentSelectDistanceThreshold;
        int newSelectedSegmentIndex = -1;
        for (int i = 0; i < path.NumSegments; i++)
        {
            Vector2[] points = path.GetPointsInSegment(i);
            float dst = HandleUtility.DistancePointBezier(mousePos, points[0], points[3], points[1], points[2]);
            if (dst < minDstToSegment)
            {
                minDstToSegment = dst;
                newSelectedSegmentIndex = i;
            }
        }
        if(newSelectedSegmentIndex != selectedSegmentIndex)
        {
            selectedSegmentIndex = newSelectedSegmentIndex;
            HandleUtility.Repaint();
        }
    }
    ...
```
- 색깔 변경하기
- path creator
```
    public Color anchorColor = Color.red;
    public Color controlColor = Color.white;
    public Color segmentColor = Color.green;
    public Color selectedSegmentCol = Color.yellow;
    public float anchorDiameter = 0.5f;
    public float controlDiameter = 0.25f;
    public bool displayControlPoints = true;

```
- pathEditor
```
    void Draw()
    {
        // Anchor-Control 사이의 Line, Bezier Curve Line 그리기
        for(int i = 0; i < path.NumSegments; i++)
        {
            Vector2[] points = path.GetPointsInSegment(i);
            if(creator.displayControlPoints){
                Handles.color = Color.black;
                Handles.DrawLine(points[1], points[0]);
                Handles.DrawLine(points[2], points[3]);
            }
            Color segmentColor = (i == selectedSegmentIndex && Event.current.shift) ? creator.selectedSegmentCol: creator.segmentColor;
            Handles.DrawBezier(points[0], points[3], points[1], points[2], segmentColor, null, 2);
        }
        // Anchor 그리기
        for(int i = 0; i < path.NumPoints; i++)
        {
            if (i % 3 == 0 || creator.displayControlPoints)
            {
                Handles.color = (i % 3 == 0) ? creator.anchorColor : creator.controlColor;
                float handleSize = (i % 3 == 0) ? creator.anchorDiameter : creator.controlDiameter;
                // Anchor는 Handle로, 움직일 수 있음
                Vector2 newPos = Handles.FreeMoveHandle(path[i], Quaternion.identity, handleSize, Vector2.zero, Handles.CylinderHandleCap);
                if (path[i] != newPos)
                {
                    Undo.RecordObject(creator, "Move point");
                    path.MovePoint(i, newPos);
                }
            }
        }
    }
```
- Reset
- path creator
```
    private void Reset()
    {
        CreatePath();
    }
```
- path Editor
```
    Path Path
    {
        get
        {
            return creator.path;
        }
    }
```


## #05 : Evenly Spaced Points
```
public class Bezier
{
    public static Vector2 EvaluateQuadratic(Vector2 a, Vector2 b, Vector2 c, float t)
    {
        Vector2 p0 = Vector2.Lerp(a, b, t);
        Vector2 p1 = Vector2.Lerp(b, c, t);
        return Vector2.Lerp(p0, p1, t);
    }
    public static Vector2 EvaluateCubic(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float t)
    {
        Vector2 p0 = EvaluateQuadratic(a, b, c, t);
        Vector2 p1 = EvaluateQuadratic(b, c, d, t);
        return Vector2.Lerp(p0, p1, t);
    }
}
```
- path
```
    public Vector2[] CalculateEvenlySpacedPoints(float spacing, float resolution = 1)
    {
        List<Vector2> evenlySpacedPoints = new List<Vector2>();
        evenlySpacedPoints.Add(points[0]);
        Vector2 previousPoint = points[0];
        float dstSinceLastEvenPoint = 0;
        for(int segmentIndex = 0; segmentIndex < NumSegments; segmentIndex++)
        {
            Vector2[] p = GetPointsInSegment(segmentIndex);
            float controlNetLength = Vector2.Distance(p[0], p[1]) + Vector2.Distance(p[1], p[2]) + Vector2.Distance(p[2], p[3]);
            float estimatedCurveLength = Vector2.Distance(p[0], p[3]) + controlNetLength / 2f;
            int divisions = Mathf.CeilToInt(estimatedCurveLength * resolution * 10f);
            float t = 0;
            while (t <= 1)
            {
                t += 1f / divisions;
                Vector2 pointOnCurve = Bezier.EvaluateCubic(p[0], p[1], p[2], p[3], t);
                dstSinceLastEvenPoint += Vector2.Distance(previousPoint, pointOnCurve);
                while(dstSinceLastEvenPoint >= spacing)
                {
                    float overShootDst = dstSinceLastEvenPoint - spacing;
                    Vector2 newEvenlySpacedPoint = pointOnCurve + (previousPoint - pointOnCurve).normalized * overShootDst;
                    evenlySpacedPoints.Add(newEvenlySpacedPoint);
                    dstSinceLastEvenPoint = overShootDst;
                    previousPoint = newEvenlySpacedPoint;
                }
                previousPoint = pointOnCurve;
            }
        }
        return evenlySpacedPoints.ToArray();
    }
```
- BezierMobingPlatform
```
    void Start()
    {
        pathCreator = GetComponent<PathCreator>();
        points = pathCreator.path.CalculateEvenlySpacedPoints(spacing, resolution);
        //foreach(Vector2 p in points)
        //{
        //    GameObject g = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        //    g.transform.position = p;
        //    g.transform.localScale = Vector3.one * spacing * 0.5f;
        //}
    }
```