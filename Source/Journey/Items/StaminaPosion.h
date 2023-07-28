// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Journey/Items/Item.h"
#include "StaminaPosion.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UStaminaPosion : public UItem
{
	GENERATED_BODY()
public:
	UStaminaPosion();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="StaminaPosion")
	float HealStamina;
protected:
	virtual void Use(class ABaseUnit* Character) override;
};
