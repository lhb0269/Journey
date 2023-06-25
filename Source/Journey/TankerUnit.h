// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "TankerUnit.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API ATankerUnit : public ABaseUnit
{
	GENERATED_BODY()
public:
	ATankerUnit();
	virtual void Attack() override;
	virtual void MoveTo(FVector Location) override;
	virtual void Idle() override;
	virtual void UseSkill() override;
	virtual void Die() override;
};
