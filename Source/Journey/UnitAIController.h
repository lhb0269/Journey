// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AUnitAIController : public AAIController
{
	GENERATED_BODY()
public:
	AUnitAIController();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BTAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBlackboardData* BBAsset;
};
