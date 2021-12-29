- C++ Classes 안에 프로젝트 폴더에 C++ class actor로 생성
- #include "MyTestActor.generated.h" 이거는 include맨 마지막에 있어야 함

- 블루 프린트를 생성할때 class 이름으로 찾아서 생성

- window - developer tools -> Output Log, Message Log
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World"));
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));


- BasicCharacter라는 Character 형식의 C++ 클래스 생성, 이것을 상속받는 MyTestCharacter 생성

-Setting -> ProjectSetting -> Map&Modes -> DefaultMap

- C++Classes->MyTestProject->GameMode-> 이것도 BP 만들어줘야함
-> Setting에서 Mode->DefaultMode 설정하고, Default Pawn Class 설정


-헤더파일은 명령어를 검색 엔진에 검색해보면 찾을 수 있음


-Use Controller Rotatoin Yaw 끄기 -> 카메라와 별개로 캐릭터가 회전 가능

- C++ 클래스에서 만든 것들이 Blueprint에 생기는 것을 볼 수 있다.

- alt 누르고 드래그하면 복사

- AddDynamics를 생성자로 했더니 안되고, BeginPlay로 해야 됨

- 애셋 copy reference하고 코드에서 붙여넣기 하면 그 경로가 넣어짐

-GameMode는 프로젝트를 만들 때 자동으로 만들어짐
-MyTestProject.Build.cs에 UMG를 사용하겠다고 넣어줘야함

-우클릭->UserInterface->HUD
- HUD 적용하려면 GameMode에서 적용

-우클릭->miscellaneous -> Data Table -> 코드로 작성한 struct 선택 가능

-Hud에서 Text를 binding한 후에 GetDataTableRow 로 RowName을 통해 정보를 변수에 담아서 Return할 수 있음


-fbx Import
- animaiton blueprint 생성
- add new statemachine -> 애니메이션 드래그 -> 조건 작성
- animation Montage 생성


-setting -> Input 


- c++ file을 그냥 Editor나 Visual Studio에서 지우면 지워지지 않거나 에러가 발생
	1. Source 폴더로 가서 원하는 파일 지움
	2. vs, Binaries, Intermediate, ~~.sln 지움
	3. Unreal Project를 누르면 rebuild
	- 일반 블루프린트, Unreal Editor에서 만들거나 사용하는 리소스 파일들은 그냥 force delete하면 보통 문제 없음


- retarget error
	애니메이션 우클릭 -> retarget -> 설정

- anim missing
	몽타주에서 anim이 미씽뜨면 해당 몽타주 애니메이션 strip을 눌러 detail화면을 보고, 거기에서 애니메이션 설정

- github
	1. github desktop다운
	2. New Repository 선택해 자신의 Project 기록
	3. 기록하고싶은Projec 폴더로 이동
	4. Repository 이름과 내용 작성