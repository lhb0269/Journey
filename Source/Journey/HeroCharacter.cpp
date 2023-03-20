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
#include "HeroAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "CellularAutomata.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

AHeroCharacter::AHeroCharacter()
{

	WorldCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("WorldCameraBoom"));
	WorldCameraBoom->SetupAttachment(RootComponent);
	WorldCameraBoom->TargetArmLength = 800.0f;
	//WorldCameraBoom->bUsePawnControlRotation = true;

	WorldFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("WorldFollowCamera"));
	WorldFollowCamera->SetupAttachment(WorldCameraBoom, USpringArmComponent::SocketName);
	//WorldFollowCamera->bUsePawnControlRotation = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//FollowCamera->bUsePawnControlRotation = true;

	WorldFollowCamera->bAutoActivate = false;
	FollowCamera->bAutoActivate = false;


	WorldFollowCamera->SetActive(true);
	FollowCamera->SetActive(false);


	GetCharacterMovement()->bOrientRotationToMovement = true;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	shop = CreateDefaultSubobject<UShopComponent>("Shop");
	shop->Capacity = 20;

	hp = 50;
	gold=200;

	MySaveGame = Cast<UJourneySaveGame>(UGameplayStatics::LoadGameFromSlot("MySaveSlot", 0));
	if (nullptr == MySaveGame)
	{
		MySaveGame = GetMutableDefault<UJourneySaveGame>(); // Gets the mutable default object of a class.
	}
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
	AHeroAIController* AIController = Cast<AHeroAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToLocation(DestLocation);
	}
}

void AHeroCharacter::LoadGame()
{
	MySaveGame = Cast<UJourneySaveGame>(UGameplayStatics::LoadGameFromSlot("MySaveSlot", 0));

	if (MySaveGame == nullptr)
	{

	}
}

void AHeroCharacter::SaveGame()
{
	//MySaveGame->height = ;
	
	UGameplayStatics::SaveGameToSlot(MySaveGame, "MySaveSlot", 0);
}

void AHeroCharacter::GoToWorldMap()
{
	UGameplayStatics::OpenLevel(this, "WorldMap", true);

}

void AHeroCharacter::ChangeCamera(bool isWorld)
{
	if (isWorld)
	{
		WorldFollowCamera->SetActive(true);
		FollowCamera->SetActive(false);
	}
	else
	{
		WorldFollowCamera->SetActive(false);
		FollowCamera->SetActive(true);
	}
}

void AHeroCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapped actor has a specific tag
	if (OtherActor->ActorHasTag("TownBox"))
	{
		// CellularAutomata �������� 
		CellularActor = Cast<ACellularAutomata>(UGameplayStatics::GetActorOfClass(GetWorld(), ACellularAutomata::StaticClass()));

		AWorldCubeBase *worldCube = Cast<AWorldCubeBase>(OtherActor);

		// �湮�ߴ������� üũ
		if (!worldCube->isVisited)
		{

			// �ƴϸ� �湮 �ߴٰ� üũ
			CellularActor->CATileInfos[worldCube->cubeNumber].isVisited = true;

			MySaveGame->SavedPos = OtherActor->GetActorLocation();
			MySaveGame->CADatas = CellularActor->CATileInfos;
			MySaveGame->tileMax = CellularActor->Tilemax;
			MySaveGame->PlayerName = "TESTNAME";


			// ������ġ�� �����ؾ��Ѵ�.
			// ������ ���� ������ Ȯ��

			// �ƴϸ� ���� ����
			SaveGame();

			// check town or battle
			if (worldCube->isTown)
			{
				// Load the next level
				UGameplayStatics::OpenLevel(this, "Town", true);
			}
			else
			{
				// Load the next level
				UGameplayStatics::OpenLevel(this, "AIMAP", true);
			}

			
		}

	
	}
}



void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Pressed, this, &AHeroCharacter::GoToWorldMap);
	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &AHeroCharacter::OnRightClick);

}
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeGameAndUI());
}

void AHeroCharacter::OnRightClick()
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
				FVector TargetLocation = HitResult.Location;

				APlayerController* PlayerController = Cast<APlayerController>(GetController());
				if (PlayerController)
				{
					
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
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AHeroCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}
