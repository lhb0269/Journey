// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopComponent.h"
#include "Items/Item.h"
// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	Capacity = 20;
}

void UShopComponent::BeginPlay()
{
	Super::BeginPlay();
	for(auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UShopComponent::AddItem(UItem* Item)
{
	if(Items.Num() >= Capacity || !Item)
    	{
    		return false;
    	}
    	Item->OwningShop = this;
    	Item -> World = GetWorld();
    	Items.Add(Item);
    
    	//Update UI
    	OnShopUpdated.Broadcast();
    
    	return true;
}

bool UShopComponent::RemoveItem(UItem* Item)
{
	if(Item)
	{
		Item->OwningShop = nullptr;
		Item -> World = nullptr;
		Items.RemoveSingle(Item);
		OnShopUpdated.Broadcast();
		return true;
	}
	return false;
}

bool UShopComponent::BuyItem(UItem* Item, UInventoryComponent* InventoryComponent)
{
	if(Item)
	{
		Item->OwningShop=nullptr;
		Item->OwingInventory=InventoryComponent;
		OnShopUpdated.Broadcast();
		return true;
	}
	return false;
}

void UShopComponent::Reroll()
{
	Items.Empty();
	for(int i=0;i<ItemCnt;++i)
	{
		int32 cnt = FMath::RandRange(0,DefaultItems.Num()-1);
		AddItem(DefaultItems[cnt]);
	}
}
