// Fill out your copyright notice in the Description page of Project Settings.


#include "Journey/Items/Item.h"

#include "Journey/ShopComponent.h"

UItem::UItem()
{
	weight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void UItem::Buy(UInventoryComponent* Inventory)
{
	if (OwningShop != nullptr && OwingInventory == nullptr)
	{
		OwningShop->BuyItem(this,Inventory);
	}
}
