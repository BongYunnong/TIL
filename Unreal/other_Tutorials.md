## #1 - Actors
- 헤더파일에서는 보통 정의를 함
- cpp에서 대부분의 코드를 작성함

``` C++
-MyActor.h-
...
	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;
```
``` C++
-MyActor.cpp-
#include "Components/BoxComponent.h"
...
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->AttachTo(RootComponent);
```
- 이것을 Level에 드래그해보면 BoxComponent를 볼 수 있다. 이 아래에는 StaticMeshComponent가 붙어있는데, detail패널에서 이것을 수정하면 그 mesh를 볼 수 있다.

## #2 - Tick function
```
	PrimaryActorTick.bCanEverTick = true;
```
- Tick을 쓰고 싶지 않다면 false로 하면 된다.

```
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime)) - FMath::Sin(RunningTime);
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
```
- 어떤것을 움직일때는 한 프레임마다 조금씩 움직이는 모습을 보여주면 된다. -> Tick
- 위처럼 하면, 한 프레임동안 움직여야 할 deltaHeight를 알 수 있다. 이것을 매 프레임 Z축으로 더해주면 위아래로 왔다갔다하는 모습을 볼 수 있다.
- 이것을 Y로 바꿔주면 양 옆으로 움직이는 것을 볼 수 있다.

## #3 - Making a game

```
	UPROPERTY(EditAnywhere)
```
- EditAnywhere로 하면 detail 패널에서 수정이 가능하다.
```
	//UFUNCTION()
	//	void TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
	UFUNCTION()
		void TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
```
```
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Box->SetGenerateOverlapEvents(true);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::TriggerEnter);
	//Box->SetRelativeScale3D(BoxSize);
    ...
    
void AMyActor::TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// When Player is hit by the box, teleport them back to the start
	OtherActor->SetActorLocation(PlayerStartingLocation);
}

```