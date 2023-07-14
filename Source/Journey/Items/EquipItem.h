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
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Armour;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FString E_Set;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)//0 - hemet 1 - vest 2 - weapon 3 - shoes
	int E_Case;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int Level;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 UpgradeCost;
	void settingItem(UEquipItem* origin);
	void LevelUP();
protected:
	virtual void Use(class ABaseUnit* Character) override;
};
