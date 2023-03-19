// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "InventoryComponent.h"
#include"ShopComponent.h"
#include "Engine/DataTable.h"
#include "JourneySaveGame.h"
#include "CellularAutomata.h"
#include "ProceduralNoiseGenerator.h"
#include "HeroCharacter.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterInfo :public FTableRowBase
{
	GENERATED_BODY()
public:
	FCharacterInfo()
	{

	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 mp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 as;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 skill1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 skill2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 skill3;
	// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 satiety;
	// �Ƿε�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 fatigue;

};

UCLASS()
class JOURNEY_API AHeroCharacter : public ABasicCharacter
{
	GENERATED_BODY()
public:
	AHeroCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* WorldCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* WorldFollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UInventoryComponent* Inventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UShopComponent* shop;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 hp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 mp;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 Armour;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 gold;
	
	UFUNCTION(BlueprintCallable,Category="Items")
	void UseItem(class UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveToLocation(const FVector& DestLocation);



	UJourneySaveGame* MySaveGame;
	// 월드맵 정보
	ACellularAutomata* CellularActor;
	AProceduralNoiseGenerator* ProceduralActor;

	void LoadGame();
	void SaveGame();

	void GoToWorldMap();

	void ChangeCamera(bool isWorld);

	// 월드맵 충돌 체크
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	//UFUNCTION(BlueprintCallable,Category="Items")
	//void BuyItem(UItem* Item,UInventoryComponent* UserInventory);
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	void MoveForward(float value);
	void MoveRight(float value);
	void OnRightClick();
};
