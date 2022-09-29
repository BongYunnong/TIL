# My Fault2 - 스스로 불러온 재앙2
------------------
## SetTimer - Multiple Parameter
- 파라미터 사용하는 Timer
``` C++
void AMyGameMode::RespawnPlayerWithDelay(APlayerController * Player, float Delay)
{
	FTimerHandle UniqueHandle;
    // Delegate를 사용해서 파라미터를 가지는 함수를 Call
	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject( this, &AMyGameMode::RespawnPlayer, Player );
	GetWorldTimerManager().SetTimer(UniqueHandle, RespawnDelegate, Delay, false );
}
```

## Log 출력 시, FString, FName 등 처리
- Log는 TEXT("...")이런 FText형식으로 들어가게 된다.
- FString, FName은 들어갈 수가 없는데,이런 경우에는 
    - 이런식으로 *를 붙여주면 된다.
    ``` C++
    UE_Log(LogTemp,Log,TEXT("...%s"),*(GetActor()->GetName()));
    ```

## Enum(열거형)
- 그냥 enum으로 열거형을 만들면 Blueprint나 다른 곳에서 사용불가
    - BlueprintType를 써주자
``` C++
UENUM(BlueprintType)
enum class EPrototypePlayState : uint8 {
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};
...
EPrototypePlayState currentState;
```

## struct(구조체)
- 그냥 struct로 구조체를 만들면 Blueprint나 다른 곳에서 사용불가
    - BlueprintType를 써주자
``` C++
USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase {
	GENERATED_BODY()
public:
	FCharacterInfo() {
		CharacterName = FText::FromString("Name");
		CharacterLevel = 1;
		Description = FText::FromString("Your Character is ....");
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CharacterThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
};
```

## DamageType
- TakeDamage를 보면 DamageEvent에 DamageType 값을 넣어서 전달되는 것을 알 수 있다.
- DamageType은 Damage를 불러일으킨 공격의 Type이 어떤 것인지 판단하는데 유용하다.
    - 예를 들면 불속성 공격, 폭발 공격 등등이 있겠다.
``` C++
UCLASS()
class PROTOTYPE_API UAirborneDamgeType : public UDamageType
{
	GENERATED_BODY()
};
```
- .cpp 파일에서 뭔가 더 할수도 있을 듯 하다.


## Anim Retarget
- 블렌더에서 UE마네킹의 Bone구조를 가져와서 리깅을 했음에도 불구하고 다시 언리얼로 Import해보면 엄청나게 깨지는 현상을 볼 수 있다.
    - 보통 무료로 얻을 수 있는 애니메이션들은 UE4마네킹에 최적화되어있다.
    - 그러니 UE4마네킹에 우선적으로 리타겟팅을 하고, 그 애니메이션을 다시 내 모델에 리타겟팅 하면 큰 문제 없이 리타겟팅이 된다.
- UE마네킹의 Bone구조에는 ArmTwist같은 Bone들이 있는데, 어떤 애니메이션은 이 Twist 본이 엄청 이상한 곳으로 가있어서, 여기에 Weight Painting이 된 vertex들이 난리나는 경우가 있다.
    - 이것은 Blender에서 Automatic으로 한 후에 다시 Twist같은 쓸데없는 Bone에 대해서 weight를 해제해주면 된다.

## Blender To Unreal
- Python 플러그인이 있으니 확인해보자.
- blender에서 fbx로 Export한 후에 Unreal에 import를 하면 다음부터 같은 경로의 애셋은 바꿔치기가 된다.
    - 이미 Animation이나 PhysicsAsset이 만들어진 모델에 대해서도 잘 작동한다.
    - 물론 Texture도 쉽게 바꿔치기가 가능하다.

## AnimMontage
- Montage에는 Notify를 설정할 수 있고, 그러면 AnimBP에서 Event로 이벤트를 받을 수 있다.

## ComponentClass의 Instance
- AddRadialImpulse를 Explosion_BP에 넣어놨었는데, AddRadialImpulse의 값으로 들어가야 할 DamageType이 컴파일을 할 때마다 Missing이 되었다.
    - 이것에 DamageType이 Blueprint가 아니라서 그런 줄 알고 BP로 만든 후 넣어봐도 똑같았다.
    - 이것은 옛날에 SFX, VFX등을 콘텐츠 경로를 찾아서 Constructor에서 직접 집어넣어준 방법을 활용해서 해결하였다.
    ``` C++
    static ConstructorHelpers::FClassFinder<UDamageType> AirbornBPClass(TEXT("/Game/Blueprint/AirborneDamageType_BP"));
	if (AirbornBPClass.Class != NULL)
	{
		damageType = AirbornBPClass.Class;
	}
    ```

## TArray
- Unity에서 Array나 List가 있다면 여기에는 TArray가 있다.
- Loop
    - for문으로 사용해보자.
    ```C++
	TArray<AActor*> tmpActors;
    for(AActor* a : tmpActors){
        a->GetLocation();
        ...
    }
    ``` 

## PredictProjectile
- 블루프린트에서 처음 보고 C++로 전환하려했는데, Parameter와 Result를 제대로 넣었음에도 실제 실행해보면 Result가 나오지 않았다.
    - 이것은 Blueprint에서 PredictProjectile이 ByObject, ByTrace 2개 버전이 있는 것을 보고 단서를 찾았다.
    - 알고보니 Parameter에 Object를 쓸지 Trace를 쓸 지 정하는 bool값이 있었다.
    - Object를 설정해주니 해결이 되었다.
- ObjectType
    - PredictProjectile은 목표 Object나 Trace를 설정할 수 있다.
    - 아래처럼 선언해서 넣어주자.
    ``` C++
    -- h --
	UPROPERTY(EditAnywhere, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
		TArray<TEnumAsByte<EObjectTypeQuery>> PredictProjectileObstacleQuery;
    -- cpp --
    FPredictProjectilePathParams projectileParams(10.0f, startTR.GetLocation() + startTR.GetRotation().RotateVector(CannonStartOffset), LaunchVelocity,20.0f);
    projectileParams.OverrideGravityZ = GetWorld()->GetGravityZ();
    projectileParams.ObjectTypes = PredictProjectileObstacleQuery;
    projectileParams.bTraceWithCollision = true;
    ```
    - 참고로 Channel을 사용한다면 ECollisionChannel이다.

## FVector를 Relative하게 변환하기
- Cannon을 만들었는데 Socket에 바로 부착을 해버리니 캐릭터 애니메이션에 따라 CannonStart location이 변했다.
    - 이것을 해결하기 위해서는 Cannon을 가진 Owner Pawn의 위치에 일정한 상대벡터를 더해서 거기서 생성을 하는 것이 맞다고 생각했다.
    ``` C++
    FVector currTR = MyPawn->GetActorLocation() + MyPawn->GetActorRotation().RotateVector(CannonStartOffset);
    ```


## Interface
- 인터페이스를 상속받으면 아래처럼 인터페이스에서 정의한 함수와, 그 함수의 이름에 _Implementation이 붙은 함수를 선언, 정의해야한다.
``` C++
UFUNCTION(BlueprintCallable, Category = "Combat")
    void Attack();
virtual void Attack_Implementation();
``` 
- 호출은 아래와 같다.
    - 클래스가 Interface를 가지고있는지 확인한 후 Execute하는 방식이다.
    ``` C++
    void APrototypeCharacter::AttackEvent()
    {
        UE_LOG(LogTemp, Log, TEXT("Fire!!"));
        if (CurrentWeapon != NULL && attackCoolTime >= attackMaxCoolTime) {
            if (GetClass()->ImplementsInterface(UCombatInterface::StaticClass()))
            {
                ICombatInterface::Execute_Attack(this);
            }
        }
    }
    ```

## Visibility, HideInGame
- Component는 Visibility, Actor는 HideInGame이다.
- Component로 투명화하고싶다면 아래처럼 GetRootComponent를 활용하면 된다.
``` C++
CannonTrail[i]->GetRootComponent()->SetVisibility(false);
```

## UCurveFloat
- Zoom In,Out과 ViewTransition을 만들고싶었는데, Blueprint의 Timeline을 어떻게 만들까 싶었다.
- Content브라우저에서 FloatCurve나 VectorCurve등을 만들 수 있다.
    - C++에서 이 애셋을 참조해서 사용할 수 있도록 하자.
    ``` C++
    class UCurveFloat;
    ...
    FOnTimelineFloat TimelineProgress; // Progress가 진행함에 따라 호출할 함수 모음
	FTimeline CurveTimeline;
	UPROPERTY(EditDefaultsOnly, Category = "Timeline")
		UCurveFloat* CurveFloat;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline", meta = (AllowPrivateAccess = "true"))
		float LerpTimelineLength;
	bool bViewTransitionActivated;
    ```
    - CurveFloat과 TimelineProgress를 인자로 받은 것을 볼 수 있다.
    ``` C++
	if (CurveFloat) {
		//FOnTimelineEventStatic LerpTimelineFinishedCallback;
		TimelineProgress.BindUFunction(this, FName("ViewTransitionTimelineProgress"));
		
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		//CurveTimeline.SetTimelineFinishedFunc(LerpTimelineFinishedCallback);

		CurveTimeline.SetTimelineLength(LerpTimelineLength);
	}
    ...
    void APrototypeCharacter::Tick(float DeltaTime) {
        Super::Tick(DeltaTime);
        
        CurveTimeline.TickTimeline(DeltaTime);
    }
    ```
    - 여기서 FOnTimelineEventStatic은 Timeline이 끝났을 때 함수를 호출할 수 있다.
    - Tick에서 DelatTime을 먹여줘야 정상적으로 작동할 수 있다.
    ``` C++
    void APrototypeCharacter::StartViewTransition()
    {
        bViewTransitionActivated = !bViewTransitionActivated;
        if (bViewTransitionActivated)
            CurveTimeline.ReverseFromEnd();
        else
            CurveTimeline.PlayFromStart();
    }
    ```
    - Timeline의 시작은 위처럼 하면 된다.
    - 사용법은 아래와 같다.
    ``` C++
    void APrototypeCharacter::ViewTransitionTimelineProgress(float Value)
    {
        CameraBoom->SocketOffset = FVector(CameraBoom->SocketOffset.X, Value, CameraBoom->SocketOffset.Z);
    }
    ```

## 함수가 이미 정의되어있다 할 때(function is already defined in .obj)
- 이거 UFUNCTION(BlueprintNative)로 해서 그럼
- Native로 하면 Implementation이 붙어서 사용되기에 블루프린트를 위해 미리 정의를 하나봄

## BindAction Multilpe Paramter
``` C++
PlayerInputComponent->BindAction<TDelegate<void(bool)>>("Reload", IE_Pressed, this, &ABasicCharacter::ReloadAmmo,true);
```

## Animaiton Blueprint In C++
- Animation Instance를 상속받는 C++ 클래스를 만들고, 사용중인 AnimBlueprint의 File탭에서 베이스를 업데이트 해줄 수 있다.
- 그러면 AnimationInstance script에서 지정한 변수 등을 사용할 수 있다.

## 액터 컴포넌트와 씬 컴포넌트
- SceneComponent : 계층구조를 가지는 컴포넌트
- ActorComponent : 기능만 가지는 컴포넌트
    - CharacterMovement 등이 해당

## Ragdoll 안되는 문제
- 정확히 뭐가 문제인지는 모르겠지만, Physics Asset을 다시 만들어서 Assign하니 된다.
- Ragdoll에 Impulse가 안 먹히는 것은 그 값이 너무 작아서 그럴 수 있다.

## Camera Spring Arm Collision 문제
- 적이 공격을 하면 메쉬가 카메라를 막는 경우가 생겨서 순식간에 엄청나게 줌인, 줌아웃이 되는 현상이 발생한다.
- 이것은 SpringArm의 TraceChannel과 다른 컴포넌트들의 Collision을 Ignore하는 방법으로 해결할 수 있다.

## Beam ParticleSystem
- ParticleSystem 애셋을 만들고, Source와 Target을 추가한 뒤, 값을 Paramter로 만든다.
- Source Method, TargetMethod를 꼭 User Set으로 만들어야한다.
``` C++
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = "true"))
    UParticleSystem* GunBeamParticle;
```
``` C++
UParticleSystemComponent* beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
    GunBeamParticle, StartTrace, FRotator::ZeroRotator, false);
if (beam) {
    beam->SetBeamSourcePoint(0 StartTrace, 0);
    beam->SetBeamTargetPoint(0, HitResult->ImpactPoint, 0);
}
```

## Particle Loop 끄기
- Required -> Kill on Deactivate를 true로 
- Emitter Loops 0.0 -> 1로 변경

## Physics Door
- Collision에 따라서 문을 열게 하고싶다면, PhysicsContraint 컴포넌트를 활용하면 된다.
    - Ragdoll에서 활용했던 것 처럼 Limited를 주자
- 문짝 Mesh에 Collision을 추가하고 Simulate physics체크하자

## Decal
- Decal에 그냥 Material을 넣으면 적용이 안된다.
- 이것은 매터리얼 type을 deferred decal, blend mode를 translucent로 바꿔주지 않았기 때문에 적용이 안 된 것이다.
- 필요하다면 SampleTexture에서 Alpha값도 Opacity로 사용하자
    - 이렇게 하면 매터리얼이 투명해보이게 되는데, 이것을 막으려면 Material detail에서 Decal Blend Mode를 DBuffer로 설정하면 된다
    - 만약 적용이 안된다면 ProjectSetting에서 Engine-Rendering-Lighting에 DBuffer Decal을 체크하자
    
## Sequencer 시퀀서
- Shift+드래그 배치 : Level에 영향을 끼칠 수 있는 액터 스폰
- ctrl+드래그 배치 : Level에 영향을 끼치지 않는 액터 스폰(ex. camera rig)
    - 이것은 시퀀서에 번개 모양이 있는지로 확인 가능

- S키를 통해 키프레임 삽입
- 카메라 아이콘을 클릭하면 카메라 컷과 카메라 액터가 자동 추가된다.
- Fade, Sound는 Master에서 트랙 추가 가능
- Master는 Level 시퀀서를 모두 총괄하는 느낌
- Level 시퀀서는 협업을 위해서 Animation 트랙, 카메라 트랙 등등으로 나누어서 작업이 가능하다
- Take 시스템을 활용하면 원본을 훼손하지 않고 여러 작업을 한 뒤 손쉽게 컷 변경이 가능하다

## 왼쪽 위 메시지 뜨는 것
- DisableAllScreenMessages
- EnableAllScreeenMessages

## UI위젯을 위해 커서 활성화 후 다시 게임에 포커스하기
- Menu3D_BP를 만들어서 메인 씬을 만들고, OpenLevel으로 다음 씬으로 넘어가게했는데, 메인메뉴 씬에서 설정했던 커서 관련 데이터가 남아있어서 마우스를 클릭한 상태에서만 마우스 회전 인풋을 받을 수 있었다.
- 처음에는 LevelBlueprint의 Begin에서 해결을 하려했지만 실패했다.
- 그래서 진짜 Input을 받을, PlayerController에서 Set Input GameMode Only와 Set Focus On Viewport를 실행하니 정상적으로 작동했다.

## AnimNotify와 AnimNotify State의 차이점
- 둘 다 AnimationInstance에서 Notify를 줄 수 있는 공통점이 있다.
- 다른점은 AnimNotifyState는 begin, tick, end 3가지의 이벤트가 실행된다는 점이다

## LineTrace로 GroundMaterial SurfaceType찾기
- 그냥 LineTrace를 해보면 SurfaceType을 얻을 수 없다.
- 일단 PhysicalMaterial를 include해야한다.
    ``` C++
    #include "PhysicalMaterials/PhysicalMaterial.h"
    ```
- 그러면 크래시가 뜨는데, Material이 Invalid하다고 한다.
    - 그럴때 필요한 것은 FCollisionQueryParams속성에서 bReturnPhysicalMaterial를 true로 만들어주는 것이다.
    - 블루프린트에서는 기본적으로 세팅이 되어있지만, C++은 더 복잡하기 때문에 수동으로 설정을 해줘야한다.
    ``` C++
    FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
    TraceParams->bReturnPhysicalMaterial = true;
    TraceParams->AddIgnoredActor(Player);
    if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndVector, ECC_WorldStatic, *TraceParams)) {
        if (HitResult->PhysMaterial.IsValid()) {
            ...
    ```
- 참고로 SurfaceType은 ProjectSetting의 Physics카테고리에서 찾을 수 있다.

## DebugDrawLine
- C++에서 Line Debug하기
``` C++
DrawDebugLine(
    GetWorld(),
    socketVec,
    destVec,
    FColor(255, 0, 0),
    false, -1, 0,
    12.333
);
```

## CharacterAnimaion Jittering문제
- 앞쪽으로는 상관이 없는데 왼,오,뒤쪽으로 이동하려하면 자꾸 애니메이션이 버벅이는 문제가 있었다.
- AnimInstance, BasicCharacter, PrototypeCharacter등등 코드를 조금씩 수정해봤는데 결국 못 찾았다.
- 그러다가 CharacterMovement의 속도를0으로 했을 때 Input이 들어가면 Actor가 회전하려한다는 것을 보았고, 이것을 CharacterMovement의 Orient Rotation To Movement와 연관있을것이라 판단하여 해당 속성을 false로 하니 정상적으로 작동하였다.

## Camera Boom Lag
- 캐릭터가 계단을 오를때면 위쪽 벡터로는 계속 텔레포트를 하기 때문에 되게 보기 안 좋았다.
- 그래서 CameraBoom Component의 Lag 속성을 사용하였다.
- 이것을 사용하면 Smooth한 카메라를 만들 수 있다.

## Persistent Level, Level Streaming, GameMode
- Loading을 만들기 위해서 Persistent Level을 만들고 Level Streaming을 통해 Load하려했는데, 게임 플레이 레벨에서 Prototype GameMode로 전환이 이루어지지 않아서 플레이어가 생성되지 않는 현상이 일어났다.
- 알아보니 Level Streaming으로는 GameMode가 변하지 않으니, OpenLevel을 통해서만 GameMode를 바꿀 수 있다고 한다.

## Using Incorrect Object Initializer
- 생성자에 컴포넌트를 추가한 후에 빌드를 했는데 바로 크래시남
- 알고보니 MovementComp = CreateDefault.... 이래야하는데 MovementComp->CreateDefault... 이런식으로 null참조를 함...

## Delegate AddDynamic
- UFUNCTION()을 binding 함수에 넣어주지 않으면 binding 실패함

## UPROPERTY()
- UPROPERTY()가 있어야 언리얼에서 UObject로 인식하여 메모리 할당,해제를 가능케함