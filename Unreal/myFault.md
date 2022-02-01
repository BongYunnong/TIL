# My Fault - 스스로 불러온 재앙
------------------
## ProjectName.Build.cs
- Destructible같은 plugin 사용한 후에는 이것을 확인해보자
- UMG, AI 같은 것도 여기에서 추가해주어야한다.
```C++
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" ,"UMG", "ApexDestruction" });
```

## GameMode - DefaultPawn
```C++
static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
if (PlayerPawnBPClass.Class != NULL)
{
	DefaultPawnClass = PlayerPawnBPClass.Class;
}
```

## GameMode - HUD
```C++
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClasses;

	UPROPERTY()
		class UUserWidget* CurrentWidget;
    ...
	if (HUDWidgetClasses != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClasses);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
```

## GameMode - State
- SetCurrentState로 EWon, EGameOver를 정할 수 있다.
```C++
    UFUNCTION(BlueprintPure, Category = "Score")
	EPrototypePlayState GetCurrentState() const;
	void SetCurrentState(EPrototypePlayState NewState);
    ...
	APrototypeCharacter* MyCharacter = Cast<APrototypeCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) {
		if (MyCharacter->GetCurrentScore() > ScoreToWin) {
			SetCurrentState(EPrototypePlayState::EWon);
		}
		else if (MyCharacter->GetCurrentHealth() > 0 && TimeLimit > 0) {
			TimeLimit -= DecayRate;
		}
		else {
			SetCurrentState(EPrototypePlayState::EGameOver);
		}
	}
    ...
void APrototypeGameMode::SetCurrentState(EPrototypePlayState NewState)
{
	currentState = NewState;
	HandleNewState(currentState);
}

void APrototypeGameMode::HandleNewState(EPrototypePlayState NewState)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	switch (NewState)
	{
	case EPrototypePlayState::EPlaying:
		for (APickupSpawnVolume* volume : SpawnVolumeActors) {
			volume->SetSpawningActive(true);
		}
		break;
	case EPrototypePlayState::EWon:
		for (APickupSpawnVolume* volume : SpawnVolumeActors) {
			volume->SetSpawningActive(false);
		}
		break;
	case EPrototypePlayState::EGameOver:
		for (APickupSpawnVolume* volume : SpawnVolumeActors) {
			volume->SetSpawningActive(false);
		}
		if (PlayerController) {
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		if (MyCharacter) {
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
		break;
	default:
		break;
	case EPrototypePlayState::EUnknown:
		break;
	}
}
```
-----------------------------
## Constructor
- 여기서 만든 것들이 블루프린트로 승격했을 때의 초기설정이 된다.
- 이 생성자를 바꾸면 이 영향을 받는 블루프린트도 재 컴파일되어서 구조가 변경될 수 있다.
    - 이거 곧바로 업데이트가 안 될수도 있으니, 그럴 때에는 껏다가 다시 켜보자.
``` C++
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}
```
## SetupPlayerInputComponent
- Player의 Input binding같은 것을 담당
```C++
- header -
virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
- cpp -
void AMyTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyTestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyTestCharacter::MoveRight);

	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMyTestCharacter::Attack_Melee);
}
```

## PostInitializeComponents
- Actor가 Initailze를 끝난 후에 실행된다.
- 게임 플레이 도중에만 실행이 가능하다.
```C++
- header -
virtual void PostInitializeComponents() override;
- cpp -
void AMyTestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}
```

## InlineFunction
``` C++
FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }
```

## Timer
``` C++
	FTimerHandle SpawnTimer;
    ...
	if (bShouldSpawn) {
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &APickupSpawnVolume::SpawnPickup, SpawnDelay, false);
	}
	else {
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
```

## C++ Delay
- C++로 delay를 어떻게 사용할 수 있을까 검색해봤는데 아래와 같은 코드가 있었다.
    ``` C++
        FTimerHandle waitHandle;
        GetWorld()->GetTimerManager().SetTimer(waitHandle, FTimerDelegate::CreateLambda([&]() {
            //UpdateAmmo(addCount);
            //GetWorld()->GetTimerManager().ClearTimer(waitHandle);
        }), tmpWaitTime, false);
    ```
    - 해석을 해보면, tmpWaitTime만큼의 delay 후에 Lambda식 안에 있는 코드들을 delegate로 실행을 하되, loop하지는 않는다는 것이다.
    - 이렇게만 보면 내가 찾던 것이었는데, 문제는 매개변수가 제대로 들어가지 않았다. 나는 분명 addCount에 1을 넣었는데 Log를 찍어보면 6230(예시) 이런 숫자들이 찍혔다. 마치 range를 벗어나서 생기는 것 같았다.
- 그래서 다른 방법을 찾아봤는데, 그것은 다음과 같다.
    ``` C++
        FTimerHandle waitHandle;
        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &APrototypeCharacter::UpdateAmmo, addCount);
        GetWorld()->GetTimerManager().SetTimer(waitHandle, TimerDelegate, waitTime, false);
    ```
    - 위와의 차이점은 Delegate를 선언을 해준 뒤 사용한다는 것인데, 이렇게 하면 매개변수를 전달해줬을 때 제대로 찍히는 것을 확인했다.
    - 그런데 문제점은 하나의 함수만 사용이 가능하다는 것이었다.
        - Delegate니까 나중에 더하면 되나? -> +=이걸로 해보니 안된다.
## Blueprint For Loop with Delay
- C++로 delay주는 것을 실패하고 그냥 블루프린트로 구현하려했다.
- 그런데 블루프린트에도 문제가 있었는데 그냥 for loop의 body에 delay를 주면 그걸 무시하고 Completed로 갔다.
- 이것을 해결하는 방법은 매크로를 새로 만드는 방법이었다.
![image](https://user-images.githubusercontent.com/11372675/148753799-d2657431-c3a7-4af0-9cbd-fd2f5b1ecef5.png)


## OnLanded
- OnLanded를 재정의하려했는데 override를 못함
- character.h에 들어가서 virtual을 붙여줬는데, BlueprintImplementableEvent가 붙어있어서 못한다고함
- 그냥 블루프린트에서 만들자

## Cast
- 블루프린트를 배웠을 때부터 느낀 것인데, Cast가 매우 중요하다.
    - Unity의 GetComponent해서 형 변환을 하는 느낌과 비슷한다.
    - 형 변환을 해야 그것이 가지고있는 프로퍼티, 함수에 접근이 가능하다.
``` C++
UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((HitResult.GetActor())->GetRootComponent());
if(MeshComp){
    MeshComp->AddRadialImpulse(Start, Radius, Strength, ERadialImpulseFalloff::RIF_Constant, true);
}
...
APrototypeCharacter* player = Cast<APrototypeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
```

## FindComponentByClass
- 진짜 Actor 하위의 Component를 참조하고싶은 것이라면?
``` C++
		UAddRadialImpulse* impulseComp = SpawnedExplosion->FindComponentByClass<UAddRadialImpulse>();
		if (impulseComp) {
			UE_LOG(LogTemp, Log, TEXT("impulseComp!!!"));
			impulseComp->Explode();
		}
```

## GetAllActorsOfClass
- Unity의 FindObjectsOfType 같은 느낌
- 찾을 class를 넣어주고, 찾은 것을 넣을 array도 넣어줌
```C++
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickupSpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors) {
		APickupSpawnVolume* SpawnVolumeActor = Cast<APickupSpawnVolume>(Actor);
		if (SpawnVolumeActor) {
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}
```

## Log
- UE Log는 OutputLog를 통해 볼 수 있는 것.
- Gengine->AddOnScreenDebugMessage는 screen위에 띄워주는 것
``` C++
UE_LOG(LogTemp, Log, TEXT("Non Destructible"));
...
UE_LOG(LogTemp, Log, TEXT("You have Collected %s"), *PickupDebugString);
...
GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "AppyDamage!");

```

## SweepMultiByChannel
- Start, End 위치로 Collider에 Overlap된 것들을 참조할 수 있다.
``` C++
	TArray<FHitResult> HitArray;
	const FVector Start = this->GetComponentLocation();
	const FVector End = Start;
	const FCollisionShape SphereShape = FCollisionShape::MakeSphere(Radius);
	const bool bSweepHit = GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity, ECC_WorldStatic, SphereShape);
	DrawDebugSphere(GetWorld(), Start, Radius, 50, FColor::Orange, true);

	if (bSweepHit) {
		for (const FHitResult HitResult : HitArray) {
			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((HitResult.GetActor())->GetRootComponent());
            ...
		}
	}
```

## ApplyRadialDamage
``` C++
	TArray<AActor*> ignoredActors;
	UGameplayStatics::ApplyRadialDamage(GetWorld(),
		Strength,
		Start,
		Radius,
		UDamageType::StaticClass(),
		ignoredActors,
		this->GetAttachmentRootActor(),
		nullptr,
		false,
		ECollisionChannel::ECC_Visibility);
```

## Add RadialImpulse
``` C++
MeshComp->AddRadialImpulse(Start, Radius, Strength, ERadialImpulseFalloff::RIF_Constant, true);
```

## OnOverlapBegin
``` C++
void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsExploded)
		return;

	UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(OtherComp);
	if (MeshComp) {
		bIsExploded = true;

		Explosion();

		APrototypeCharacter* player = Cast<APrototypeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player) {
			player->UpdateScore(200.0f);
		}
	}
}
```

## SpawnActor
- Spawn을 하려면 TSubclassOf로 형태를 지정해줘야한다.
```C++
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<class AActor> ExplosionActor;
    ...
	FRotator SpawnRotation;
	SpawnRotation.Yaw = FMath::FRand() * 360.0f;
	SpawnRotation.Pitch = FMath::FRand() * 360.0f;
	SpawnRotation.Roll = FMath::FRand() * 360.0f;

	AActor* const SpawnedExplosion = GetWorld()->SpawnActor<AActor>(ExplosionActor, GetActorLocation(), SpawnRotation);
```

## BoxComponent
- Origin과 Scale을 가져올 수 있구나.
```C++
FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
FVector SpawnExtent = WhereToSpawn->GetScaledBoxExtent();
```

## KismetLibrary
- 여러가지 유용한 함수들(아마 수학적인 것?)
``` C++
UKismetMathLibrary::RandomPointInBoundingBox(FVector _origin_, FVector _extent);
```


## Circular Progress
- Unity처럼 그냥 Image fill amount로 하는 것이 아니다.
- Texture를 Import한 후에 Compression Setting을 'UserInterface2D(RGBA)'로 바꿔주고, Level Of Detail탭에서 Texture Group을 UI로 바꿔준다.
- 새로운 매터리얼을 만들어주고 다음과 같이 노드를 작성한다.

![image](https://user-images.githubusercontent.com/11372675/149047409-affd4a40-f4f4-4684-b97b-a0eb2662be22.png)

- HUD Tick같은 곳에서 Get Dynamic Material -> Set Scalar Parameter Value(Prameter Name 정해주기)

---------------------------
## On Overlap Begin
``` C++
- header -
UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
- cpp -
void AMyTestActor::OnOverlapBegin(UPrimitiveComponent* OverlapeedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("OnOverlapBegin"));
	if (OtherActor->IsA(AMyTestCharacter::StaticClass())) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFX, GetActorLocation());
		Destroy();
	}
}
```

## Notify Begin overlap
``` C++
-header-
virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
...
-cpp
void AMyTestWeapon::NotifyActorBeginOverlap(AActor* OtherActor) {
	if (OtherActor->IsA(AActor::StaticClass()) && MyPawn->isDuringAttack && OtherActor!=MyPawn) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "AppyDamage!");

		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
	}
}
```

## ApplyDamage
- Damage라는 속성이 이미 GameplayStatics에 있음
- static float UGameplayStatics::ApplyDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass)
``` C++
UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
```

## Die
```C++
- header -
virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
- cpp -
void ABasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	myHealth = FMath::Min(0.0f, myHealth);
	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ?
		Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject())
		: GetDefault<UDamageType>();
	Killer = GetDamageInstigator(Killer, *DamageType);
	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent()) {
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn,ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody,ECR_Ignore);
	}
	if (GetCharacterMovement()) {
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}
	if (Controller != NULL) {
		Controller->UnPossess();
	}
	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasicCharacter::DeathAnimationEnd, DeathAnimDuration, false);
}
void ABasicCharacter::DeathAnimationEnd() {
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}
- caller - 
float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstiagtor, AActor* DamageCauser)
{
	Die(myGetDamage, DamageEvent, EventInstiagtor, DamageCauser);
}
```


--------------------
## AnimMontage
``` C++
- header -
UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* AttackCombo_AnimMt;
UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Death_AnimMontage;
- cpp -
PlayAnimMontage(Death_AnimMontage, 1.0f);
or
FString PlaySection = "Attack_" + FString::FromInt(tmp_Num);
PlayAnimMontage(AttackCombo_AnimMt, 1.0f, FName(*PlaySection));
```
- Montage를 부분부분 나누면 그 section의 이름을 통해 그 시작부분부터 play가 가능하다.


## AnimNotify
- Unity의 Animation Event같은 느낌
- Animation에 Notify를 줄 수 있는데, 
```C++
- header-
UCLASS()
class MYTESTPROJECT_API UMyTestAnimNotifyState : public UAnimNotifyState{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
};
- cpp -
void UMyTestAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());
		if (Player != NULL) {
			//player->ShowFX();
			Player->isDuringAttack = true;
		}
	}
}

void UMyTestAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());
		if (Player != NULL) {
			Player->Attack_Melee_End();
			Player->isDuringAttack = false;
		}
	}
}
```
![image](https://user-images.githubusercontent.com/11372675/149083268-31b4c175-cb14-4915-b873-5c8406bdfd1b.png)
- Montage Asset을 만들고, 부분부분 나눈 후에 Notify의 start, end를 설정
	- Notify Start, Notify End 함수가 호출

--------------------
## Particle FX
``` C++
- header -
UPROPERTY(EditDefaultsOnly, Category = "MyFX")
	UParticleSystem* HitFX;
- cpp -
static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	HitFX = ParticleAsset.Object;
...
UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
```


-------------
## Struct
``` C++
#include "Engine/DataTable.h"

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

## DataTable
- 위처럼 Struct를 만든 후에는 DataTable Asset을 만들 수 있다.
	![image](https://user-images.githubusercontent.com/11372675/149086010-053f0c5a-8b1e-431b-b312-9d3d2257944b.png)
	- RowName으로 블루프린트에서 접근을 하니, 잘 생각해서 수정하자.
- 그 활용은 다음과 같다
![image](https://user-images.githubusercontent.com/11372675/149085889-563f0488-ed46-4302-80e9-a2b9149a30dd.png)

--------------------------
## Widget Designer Tab
- Widget을 상속받은 C++ Class에서부터 바로 Blueprint를 만들어내면 Designer탭이 없음
- 이것은 그냥 브라우저에서 블루프린트를 생성하고, 거기에서 class를 선택해야한다.

## Widget Constructor
- Widget class를 그냥 다른 actor 생성자처럼 만들려고 하면 에러가 뜸
```
- header-
UMenuWidgetBase(const FObjectInitializer &ObjectInitializer);
- cpp -
UMenuWidgetBase::UMenuWidgetBase(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}
```
or
```
- header-
void NativeConstruct() override;
- cpp-
void UHealthBar::NativeConstruct(){
}
```

## Widget can't have children
- BP를 만들어서 열어보면 Graph에 아무것도 없을 수 있다.
- 그런데 뭔가를 추가하려고 하면 can't add child라고 한다.
- 이것은 Named Slot을 넣거나 CanvasPanel를 필요로 하기 때문이다.
- C++ class에서 미리 canvasPanel을 정의하고, BP로 넘어와서 그것의 이름에 맞게 CanvasPanel을 추가해주면 그 다음부터는 평범한 BP처럼 넣을 수 있다.

## World? Screen?
- 3D 월드 상에 있는 Text가 항상 Camera를 보고 싶게 하고 싶다면 Detail->UserInterface->Space를 World에서 Screen으로 바꾸면 된다.
- 원래는 SceneComponent에 넣고 그걸 돌렸는데, 굳이 안 그래도 될듯..
---------------------------
## LineTrace
- Line Trace를 ECC_Visibility로 하면 Widget까지 Trace하는 수가 있다.
	- player의 Health Bar가 계속 충돌하는 바람에 문제가 있었음
- 이것을 방지하려면 ECC_WorldStatic으로 하면 된다.
	- StaticMesh가 Static으로 들어가서 되는듯
	- 그러면 Trigger같은 것은...? 되려나?

---------------------
## UCLASS(config=game)
- config 지정자로 선언된 언리얼 오브젝트(UCLASS(config=aaa)로 선언된 클래스)의 멤버 변수가 UPROPERTY(config)로 지정되면 해당 aaa.ini로부터 기본값을 읽어온다.
- 예를 들어서 float score 멤버변수가 지정되었다면 ini에서 score를 찾아 값을 읽어옴