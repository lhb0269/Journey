// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "Journey/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameDataSingleton.h"
#include "Items/Item.h"
#include "CellularAutomata.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"


AHeroCharacter::AHeroCharacter()
{

	isAttack = false;
	isDeath = false;

	WorldCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("WorldCameraBoom"));
	WorldCameraBoom->SetupAttachment(RootComponent);
	WorldCameraBoom->TargetArmLength = 800.0f;
	//WorldCameraBoom->bUsePawnControlRotation = true;

	WorldFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("WorldFollowCamera"));
	WorldFollowCamera->SetupAttachment(WorldCameraBoom, USpringArmComponent::SocketName);
	//WorldFollowCamera->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = true;

	WorldFollowCamera->bAutoActivate = false;
	FollowCamera->bAutoActivate = true;


	FollowCamera->SetActive(true);
	WorldFollowCamera->SetActive(true);


	GetCharacterMovement()->bOrientRotationToMovement = true;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	shop = CreateDefaultSubobject<UShopComponent>("Shop");
	shop->Capacity = 20;

	hp = 50;
	Armour = 200;
	gold=200;

	isTown = false;
	UCapsuleComponent* MyCapsuleComponent = GetCapsuleComponent();
	MyCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AHeroCharacter::OnOverlapBegin);
}

void AHeroCharacter::UseItem(UItem* Item)
{
		if(Item)
		{
			if(Item->OwingInventory!=nullptr && Item-> OwningShop == nullptr)
			{
				Item->Use(this);
				Item->OnUse(this);
			}
			if(Item->OwingInventory==nullptr && Item-> OwningShop != nullptr)//사는거
			{
				if(gold >= Item->cost)
				{
					Inventory->AddItem(Item);
					shop->RemoveItem(Item);
					UE_LOG(LogTemp,Warning,TEXT("%d"),gold);
					gold-=Item->cost;
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

void AHeroCharacter::LoadGame()
{

}

void AHeroCharacter::SaveGame()
{

}

void AHeroCharacter::GoToWorldMap()
{
	SetActorRotation(FRotator(0,0,0));
	SetActorLocation(UGameDataSingleton::GetInstance()->SavedPos);
	PlayerController->bShowMouseCursor = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	//UGameplayStatics::OpenLevel(this, "WorldMap", true);
	//FollowCamera->SetActive(false);
	//WorldFollowCamera->SetActive(true);
	SwitchToWorldFollowCamera();
	//WorldFollowCamera->SetActive(false);
	isTown=false;
}

void AHeroCharacter::ChangeCamera(bool isWorld)
{
	CellularActor = Cast<ACellularAutomata>(UGameplayStatics::GetActorOfClass(GetWorld(), ACellularAutomata::StaticClass()));

	if (isWorld)
	{
		WorldFollowCamera->SetActive(true);
		FollowCamera->SetActive(false);
	}
	else
	{
		WorldFollowCamera->SetActive(false);
		//FollowCamera->SetActive(true);
	}
}

void AHeroCharacter::ChangeGameMode()
{

}

void AHeroCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapped actor has a specific tag
	if (OtherActor->ActorHasTag("TownBox"))
	{
		// CellularAutomata �������� 
		//CellularActor = Cast<ACellularAutomata>(UGameplayStatics::GetActorOfClass(GetWorld(), ACellularAutomata::StaticClass()));

		AWorldCubeBase *worldCube = Cast<AWorldCubeBase>(OtherActor);

		// �湮�ߴ������� üũ
		if (!worldCube->isVisited)
		{

			// �ƴϸ� �湮 �ߴٰ� üũ
 			UGameDataSingleton::GetInstance()->TileInfos[worldCube->cubeNumber].isVisited = true;
			UGameDataSingleton::GetInstance()->SavedPos = OtherActor->GetActorLocation();
			//CellularActor->CATileInfos[worldCube->cubeNumber].isVisited = true;

			//MySaveGame->SavedPos = OtherActor->GetActorLocation();
			//MySaveGame->CADatas = CellularActor->CATileInfos;
			//MySaveGame->tileMax = CellularActor->Tilemax;
			//MySaveGame->PlayerName = "TESTNAME";


			// ������ġ�� �����ؾ��Ѵ�.
			// ������ ���� ������ Ȯ��

			// �ƴϸ� ���� ����
			//SaveGame();

			// check town or battle
			// 0403 일단 무조건 Town 쪽으로 이동하게 설정
			if (worldCube->isTown)
			{
				//ChangeController(false);
				worldCube->isVisited = true;
				SetActorRotation(FRotator(0,0,0));
				SetActorLocation(worldCube->Location);
				SwitchToFollowCamera();
				PlayerController->SetInputMode(FInputModeGameOnly());
				PlayerController->bShowMouseCursor=false;
				bUseControllerRotationPitch = true;
				bUseControllerRotationYaw = true;
				isTown = true;
			}
			else
			{
				//ChangeController(true);
				worldCube->isVisited = true;
				worldCube->isKey = false;
				SetActorRotation(FRotator(0,0,0));
				SetActorLocation(UGameDataSingleton::GetInstance()->BattleSpawnPos);
				SwitchToFollowCamera();
				PlayerController->SetInputMode(FInputModeGameOnly());
				PlayerController->bShowMouseCursor=false;
				bUseControllerRotationPitch = true;
				bUseControllerRotationYaw = true;
				isTown = true;
			}

			
		}

	
	}
}

void AHeroCharacter::SwitchToFollowCamera()
{

	// Activate the FollowCamera
	WorldFollowCamera->SetActive(false);
	FollowCamera->SetActive(true);
}

void AHeroCharacter::SwitchToWorldFollowCamera()
{
	// Activate the WorldFollowCamera
	FollowCamera->SetActive(false);
	WorldFollowCamera->SetActive(true);



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



	PlayerInputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &AHeroCharacter::OnZoomIn);
	PlayerInputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &AHeroCharacter::OnZoomOut);

}

void AHeroCharacter::OnZoomIn()
{
	float NewFieldOfView = FMath::Clamp(WorldFollowCamera->FieldOfView - 5.f, 20.f, 180.f);

	// Set the new field of view
	WorldFollowCamera->SetFieldOfView(NewFieldOfView);

	// Adjust the spring arm's length to compensate for the new field of view
	float CameraDistance = WorldCameraBoom->TargetArmLength;
	float NewCameraDistance = CameraDistance / (NewFieldOfView / WorldFollowCamera->FieldOfView);
	WorldCameraBoom->TargetArmLength = NewCameraDistance;

	// Increase the camera's field of view to zoom out
	//WorldFollowCamera->SetFieldOfView(WorldFollowCamera->FieldOfView + 5.f);
}

void AHeroCharacter::OnZoomOut()
{
	float NewFieldOfView = FMath::Clamp(WorldFollowCamera->FieldOfView + 5.f, 20.f, 180.f);

	// Set the new field of view
	WorldFollowCamera->SetFieldOfView(NewFieldOfView);

	// Adjust the spring arm's length to compensate for the new field of view
	float CameraDistance = WorldCameraBoom->TargetArmLength;
	float NewCameraDistance = CameraDistance / (NewFieldOfView / WorldFollowCamera->FieldOfView);
	WorldCameraBoom->TargetArmLength = NewCameraDistance;

	// Decrease the camera's field of view to zoom in
	//WorldFollowCamera->SetFieldOfView(WorldFollowCamera->FieldOfView - 5.f);
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

	isAttack = false;
	isDeath = false;
	isInBattle = false;
}

void AHeroCharacter::OnLeftClick()
{
	//FVector2D ScreenPosition;
	//if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(ScreenPosition.X, ScreenPosition.Y))
	//{
	//	FVector WorldLocation;
	//	FVector WorldDirection;
	//	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldLocation, WorldDirection))
	//	{
	//		FHitResult HitResult;
	//		FVector StartLocation = WorldLocation;
	//		FVector EndLocation = StartLocation + WorldDirection * 10000.0f; // Adjust the distance as needed

	//		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	//		{

	//			AActor* HitActor = HitResult.GetActor();

	//			AWorldCubeBase* WCube = dynamic_cast<AWorldCubeBase*>(HitActor);

	//			// 캐스팅 결과 확인하기
	//			if (WCube != nullptr)
	//			{
	//				UE_LOG(LogTemp, Warning, TEXT("MONSTER Power %d"), WCube->monsterPower);
	//				UE_LOG(LogTemp, Warning, TEXT("MONSTER Level %d"), WCube->monsterLevel);
	//				UE_LOG(LogTemp, Warning, TEXT("MONSTER Type %d"), WCube->monsterType);
	//			}
	//			else
	//			{
	//				
	//			}
	//		}
	//	}
	//}
}

void AHeroCharacter::OnRightClick()
{
	UE_LOG(LogTemp,Warning,TEXT("rightclick"));
	FVector2D ScreenPosition;
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(ScreenPosition.X, ScreenPosition.Y))
	{
		UE_LOG(LogTemp,Warning,TEXT("rightclick2"));
		FVector WorldLocation;
		FVector WorldDirection;
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldLocation, WorldDirection))
		{
			UE_LOG(LogTemp,Warning,TEXT("rightclick3"));
			FHitResult HitResult;
			FVector StartLocation = WorldLocation;
			FVector EndLocation = StartLocation + WorldDirection * 10000.0f; // Adjust the distance as needed

			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
			{
				UE_LOG(LogTemp,Warning,TEXT("rightclick4"));
				FVector TargetLocation = HitResult.Location;
				if (PlayerController)
				{
					UE_LOG(LogTemp,Warning,TEXT("rightclick5"));
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, TargetLocation);
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
