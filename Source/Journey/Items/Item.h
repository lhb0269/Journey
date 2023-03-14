// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType,Blueprintable,EditInlineNew,DefaultToInstanced)
class JOURNEY_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem();

	virtual class UWorld* GetWorld() const {return World;};
	UPROPERTY(Transient)
	class UWorld* World;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Item")
	FText UseActionText;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Item")
	class UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Item")
	class UTexture2D* Thumbnail;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Item")
	FText ItemDisplayName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Item",meta = (MultiLine = true))
	FText ItemDescription;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Item",meta = (ClampMin =0.0))
	float weight;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Item")
	int32 cost;
	UPROPERTY()
	class UInventoryComponent* OwingInventory;
	class UShopComponent* OwningShop;
	virtual void Use(class AHeroCharacter* Character) PURE_VIRTUAL(UItem,);
	void Buy(UInventoryComponent* Inventory);
	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AHeroCharacter* Character);
};
