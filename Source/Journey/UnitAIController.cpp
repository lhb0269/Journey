// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAIController.h"

AUnitAIController::AUnitAIController()
{
}

void AUnitAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BTAsset)
	{
		RunBehaviorTree(BTAsset);
	}
}
