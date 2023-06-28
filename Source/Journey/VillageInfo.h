// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "VillageInfo.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UVillageInfo : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void SetUpText(const FString& VillageName,const FVector& pos,const FVector& savedpos);
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* VillageNameBlock;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		FVector Location;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector SavedLocation;
	void OnClicked();
private:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* RootPanel;
	
	UPROPERTY(Meta = (BindWidget))
	UButton* UseButton;
};
