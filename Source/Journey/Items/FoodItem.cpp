// Fill out your copyright notice in the Description page of Project Settings.


#include "Journey/Items/FoodItem.h"
#include "Journey/InventoryComponent.h"
#include "Journey/ShopComponent.h"

void UFoodItem::Use(AHeroCharacter* Character)
{
	if(Character)
	{
		if(OwingInventory)
		{
			OwingInventory->RemoveItem(this);
		}
		else
		{
			OwningShop->RemoveItem(this);
		}
	}
}
