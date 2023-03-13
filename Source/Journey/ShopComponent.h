// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopUpdated);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOURNEY_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShopComponent();
	virtual void BeginPlay() override;
	bool AddItem(class UItem* Item);
	bool RemoveItem(class UItem* Item);
	bool BuyItem(class UItem* Item,class UInventoryComponent* InventoryComponent);
	UPROPERTY(EditDefaultsOnly,Instanced)
	TArray<class UItem*>DefaultItems;

	UPROPERTY(EditDefaultsOnly,Category="Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable,Category="Inventory")
	FOnShopUpdated OnShopUpdated;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Items")
	TArray<class UItem*>Items;		
};
