// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include<iostream>
#include<random>
#include<algorithm>
#include<vector>
#include "Engine/World.h"

#include "NavigationSystem.h"
#include "Journey/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraActor.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"
#include "GameDataSingleton.h"
#include "Items/Item.h"
#include "CellularAutomata.h"
#include "BattleSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Elements/Framework/TypedElementOwnerStore.h"
#include "Kismet/GameplayStatics.h"


AHeroCharacter::AHeroCharacter()
{
	isAttack = false;
	isDeath = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = true;

	FollowCamera->bAutoActivate = true;


	FollowCamera->SetActive(true);
	//WorldFollowCamera->SetActive(true);


	GetCharacterMovement()->bOrientRotationToMovement = true;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	shop = CreateDefaultSubobject<UShopComponent>("Shop");
	shop->Capacity = 20;

	hp = 50;
	Armour = 200;
	gold = 200;
	fatigue = 0;

	isTown = false;
	UCapsuleComponent* MyCapsuleComponent = GetCapsuleComponent();
	MyCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AHeroCharacter::OnOverlapBegin);

	
	
}

void AHeroCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		if (Item->OwingInventory != nullptr && Item->OwningShop == nullptr)
		{
			Item->Use(this);
			Item->OnUse(this);
		}
		if (Item->OwingInventory == nullptr && Item->OwningShop != nullptr) //사는거
		{
			if (gold >= Item->cost)
			{
				Inventory->AddItem(Item);
				shop->RemoveItem(Item);
				//UE_LOG(LogTemp,Warning,TEXT("%d"),gold);
				gold -= Item->cost;
				//Item->OnUse(this);
			}
		}
	}
}

// void AHeroCharacter::BuyItem(UItem* Item, UInventoryComponent* Inventory)
// {
// 	if(Item)
// 	{
// 		Item->Buy(Inventory);
// 	}
// }

void AHeroCharacter::MoveToLocation(const FVector& DestLocation)
{
	if (AIController)
	{
		AIController->MoveToLocation(DestLocation);
	}
}

void AHeroCharacter::ChangeToWorldMapCamera()
{
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();

	PlayerController->SetViewTargetWithBlend(WorldMapCamera, 0);
	//if (PController != nullptr && WorldMapCamera != nullptr)
	//{
	//	if (PController->GetViewTarget() != WorldMapCamera)
	//	{
	//	}
	//}
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->SetFOV(60);
}

void AHeroCharacter::ChangeToBossWorldMapCamera()
{
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();

	PlayerController->SetViewTargetWithBlend(BossMapCamera, 0);
	//if (PController != nullptr && BossMapCamera != nullptr)
	//{
	//	if (PController->GetViewTarget() != BossMapCamera)
	//	{
	//	}
	//}
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->SetFOV(90);
}

void AHeroCharacter::ChangeToBattleCamera()
{
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();

	PlayerController->bEnableMouseOverEvents = true;
	PlayerController->bShowMouseCursor = true;

	PlayerController->SetViewTargetWithBlend(BattleCamera, 0);
	//if (PController != nullptr && BattleCamera != nullptr)
	//{
	//	if (PController->GetViewTarget() != BattleCamera)
	//	{
	//	}
	//}
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->SetFOV(90);
}

void AHeroCharacter::ChangeToBossBattleCamera()
{
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();

	PlayerController->SetViewTargetWithBlend(BossBattleCamera, 0);
	//if (PController != nullptr && BossBattleCamera != nullptr)
	//{
	//	if (PController->GetViewTarget() != BossBattleCamera)
	//	{
	//	}
	//}
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->SetFOV(90);
}

void AHeroCharacter::ChangeToTownCamera()
{
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();

	AActor* CameraOwner = FollowCamera->GetOwner();
	PlayerController->SetViewTargetWithBlend(CameraOwner, 0);

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->SetFOV(90);
}

void AHeroCharacter::OnMouseWheelClicked()
{
	bIsMouseWheelClicked = true;
}

void AHeroCharacter::OnMouseWheelReleased()
{
	bIsMouseWheelClicked = false;
}

void AHeroCharacter::ChangeController(bool isAI)
{
	AController* currentController = GetController();
	currentController->UnPossess();

	if (isAI)
	{
		//PlayerController->UnPossess();
		AIController->Possess(this);
		isInBattle = true;
	}
	else
	{
		//AIController->UnPossess();
		PlayerController->Possess(this);
		isInBattle = false;
	}
}

void AHeroCharacter::cutSceneEnd()
{
	isCutsceneEnd = true;

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;
		// 해당 태그를 가진 액터만 선택합니다.
		if (Actor->ActorHasTag("TownBox"))
		{
			SetActorLocation(Actor->GetActorLocation());
			break;
		}
	}
}

void AHeroCharacter::MoveCamera(float DeltaTime)
{
	float mouseX, mouseY;
	PlayerController->GetMousePosition(mouseX, mouseY);
	const FVector2D MousePosition = FVector2D(mouseX, mouseY);
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	ACameraActor* CameraActor = Cast<ACameraActor>(PlayerController->GetViewTarget());

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);


	if (CameraActor == WorldMapCamera)
	{
		if (MousePosition.X < ViewportSize.X / 2)
		{
			// 왼쪽으로 카메라 이동
			FVector loc = CameraActor->GetActorLocation();
			loc.Y -= 20;

			CameraActor->SetActorLocation(loc);
		}

		else
		{
			// 오른쪽으로 카메라 이동
			FVector loc = CameraActor->GetActorLocation();
			loc.Y += 20;
			CameraActor->SetActorLocation(loc);
		}

		if (MousePosition.Y < ViewportSize.Y / 2)
		{
			// 위쪽으로 카메라 이동
			FVector loc = CameraActor->GetActorLocation();
			loc.X += 20;

			CameraActor->SetActorLocation(loc);
		}
		else
		{
			// 아래쪽으로 카메라 이동

			FVector loc = CameraActor->GetActorLocation();
			loc.X -= 20;
			CameraActor->SetActorLocation(loc);
		}
	}


	// PlayerController로부터 카메라 액터를 가져옵니다.
	//if (APlayerController* PC = Cast<APlayerController>(GetController()))
	//{
	//	//ACameraActor* CameraActor = Cast<ACameraActor>(PC->GetViewTarget());
	//	ACameraActor* CameraActor = Cast<ACameraActor>(PlayerController->GetViewTarget());

	//	if (CameraActor == WorldMapCamera)
	//	{
	//		FVector NewLocation = CameraActor->GetActorLocation() + CameraMoveDirection * CameraMoveSpeed * DeltaTime;
	//		CameraActor->SetActorLocation(NewLocation);
	//	}

	//	// 카메라 액터가 있는 경우 카메라 위치를 변경합니다.
	//	if (CameraActor == BossMapCamera)
	//	{
	//		FVector NewLocation = CameraActor->GetActorLocation() + CameraMoveDirection * CameraMoveSpeed * DeltaTime;
	//		CameraActor->SetActorLocation(NewLocation);
	//	}
	//}
}

void AHeroCharacter::LoadGame()
{
}

void AHeroCharacter::SaveGame()
{
}

void AHeroCharacter::GoToWorldMap()
{
	// 혹시 모를 남아있을 monster, player 모두 제거
	UWorld* World = GetWorld();
	ABattleSystem* battleSystem = nullptr;
	for (TActorIterator<ABattleSystem> It(World); It; ++It)
	{
		if (!(*It)->isBossSystem)
			battleSystem = *It;
	}
	battleSystem->isBattleStart = false;
	if (World)
	{
		// 게임 월드에 있는 모든 액터를 찾습니다.
		for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
		{
			AActor* Actor = *ActorItr;

			// 해당 태그를 가진 액터만 선택합니다.
			if (Actor->ActorHasTag("BP_MONSTER"))
			{
				Actor->Destroy();
			}

			if (Actor->ActorHasTag("BP_HERO"))
			{
				Actor->Destroy();
			}
		}
	}


	//if (UGameDataSingleton::GetInstance()->isBossWorld)
	//{
	//	SetActorRotation(FRotator(0, 0, 0));
	//	SetActorLocation(UGameDataSingleton::GetInstance()->SavedPos);

	//	PlayerController->SetInputMode(FInputModeGameOnly());
	//	PlayerController->bEnableMouseOverEvents = true;
	//	PlayerController->bShowMouseCursor = true;
	//	bUseControllerRotationPitch = false;
	//	bUseControllerRotationYaw = false;
	//	ChangeToBossWorldMapCamera();

	//	UE_LOG(LogTemp, Warning, TEXT("goto pos: %s"), *UGameDataSingleton::GetInstance()->SavedPos.ToString());
	//}
	//else

	SetActorRotation(FRotator(0, 0, 0));
	SetActorLocation(SavedPos);

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	ChangeToWorldMapCamera();


	//UGameplayStatics::OpenLevel(this, "WorldMap", true);
	//FollowCamera->SetActive(false);
	//WorldFollowCamera->SetActive(true);
	//SwitchToWorldFollowCamera();
	//WorldFollowCamera->SetActive(false);
	isTown = false;
}

void AHeroCharacter::GoToWorld()
{
	// 혹시 모를 남아있을 monster, player 모두 제거
	UWorld* World = GetWorld();
	ABattleSystem* battleSystem = nullptr;
	for (TActorIterator<ABattleSystem> It(World); It; ++It)
	{
		if (!(*It)->isBossSystem)
			battleSystem = *It;
	}
	battleSystem->isBattleStart = false;
	if (World)
	{
		// 게임 월드에 있는 모든 액터를 찾습니다.
		for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
		{
			AActor* Actor = *ActorItr;

			// 해당 태그를 가진 액터만 선택합니다.
			if (Actor->ActorHasTag("BP_MONSTER"))
			{
				Actor->Destroy();
			}

			if (Actor->ActorHasTag("BP_HERO"))
			{
				Actor->Destroy();
			}
		}
	}

	SetActorRotation(FRotator(0, 0, 0));
	SetActorLocation(SavedPos);

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	ChangeToWorldMapCamera();
}

void AHeroCharacter::ChangeCamera(bool isWorld)
{
	//if (isWorld)
	//{
	//	WorldFollowCamera->SetActive(true);
	//	FollowCamera->SetActive(false);
	//}
	//else
	//{
	//	WorldFollowCamera->SetActive(false);
	//	//FollowCamera->SetActive(true);
	//}
}

void AHeroCharacter::ChangeGameMode()
{
}

void AHeroCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	PlayerController->StopMovement();


	if (OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor IS NULLPTR"));
		return;
	}

	// Check if the overlapped actor has a specific tag
	if (OtherActor->ActorHasTag("TownBox"))
	{
		// CellularAutomata �������� 
		//CellularActor = Cast<ACellularAutomata>(UGameplayStatics::GetActorOfClass(GetWorld(), ACellularAutomata::StaticClass()));

		AWorldCubeBase* worldCube = Cast<AWorldCubeBase>(OtherActor);

		if (worldCube->cubeNumber < 0 || worldCube->cubeNumber > 143)
		{
			int nowIndex = worldCube->cubeNumber;
			//bool v = UGameDataSingleton::GetInstance()->TileInfos.IsValidIndex(worldCube->cubeNumber);
		}

		// �湮�ߴ������� üũ
		if (!worldCube->isVisited)
		{
			//TArray<FCAStruct> MainTileInfos = UGameDataSingleton::GetInstance()->TileInfos;
			// �ƴϸ� �湮 �ߴٰ� üũ

			//UGameDataSingleton::GetInstance()->TileInfos[worldCube->cubeNumber].isVisited = true;
			SavedPos = FVector(worldCube->GetActorLocation().X, worldCube->GetActorLocation().Y,
			                   worldCube->GetActorLocation().Z + 60);

			// check town or battle
			// 0403 일단 무조건 Town 쪽으로 이동하게 설정
			if (worldCube->isTown)
			{
				//ChangeController(false);
				worldCube->isVisited = true;
				SetActorRotation(FRotator(0, 0, 0));
				SetActorLocation(worldCube->Location);
				//SwitchToFollowCamera();
				PlayerController->SetInputMode(FInputModeGameOnly());
				PlayerController->bShowMouseCursor = false;
				bUseControllerRotationPitch = true;
				bUseControllerRotationYaw = true;
				ChangeToTownCamera();
				isTown = true;
				townnamecnt++;
			}
			else
			{
				fatigue += 1;

				//ChangeController(true);
				// 해당 타일이 포털일때
				if (worldCube->isPortal)
				{
					worldCube->isVisited = true;

					SetActorRotation(FRotator(0, 0, 0));
					SetActorLocation(UGameDataSingleton::GetInstance()->BossWorldSpawnPos);
					//UGameDataSingleton::GetInstance()->isBossWorld = true;
					ChangeToBossWorldMapCamera();
				}
				else
				{
					if (worldCube->isKey)
					{
						UGameDataSingleton::GetInstance()->NowKeyNum += 1;
						maxKeyNum = UGameDataSingleton::GetInstance()->TotalKeyNum;
						nowKeyNum += 1;
					}
					worldCube->isVisited = true;
					worldCube->isKey = false;
					SetActorRotation(FRotator(0, 0, 0));
					SetActorLocation(UGameDataSingleton::GetInstance()->BattleSpawnPos);
					PlayerController->bEnableMouseOverEvents = true;
					PlayerController->bShowMouseCursor = true;
					bUseControllerRotationPitch = false;
					bUseControllerRotationYaw = false;

					// 전투맵 세팅
					UWorld* World = GetWorld();
					ABattleSystem* battleSystem = nullptr;
					for (TActorIterator<ABattleSystem> It(World); It; ++It)
					{
						if (!(*It)->isBossSystem)
							battleSystem = *It;
					}
					battleSystem->resetBattleField(worldCube->monsterPower * worldCube->monsterLevel);

					ChangeToBattleCamera();
					//PlayerController->SetInputMode(FInputModeGameOnly());

					//isTown = true;
				}
			}
		}
	}
	// Check if the overlapped actor has a specific tag
	if (OtherActor->ActorHasTag("BossBox1"))
	{
	}

	// Check if the overlapped actor has a specific tag
	if (OtherActor->ActorHasTag("BossBox2"))
	{
		AWorldCubeBase* worldCube = Cast<AWorldCubeBase>(OtherActor);

		if (!worldCube->isVisited)
		{
			worldCube->isVisited = true;


			SavedPos = FVector(worldCube->GetActorLocation().X, worldCube->GetActorLocation().Y,
			                   worldCube->GetActorLocation().Z + 60);

			SetActorRotation(FRotator(0, 0, 0));
			SetActorLocation(UGameDataSingleton::GetInstance()->BossBattleSpawnPos);

			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bEnableMouseOverEvents = true;
			PlayerController->bShowMouseCursor = true;
			bUseControllerRotationPitch = false;
			bUseControllerRotationYaw = false;

			ChangeToBossBattleCamera();
			//isTown = true;
		}
	}

	// Check if the overlapped actor has a specific tag
	if (OtherActor->ActorHasTag("BossBox3"))
	{
		AWorldCubeBase* worldCube = Cast<AWorldCubeBase>(OtherActor);
		if (!worldCube->isVisited)
		{
			worldCube->isVisited = true;


			SavedPos = FVector(worldCube->GetActorLocation().X, worldCube->GetActorLocation().Y,
			                   worldCube->GetActorLocation().Z + 60);

			SetActorRotation(FRotator(0, 0, 0));
			SetActorLocation(UGameDataSingleton::GetInstance()->BossBattleSpawnPos);
			ChangeToBossBattleCamera();

			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
			bUseControllerRotationPitch = true;
			bUseControllerRotationYaw = true;
			//isTown = true;
		}
	}

	// Check if the overlapped actor has a specific tag
	if (OtherActor->ActorHasTag("BossBox4"))
	{
		AWorldCubeBase* worldCube = Cast<AWorldCubeBase>(OtherActor);
		if (!worldCube->isVisited)
		{
			worldCube->isVisited = true;

			SavedPos = FVector(worldCube->GetActorLocation().X, worldCube->GetActorLocation().Y,
			                   worldCube->GetActorLocation().Z + 60);

			SetActorRotation(FRotator(0, 0, 0));
			SetActorLocation(UGameDataSingleton::GetInstance()->BossBattleSpawnPos);
			ChangeToBossBattleCamera();

			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
			bUseControllerRotationPitch = true;
			bUseControllerRotationYaw = true;
			//isTown = true;
		}
	}
}

void AHeroCharacter::SwitchToFollowCamera()
{
	// Activate the FollowCamera
	//WorldFollowCamera->SetActive(false);
	FollowCamera->SetActive(true);
}

void AHeroCharacter::SwitchToWorldFollowCamera()
{
	// Activate the WorldFollowCamera
	FollowCamera->SetActive(false);
	//WorldFollowCamera->SetActive(true);
}


void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Look Up", this, &AHeroCharacter::Pitch_Up);
	PlayerInputComponent->BindAxis("Turn Right", this, &AHeroCharacter::Turn_Right);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Pressed, this, &AHeroCharacter::GoToWorldMap);
	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &AHeroCharacter::OnRightClick);
	PlayerInputComponent->BindAction(TEXT("LeftClick"), IE_Pressed, this, &AHeroCharacter::OnLeftClick);

	PlayerInputComponent->BindAction(TEXT("CreateBossWorld"), IE_Pressed, this, &AHeroCharacter::createPortal);


	PlayerInputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &AHeroCharacter::OnZoomIn);
	PlayerInputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &AHeroCharacter::OnZoomOut);

	PlayerInputComponent->BindAction("MouseWheelClick", IE_Pressed, this, &AHeroCharacter::OnMouseWheelClicked);
	PlayerInputComponent->BindAction("MouseWheelClick", IE_Released, this, &AHeroCharacter::OnMouseWheelReleased);
}

void AHeroCharacter::OnZoomIn()
{
	// PlayerController로부터 카메라 액터를 가져옵니다.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		ACameraActor* CameraActor = Cast<ACameraActor>(PC->GetViewTarget());

		if (CameraActor == WorldMapCamera)
		{
			APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
			if (CameraManager == nullptr) return;

			float ZoomDelta = 1 * -3.f;
			float MyFOV = FMath::Clamp(CameraManager->GetFOVAngle() + ZoomDelta, 10.0f, 170.0f);
			CameraManager->SetFOV(MyFOV);
		}

		// 카메라 액터가 있는 경우 카메라 위치를 변경합니다.
		if (CameraActor == BossMapCamera)
		{
			APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
			if (CameraManager == nullptr) return;

			float ZoomDelta = 1 * -3.f;
			float MyFOV = FMath::Clamp(CameraManager->GetFOVAngle() + ZoomDelta, 10.0f, 170.0f);
			CameraManager->SetFOV(MyFOV);
		}
	}
}

void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isCutsceneEnd)
	{
		if (bIsMouseWheelClicked)
		{
			MoveCamera(DeltaTime);
		}

		if (PlayerController->GetViewTarget() == WorldMapCamera)
		{
			FVector loc = GetActorLocation();
			WorldMapCamera->SetActorLocation(FVector(loc.X - 400, loc.Y, loc.Z + 800));
		}
	}
}


void AHeroCharacter::OnZoomOut()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		ACameraActor* CameraActor = Cast<ACameraActor>(PC->GetViewTarget());

		if (CameraActor == WorldMapCamera)
		{
			APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
			if (CameraManager == nullptr) return;

			float ZoomDelta = 1 * 3.f;
			float MyFOV = FMath::Clamp(CameraManager->GetFOVAngle() + ZoomDelta, 10.0f, 170.0f);
			CameraManager->SetFOV(MyFOV);
		}

		// 카메라 액터가 있는 경우 카메라 위치를 변경합니다.
		if (CameraActor == BossMapCamera)
		{
			APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
			if (CameraManager == nullptr) return;

			float ZoomDelta = 1 * 3.f;
			float MyFOV = FMath::Clamp(CameraManager->GetFOVAngle() + ZoomDelta, 10.0f, 170.0f);
			CameraManager->SetFOV(MyFOV);
		}
	}
}

void AHeroCharacter::createPortal()
{
	// 1. wcube 체크
	// 마을이 아니고 지나갈수 있는 타일인 경우

	if (!CellularActor)
	{
		CellularActor = Cast<ACellularAutomata>(
			UGameplayStatics::GetActorOfClass(GetWorld(), ACellularAutomata::StaticClass()));
	}
	int tilemax = CellularActor->Tilemax * 2;

	if (CellularActor->isPortalExist)
		return;

	bool IsDuplicate = true;
	// 게임 월드에 있는 모든 액터를 찾습니다.
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AActor* Actor = *ActorItr;

		// 해당 태그를 가진 액터만 선택합니다.
		if (Actor->ActorHasTag("TownBox"))
		{
			AWorldCubeBase* worldCube = Cast<AWorldCubeBase>(Actor);
			if (!worldCube->isTown)
			{
				worldCube->isVisited = false;
				worldCube->isPortal=true;
				CellularActor->isPortalExist = true;
				break;
			}
		}
	}
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeGameAndUI());

	AIController = Cast<AHeroAIController>(GetController());

	
	
	//AIController->UnPossess();
	PlayerController->Possess(this);

	bIsMouseWheelClicked = false;

	isAttack = false;
	isDeath = false;
	landClick = false;
	oceanClick = false;
	isInBattle = false;

	maxKeyNum = 0;
	nowKeyNum = 0;


	// CAMERA
	// Bttle camera 와 world camera를 확한다.
	for (TActorIterator<ACameraActor> It(GetWorld()); It; ++It)
	{
		ACameraActor* CameraActor = *It;


		if (IsValid(CameraActor) && CameraActor->ActorHasTag(FName("BattleCamera")))
		{
			BattleCamera = CameraActor;
		}

		if (IsValid(CameraActor) && CameraActor->ActorHasTag(FName("WorldCamera")))
		{
			WorldMapCamera = CameraActor;
		}

		if (IsValid(CameraActor) && CameraActor->ActorHasTag(FName("BossBattleCamera")))
		{
			BossBattleCamera = CameraActor;
		}

		if (IsValid(CameraActor) && CameraActor->ActorHasTag(FName("BossMapCamera")))
		{
			BossMapCamera = CameraActor;
		}

		if (IsValid(CameraActor) && CameraActor->ActorHasTag(FName("PlayerCamera")))
		{
			PlayerCamera = CameraActor;
		}
	}

	//// 시작시 월드맵 카메라로 전환 
	ChangeToWorldMapCamera();




	isCutsceneEnd = false;

	FTimerHandle CutsceneTimerHandle;
	GetWorldTimerManager().SetTimer(CutsceneTimerHandle, this, &AHeroCharacter::cutSceneEnd, 16.0f, false);
	
}

void AHeroCharacter::OnLeftClick()
{
	if (!isInBattle)
	{
		FVector2D ScreenPosition;
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(ScreenPosition.X, ScreenPosition.Y))
		{
			FVector WorldLocation;
			FVector WorldDirection;
			if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldLocation, WorldDirection))
			{
				FHitResult HitResult;
				FVector StartLocation = WorldLocation;
				FVector EndLocation = StartLocation + WorldDirection * 10000.0f; // Adjust the distance as needed

				if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
				{

					AActor* HitActor = HitResult.GetActor();
					UE_LOG(LogTemp, Warning, TEXT("object name %s"), *HitActor->GetActorNameOrLabel());

					AWorldCubeBase* WCube = dynamic_cast<AWorldCubeBase*>(HitActor);

					if (HitActor->ActorHasTag("Ocean"))
					{
						LandOceanPos = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 100);
						oceanClick = true;

					}

					if (HitActor->ActorHasTag("Land"))
					{
						LandOceanPos = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 100);
						landClick = true;
					}

					// 캐스팅 결과 확인하기
					if (WCube != nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("MONSTER Power %d"), WCube->monsterPower);
						UE_LOG(LogTemp, Warning, TEXT("MONSTER Level %d"), WCube->monsterLevel);
						UE_LOG(LogTemp, Warning, TEXT("MONSTER Type %d"), WCube->monsterType);
					}
					else
					{

					}
				}
			}
		}
	}
	
}

void AHeroCharacter::OnRightClick()
{
	//UE_LOG(LogTemp,Warning,TEXT("rightclick"));
	FVector2D ScreenPosition;
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(ScreenPosition.X, ScreenPosition.Y))
	{
		//UE_LOG(LogTemp,Warning,TEXT("rightclick2"));
		FVector WorldLocation;
		FVector WorldDirection;
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(
			ScreenPosition.X, ScreenPosition.Y, WorldLocation, WorldDirection))
		{
			//UE_LOG(LogTemp,Warning,TEXT("rightclick3"));
			FHitResult HitResult;
			FVector StartLocation = WorldLocation;
			FVector EndLocation = StartLocation + WorldDirection * 10000.0f; // Adjust the distance as needed

			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,
			                                         ECollisionChannel::ECC_Visibility))
			{
				//UE_LOG(LogTemp,Warning,TEXT("rightclick4"));
				FVector TargetLocation = HitResult.Location;
				if (PlayerController)
				{
					//UE_LOG(LogTemp,Warning,TEXT("rightclick5"));
					if (!isInBattle || !isTown)
					{
						UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, TargetLocation);
					}
				}
			}
		}
	}
}

void AHeroCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AHeroCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AHeroCharacter::Turn_Right(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		PlayerController->AddYawInput(value);
	}
}

void AHeroCharacter::Pitch_Up(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		PlayerController->AddPitchInput(value);
	}
}
