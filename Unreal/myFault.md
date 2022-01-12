# My Fault - 스스로 불러온 재앙

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
``` C++
UE_LOG(LogTemp, Log, TEXT("Non Destructible"));
...
UE_LOG(LogTemp, Log, TEXT("You have Collected %s"), *PickupDebugString);
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
