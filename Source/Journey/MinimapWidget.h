// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "ProceduralWorldMapGenerator.h"
#include "ProceduralNoiseGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameViewportClient.h"

#include "MinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* LandTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* WallTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* HouseTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ShopTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* MotelTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* PlayerTexture;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 TownNum = 0;
private:
	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* RootPanel;

	UPROPERTY(Meta = (BindWidget))
	UGridPanel* GridPanel;

	UFUNCTION()
	void OnVillageButtonClicked();

};
