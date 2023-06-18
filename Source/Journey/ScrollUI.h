// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollUI.generated.h"

/**
 * 
 */
UCLASS( )
class JOURNEY_API UScrollUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly,meta =(BindWidget))
		class UImage* Background;
public:
	UFUNCTION(BlueprintCallable)
		void ChooseFight();
	UFUNCTION(BlueprintCallable)
		void ChooseShot();
	UFUNCTION(BlueprintCallable)
		void ChooseMagic();
};
