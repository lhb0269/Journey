// Fill out your copyright notice in the Description page of Project Settings.


#include "Journey/Items/FoodItem.h"

#include "Journey/HeroCharacter.h"
#include "Journey/InventoryComponent.h"
#include "Journey/ShopComponent.h"

UFoodItem::UFoodItem()
{
	HealthToHeal = cost;
	ItemDescription = "Heal 5 hp";
}

void UFoodItem::Use(ABaseUnit* Character)
{
	if(Character)
	{
		if(OwingInventory)
		{
			//Character->hp+=(HealthToHeal/2);
			OwingInventory->RemoveItem(this);
		}
		else
		{
			OwningShop->RemoveItem(this);
		}
	}
}
