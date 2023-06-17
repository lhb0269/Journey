// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollUI.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class JOURNEY_API UScrollUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta =(BindWidget))
	class UImage* Background;
};
