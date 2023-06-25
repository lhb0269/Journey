// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"
#include "MazeUnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AMazeUnitAIController : public AUnitAIController
{
	GENERATED_BODY()
public:
	AMazeUnitAIController();
};
