// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Journey/Items/Item.h"
#include "EquipItem.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UEquipItem : public UItem
{
	GENERATED_BODY()
public:
	UEquipItem();
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Item",meta=(ClampMin=0.0))
	int32 Armour;
	FString E_Description;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int E_Case;//0 - hemet 1 - vest 2 - weapon 3 - shoes
protected:
	virtual void Use(class ABaseUnit* Character) override;
};
