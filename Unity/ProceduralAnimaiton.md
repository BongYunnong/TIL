# Creating a boss with procedural animation | Prototype Series
- https://learn.unity.com/tutorial/using-animation-rigging-damped-transform

## Building the player movement
- Airplane을 3인칭으로 두고, Cinemachine을 사용
- Airplane회전
    ``` C#
    void TurnSpaceship(){
        Vector3 newTorque = new Vector3(data.steeringInput.x * data.pitchSpeed, -data.steeringInput.z*data.yawSpeed,0);
        spaceshipRigidbody.AddRelativeTorque(newTorque);
    }
    
    void VisualSpaceshipTurn(){
        shipModel.localEulerAngles = new Vector3(data.steeringInput.x * data.leanAmount_Y,shipModel.localEulerAngles.y,data.steeringInput.z*data.leanAmount_x);
    }
    ```
## Damped Transform
- Animation을 만들 필요 없이 Procedural하게 Animation 만들 수 있음

## Enemy Movement
``` C#
Vector3 playerPosition = playerShip.transform.position + (playerShip.spaceshipRigidbody.velocity*3);
playerPosition.y = Mathf.Max(10,playerPosition.y);
Vector3 randomRange = Random.insideUnitSphere*100;
randomRange.y=0;
startPosition = playerPosition + randomRange;
endPosition = palyerPosition - randomRange;
if(Physics.Raycast(startPosition,Vector3.down,out hitInfo, 1000, terrainlayer.value)){
    startPosition = hitInfo.point;
}
if(Physics.Raycast(endPosition,Vector3.down,out hitInfo, 1000, terrainLayer.value)){
    endPosition = hitInfo.point;
}
path.m_Waypoints[0].position = startPosition + (Vector3.down*15);
path.m_Waypoints[1].position = playerPosition + (Vector3.up * 10);
path.m_Waypoints[2].position = endPosition + (Vector3.down*45);

path.InvalidateDistanceCache();
cart.m_Position = 0;
```

## effect 주기
``` C#
GetComponent<CinemachineImpulseSource>().GenerateImpulse();
```

## Character Bone 설정
- Character에 'Bone Renderer'를 설정하고 transforms에 Bone을 넣기
    - 이렇게 하면 Bone을 Scene View에서 확인할 수 있음
- Character에 Rig Builder를 추가
    - 자식으로 빈 오브젝틀르 만들고 Rig 컴포넌트 추가
    - Rig Builder의 Rig Layers 속성에 Rig 추가 가능
- Rig 컴포넌트가 있는 오브젝트 하위에 빈 오브젝트 생성(Damped)
    - Damped에 Damped Transform 컴포넌트 추가
        - Constrained Object - The GameObject affected by the source GameObjects;
        - Source - The GameObject that affects the constrained GameObject
        - Damp Position - Damp Position Weight.
        - Damp Rotation - Damp Rotation weight
    - 첫 번째 damped는 Sourc에 Head, Constrained Object에 Worm Body를 둠
    - DampPosition은 0, DampRotation은 0.5로 둠
    - 나머지 bone들도 반복

# Walkable
## setup
- Animaiton Rigging Package
- Character에는 Rig Builder가 있음
- 평범한 Rigged 모델과 Rig 오브젝트 하위에 제작된 IK 관련 bone 오브젝트들
    - Rig는 Rig 컴포넌트
    - Rig 하위의 어떠한 오브젝트는(ex. Leg_L_IK_target) IK Foot Solver 사용
## IKFootSolver
``` C#
[SerializeField] LayerMask terrainLayer = default;
[SerializeField] Transform body = default;
[SerializeField] IKFootSolver otherFoot = default;
[SerializeField] float speed =1;
[SerializeField] float stepDistance = 4;
[SerializeField] float stepLength = 4;
[SerializeField] float stepHeight = 1;
[SerializeField] Vector3 footOffset default;
float footSpacing;
Vector3 oldPosition, currentPosition, newPosition;
Vector3 oldNormal, currentNormal, newNormal;
float lerp;

private void Start(){
    footSpacing = transform.localPposition.x;
    currentPosition = newPosition = oldPosition = transform.position;
    currentNormal = newNormal = oldNormal = transform.up;
    lerp = 1;
}

void Update(){
    transform.position = currentPosition;
    transform.up = currentNormal;

    Ray ray = new Ray(body.position + (body.right*footSpacing),Vector3.down);
    if(Physics.Raycast(ray,out RaycastHit info, 10, terrainLayer.value)){
        if(Vector3.Distance(newPosition, info.point)>stepDistance && !otherFoot.IsMoving() && lerp >=1){
            lerp = 0;
            int direction = body.InverseTransformPoint(info.point).x > body.InverseTransformPoint(newPosition).z ? 1 : -1;
            newPosition = info.point + (body.forward*stepLength *direction) +footoffset;
            newNormal = info.normal;
        }
    }

    if(lerp<1){
        Vector3 tempPosition = Vector3.Lerp(oldPosition, newPosition, lerp);
        tempPosition.y += Mathf.Sin(lerp * Mathf.PI)*stepHeight;

        currentPosition = tempPosition;
        currentNormal = Vector3.Lerp(oldNormal, newNormal, lerp);
        lerp += Time.deltaTime * speed;
    }
    else{
        oldPosition = newPosition;
        oldNormal = newNormal;
    }
    private void OnDrawGizmos(){
        Gizmos.color = Color.red;
        Gizmos.DrawSphere(newPosition,0.5f);
    }
    public bool IsMoving(){
        return lerp<1;
    }
}

```

## Rig Effectors
- Bone처럼 user가 보고 움직일 수 있는 Gizmo
- Rig Builder나 Rig Component에 위치할 수 있음
- 게임뷰에서는 보이지 않음

## Rig Constraints
- Assemble Rigs, Produce Procedural motion at runtime
- Blend Constraint
- Chain IK Constraint
- Damped Transform
- Multi-Aim Contraint
- Multi-Parent Constraint
- Multi-Position Constraint
- Multi-Referential Constraint
- Multi-Rotation Constraint
- Override Transform
- Twist Correction
- Two Bone IK Constraint

## Two Bone IK Constraint
1. Reset Bone Pose - AnimationRigging>RestoreBindPose
2. Character 오브젝트 하위에 "CharacterRig"라는 빈 오브젝트 생성
3. CharacterRig 하위에 "Rig Arm IK"라는 빈 오브젝트 생성
4. Right Arm IK 아래에 두개의 빈 오브젝트 생성("RH IK Target", "RH IK Hint")
5. Animator Root에 Rig Builder 넣기
6. CharacterRig에 Rig Component 넣기
7. Right Arm IK에 Two Bone IK Constraint Component 추가
8. RH IK Target에 Box Effector 추가
9. Box Effector와 Right Hand bone을 동시에 선택
10. Animation Rigging 메뉴에서 Align Transform 선택
    - Effector가 Hand에 Align됨
11. RH IK Hint 선택하여 Ball Effector 추가
    - 팔꿈치 조정
12. Effector를 팔꿈치에서 좀 떨어뜨림
13. RightArm IK 선택하고 Two Bone IK Constraint에 알맞게 추가
    - Root : RightUpperArm
    - Mid : RightLowerArm
    - Tip : RightHand
    - SourceObjects
        - Target : RH IK Target
        - Hint : RH IK Hint
14. Rig Builder에 Rig 컴포넌트 채우기

# Unity Procedural animation tutorial(10steps)
- https://youtu.be/e6Gjhr1IP6w
1. Use Inverse Kinematics to control Rig
2. Fix bottom of the leg to the ground
3. Make a target point attached to the body
4. Raycast from the target point downwards to move it up & down
5. Check distance from target point
6. Move leg towards target when distance gets to long
7. Put Leg as Zigzag Pattern
8. Only move leg when opposite legs are grounded(smae clip)
9. Use average leg position + offset for the body position
10. Rotate body based on difference between left and right leg height
