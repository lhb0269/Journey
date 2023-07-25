// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollUI.h"
#include "GameManager.h"

void UScrollUI::NativeConstruct()
{
	Super::NativeConstruct();
	for (TActorIterator<AGameManager> It(GetWorld()); It; ++It)
	{
		AGameManager* GM = *It;
		archer = GM->archer;
		hero = GM->hero;
		maze = GM->maze;
       
	}
}

void UScrollUI::ChooseFight()
{
	hero->power+= 5;
	// Instance = UGameDataSingleton::GetInstance();
	// if(Instance != nullptr)
	// {
	// 	Instance->FightUpgrade();
	// }
}

void UScrollUI::ChooseShot()
{
	archer->power+= 5;
	// Instance = UGameDataSingleton::GetInstance();
	// if(Instance != nullptr)
	// {
	// 	Instance->ShotUpgrade();
	// }
}

void UScrollUI::ChooseMagic()
{
	maze->power+= 5;
	// Instance = UGameDataSingleton::GetInstance();
	// if(Instance != nullptr)
	// {
	// 	Instance->MagicUpgrade();
	// }
}
