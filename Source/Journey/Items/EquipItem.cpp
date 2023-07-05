// Fill out your copyright notice in the Description page of Project Settings.


#include "Journey/Items/EquipItem.h"
#include "Journey/HeroCharacter.h"
#include "Journey/InventoryComponent.h"
#include "Journey/ShopComponent.h"
UEquipItem::UEquipItem()
{
	Armour = FMath::RandRange(1,10);
}

void UEquipItem::Use(ABaseUnit* Character)
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
	switch(E_Case)
	{
		case 0:
			Character->EquipItems.Add(this);
			break;
		case 1:
			Character->EquipItems.Add(this);
			break;
		case 2:
			Character->EquipItems.Add(this);
			break;
		case 3:
			Character->EquipItems.Add(this);
			break;
	}
}
