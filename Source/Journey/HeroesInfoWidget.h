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
#include "HeroesInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UHeroesInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, Category = "Hero")
		ABaseUnit* archer;

	UPROPERTY(EditAnywhere, Category = "Hero")
		ABaseUnit* hero;

	UPROPERTY(EditAnywhere,  Category = "Hero")
		ABaseUnit* maze;

	int count;
private:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* RootPanel;

	UPROPERTY(Meta = (BindWidget))
	UButton* RightChangeBtn;
	UPROPERTY(Meta = (BindWidget))
		UButton* LeftChangeBtn;
	UPROPERTY(Meta = (BindWidget))
	UButton* QuitBtn;

	UPROPERTY(Meta = (BindWidget))
	UButton* SkillBtn;

	UPROPERTY(Meta = (BindWidget))
	UButton* EquipBtn;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* EXPBar;
	UPROPERTY(meta = (BindWidget))
	 UTextBlock* NameText;
	UPROPERTY(meta = (BindWidget))
	 UTextBlock* EXPText;
	UPROPERTY(meta = (BindWidget))
	 UTextBlock* LevelText;
	UPROPERTY(meta = (BindWidget))
	 UTextBlock* ClassText;
	UPROPERTY(meta = (BindWidget))
	 UImage* SkillBG;
	UPROPERTY(meta = (BindWidget))
	 UImage* EquipBG;


	UFUNCTION()
	void OnSkillBtnClicked();
	UFUNCTION()
	void OnEquipBtnClicked();


	UFUNCTION()
	void OnLeftBtnClicked();
	UFUNCTION()
	void OnRightBtnClicked();
};
