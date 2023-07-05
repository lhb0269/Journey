// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUnit.h"

#include "Components/ProgressBar.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "GameManager.h"
#include "HeroesBattleUI.generated.h"



/**
 * 
 */
UCLASS()
class JOURNEY_API UHeroesBattleUI : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	float GetHPBar1Percent_Implementation() const;

	float GetMPBar1Percent_Implementation() const;

	float GetHPBar2Percent_Implementation() const;

	float GetMPBar2Percent_Implementation() const;

	float GetHPBar3Percent_Implementation() const;

	float GetMPBar3Percent_Implementation() const;

	float GetHPBar4Percent_Implementation() const;

	float GetMPBar4Percent_Implementation() const;


private:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* RootPanel;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* HPBar1;
	UPROPERTY(Meta = (BindWidget))
	UProgressBar* MPBar1;
	UPROPERTY(Meta = (BindWidget))
		UImage* Image1;
	UPROPERTY(Meta = (BindWidget))
	UButton* item1_1;
	UPROPERTY(Meta = (BindWidget))
	UButton* item1_2;
	UPROPERTY(Meta = (BindWidget))
	UButton* item1_3;
	UPROPERTY(Meta = (BindWidget))
	UButton* item1_4;

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* HPBar2;
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* MPBar2;
	UPROPERTY(Meta = (BindWidget))
		UImage* Image2;
	UPROPERTY(Meta = (BindWidget))
		UButton* item2_1;
	UPROPERTY(Meta = (BindWidget))
		UButton* item2_2;
	UPROPERTY(Meta = (BindWidget))
		UButton* item2_3;
	UPROPERTY(Meta = (BindWidget))
		UButton* item2_4;

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* HPBar3;
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* MPBar3;
	UPROPERTY(Meta = (BindWidget))
		UImage* Image3;
	UPROPERTY(Meta = (BindWidget))
		UButton* item3_1;
	UPROPERTY(Meta = (BindWidget))
		UButton* item3_2;
	UPROPERTY(Meta = (BindWidget))
		UButton* item3_3;
	UPROPERTY(Meta = (BindWidget))
		UButton* item3_4;

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* HPBar4;
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* MPBar4;
	UPROPERTY(Meta = (BindWidget))
		UImage* Image4;
	UPROPERTY(Meta = (BindWidget))
		UButton* item4_1;
	UPROPERTY(Meta = (BindWidget))
		UButton* item4_2;
	UPROPERTY(Meta = (BindWidget))
		UButton* item4_3;
	UPROPERTY(Meta = (BindWidget))
		UButton* item4_4;



};
