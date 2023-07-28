// Fill out your copyright notice in the Description page of Project Settings.


#include "Journey/Items/StaminaPosion.h"
#include "Journey/InventoryComponent.h"
#include "Journey/ShopComponent.h"
UStaminaPosion::UStaminaPosion()
{
	HealStamina = 0.1;
	cost = 100;
	ItemDescription = "Heal 10 Stamina";
}

void UStaminaPosion::Use(ABaseUnit* Character)
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
