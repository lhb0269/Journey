// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "UnitHPMPWidget.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UUnitHPMPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHP(float NewHP);
	void UpdateMP(float NewMP);
public:
	void Initialize(class ABaseUnit* NewUnit);
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MPBar;
private:
	ABaseUnit* Unit;
};
