// Fill out your copyright notice in the Description page of Project Settings.


#include "Journey/Items/Item.h"

UItem::UItem()
{
	weight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}
