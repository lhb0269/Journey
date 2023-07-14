// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "BaseUnit.h"
#include "Components/Image.h"
#include "EngineUtils.h"
#include "ArcherUnit.h"
#include "MageUnit.h"
#include "HeroUnit.h"
#include "UpgradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Hero")
	ABaseUnit* archer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Hero")
	ABaseUnit* hero;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category = "Hero")
	ABaseUnit* maze;

	UPROPERTY(Meta = (BindWidget))
	UImage* ItemThumnail;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ItemName;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ItemLevel;

	UPROPERTY(Meta = (BindWidget))
    UTextBlock* ItemArmour;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock*RequireGold;
	
	UPROPERTY(Meta = (BindWidget))
	UButton* UpgradeBtn;
	
	int count;
	int32 UIcharcatercnt;
private:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* RootPanel;


	UFUNCTION(BlueprintCallable)
	void OnUpgradeBtnClicked(UEquipItem* Item);
	UFUNCTION(BlueprintCallable)
	UEquipItem* SelectItems(UEquipItem* Item);

	UEquipItem* Selected;
};
