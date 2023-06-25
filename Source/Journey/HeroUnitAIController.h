// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"
#include "HeroUnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AHeroUnitAIController : public AUnitAIController
{
	GENERATED_BODY()
public:
	AHeroUnitAIController();
};
