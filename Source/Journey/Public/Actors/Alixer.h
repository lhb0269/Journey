// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Item.h"
#include "Alixer.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AAlixer : public AItem
{
	GENERATED_BODY()
public:
	AAlixer();
protected:
	UPROPERTY(EditAnywhere)
	float Value;
public:
    virtual void Use(AHeroCharacter* Character)override;
};
