// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "HeroUnit.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AHeroUnit : public ABaseUnit
{
	GENERATED_BODY()
public:
	AHeroUnit();
	virtual void Attack() override;
	virtual void MoveTo(FVector Location) override;
	virtual void Idle() override;
	virtual void UseSkill() override;
	virtual void Die() override;
	
};
