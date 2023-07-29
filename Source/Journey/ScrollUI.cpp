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
	hero->Upgrade+= 5;
}

void UScrollUI::ChooseShot()
{
	archer->Upgrade+= 5;
}

void UScrollUI::ChooseMagic()
{
	maze->Upgrade+= 5;
}
