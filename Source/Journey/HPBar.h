// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "HPBar.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UHPBar : public UUserWidget
{
	GENERATED_BODY()
public:
	//  Viewport 에 Add 될 때마다 호출됨
	//void NativeConstruct() override;
	//void set_bar_value_percent(float const value);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HpValue = nullptr;
	
};
