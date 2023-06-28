// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VillageInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Components/WrapBox.h"
#include "PortalUI.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UPortalUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	TSubclassOf<UVillageInfo> VillageInfoClass;
	UVillageInfo* VillageInfo;
	void AddVillage(const FString& VillageName,const FVector& pos,const FVector& savedpos);
private:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* RootPanel;

	UPROPERTY(Meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(Meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(Meta = (BindWidget))
	UOverlay* Overlay;

	UPROPERTY(Meta = (BindWidget))
	UWrapBox* VillageBox;
	
};
