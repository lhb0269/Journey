// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollUI.h"

void UScrollUI::ChooseFight()
{
	Instance = UGameDataSingleton::GetInstance();
	if(Instance != nullptr)
	{
		Instance->FightUpgrade();
	}
}

void UScrollUI::ChooseShot()
{
	Instance = UGameDataSingleton::GetInstance();
	if(Instance != nullptr)
	{
		Instance->ShotUpgrade();
	}
}

void UScrollUI::ChooseMagic()
{
	Instance = UGameDataSingleton::GetInstance();
	if(Instance != nullptr)
	{
		Instance->MagicUpgrade();
	}
}
