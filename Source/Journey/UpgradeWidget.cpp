// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeWidget.h"
#include"GameManager.h"
#include"GameDataSingleton.h"

void UUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (TActorIterator<AGameManager> It(GetWorld()); It; ++It)
	{
		AGameManager* GM = *It;
		archer = GM->archer;
		hero = GM->hero;
		maze = GM->maze;
       
	}
	count = 0;
	UIcharcatercnt = 0;
	// TextWidget->SetText(FText::FromString(Text));

}

void UUpgradeWidget::OnUpgradeBtnClicked(UEquipItem* Item)
{
	Item->LevelUP();
	ItemThumnail->SetBrushFromTexture(Item->Thumbnail);
	ItemName->SetText(FText::FromString(Item->E_Set));
	ItemLevel->SetText(FText::FromString(FString::FromInt(Item->Level)));
	ItemArmour->SetText(FText::FromString(FString::FromInt(Item->Armour)));
	RequireGold->SetText(FText::FromString(FString::FromInt(Item->UpgradeCost)));
}

UEquipItem* UUpgradeWidget::SelectItems(UEquipItem* Item)
{
	ItemThumnail->SetBrushFromTexture(Item->Thumbnail);
	ItemName->SetText(FText::FromString(Item->E_Set));
	ItemLevel->SetText(FText::FromString(FString::FromInt(Item->Level)));
	ItemArmour->SetText(FText::FromString(FString::FromInt(Item->Armour)));
	RequireGold->SetText(FText::FromString(FString::FromInt(Item->UpgradeCost)));
	return Item;
}
