// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "Journey/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "CellularAutomata.h"
#include "Kismet/GameplayStatics.h"

AHeroCharacter::AHeroCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	MySaveGame = Cast<UJourneySaveGame>(UGameplayStatics::LoadGameFromSlot("MySaveSlot", 0));
	if (nullptr == MySaveGame)
	{
		MySaveGame = GetMutableDefault<UJourneySaveGame>(); // Gets the mutable default object of a class.
	}


}

void AHeroCharacter::UseItem(UItem* Item)
{
		if(Item)
		{
			Item->Use(this);
			Item->OnUse(this);
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
	// CellularAutomata 가져오기 
	CellularActor = Cast<ACellularAutomata>(UGameplayStatics::GetActorOfClass(GetWorld(), ACellularAutomata::StaticClass()));
	CellularActor->height;

	MySaveGame->SavedPos = GetActorLocation();
	//MySaveGame->height = CellularActor->height;

	// 현재위치를 저장해야한다.
	

	//for (int i = 0; i < 6; ++i) {
	//	for (int j = 0; j < 6; ++j) {
	//		UE_LOG(LogTemp, Log, TEXT("Character Location :: %d"), CellularActor->height[i][j]);
	//	}
	//}
	
	//MySaveGame->height = ;
	
	UGameplayStatics::SaveGameToSlot(MySaveGame, "MySaveSlot", 0);


}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Pressed, this, &AHeroCharacter::SaveGame);
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
