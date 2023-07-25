// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameDataSingleton.h"
#include "ScrollUI.generated.h"

/**
 * 
 */
UCLASS( )
class JOURNEY_API UScrollUI : public UUserWidget
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
private:
	UGameDataSingleton* Instance;
};
