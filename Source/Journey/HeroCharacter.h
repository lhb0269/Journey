// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "Engine/DataTable.h"
#include "HeroCharacter.generated.h"

/**
 * 
 */
//struct FCharacterInfo :public FTableRowBase
//{
//	GENERATED_BODY()
//public:
//	FCharacterInfo()
//	{
//
//	}
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 hp;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 mp;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 power;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 armor;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 as;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 skill1;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 skill2;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 skill3;
//	// 포만감
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 satiety;
//	// 피로도
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 fatigue;
//
//};

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

	UFUNCTION()

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float value);
	void MoveRight(float value);
};
