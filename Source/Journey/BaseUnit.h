// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitHPMPWidget.h"
#include "Components/WidgetComponent.h"
#include "Items/EquipItem.h"
#include "BaseUnit.generated.h"

UCLASS()
class JOURNEY_API ABaseUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnit();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	virtual void Attack();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	virtual void MoveTo(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	virtual void Idle();
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	virtual void UseSkill();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	virtual void Die();


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<UUnitHPMPWidget> HPMPWidgetClass;

	//UUnitHPMPWidget* HPMPWidgetComponent;


	float GetHealthPercent();
	float GetManaPercent();


	/// <summary>
	/// unitType
	/// -1 = none
	/// 0 = hero, 1 = archer, 2 = mage, 3= tanker
	/// </summay>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int unitType;

	//status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float nowHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float nowMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float maxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float maxMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isDeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isSkill1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isSkill2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool isAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool isStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Upgrade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Armour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FVector StartLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TArray<UEquipItem*>EquipItems;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
