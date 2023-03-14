// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Engine/World.h"
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
			Item->Use(this);
			Item->OnUse(this);
		}
}

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

	//UE_LOG(LogTemp, Warning, TEXT("NowPos: %s, SavedPos: %s"), *GetActorLocation().ToString(), *MySaveGame->SavedPos.ToString());
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
		// CellularAutomata 가져오기 
		CellularActor = Cast<ACellularAutomata>(UGameplayStatics::GetActorOfClass(GetWorld(), ACellularAutomata::StaticClass()));

		AWorldCubeBase *worldCube = Cast<AWorldCubeBase>(OtherActor);

		// 방문했던곳인지 체크
		if (!worldCube->isVisited)
		{

			// 아니면 방문 했다고 체크
			CellularActor->CATileInfos[worldCube->cubeNumber].isVisited = true;

			MySaveGame->SavedPos = OtherActor->GetActorLocation();
			MySaveGame->CADatas = CellularActor->CATileInfos;
			MySaveGame->tileMax = CellularActor->Tilemax;
			MySaveGame->PlayerName = "TESTNAME";


			// 현재위치를 저장해야한다.
			// 이전에 들어갔던 곳인지 확인

			// 아니면 게임 저장
			SaveGame();

			// Load the next level
			UGameplayStatics::OpenLevel(this, "Town", true);
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
