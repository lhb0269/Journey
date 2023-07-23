// Fill out your copyright notice in the Description page of Project Settings.


#include "Journey/Items/EquipItem.h"
#include "Journey/HeroCharacter.h"
#include "Journey/InventoryComponent.h"
#include "Journey/ShopComponent.h"
UEquipItem::UEquipItem()
{
	Armour = 5;
	Level = 1;
	UpgradeCost = 500;
	Owner = nullptr;
}

void UEquipItem::settingItem(UEquipItem* origin)
{
	Armour = origin->Armour;
	E_Set = origin->E_Set;
	E_Case = E_Case;
	Thumbnail = origin->Thumbnail;
	ItemDisplayName = origin->ItemDisplayName;
	ItemDescription = origin->ItemDescription;
	weight = origin->weight;
	cost = origin->cost;
}

void UEquipItem::LevelUP()
{
	if(Level<=5)
	{
		Level++;
		Armour*=1.5;
		if(Armour==1)
			Armour++;
		UpgradeCost*=2;
		if(Owner != nullptr)
		{
			switch (E_Case)
			{
			case 0:
				Owner->EquipItems[0]->Armour = Armour;
				break;
			case 1:
				Owner->EquipItems[1]->Armour = Armour;
				break;
			case 2:
				Owner->EquipItems[2]->Armour = Armour;
				break;
			case 3:
				Owner->EquipItems[3]->Armour = Armour;
				break;
			}
		}
	}
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
	Owner = Character;
}
