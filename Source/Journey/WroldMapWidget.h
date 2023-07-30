// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "ProceduralWorldMapGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameViewportClient.h"
#include "WroldMapWidget.generated.h"




/**
 * 
 */
UCLASS()
class JOURNEY_API UWroldMapWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
    UTexture2D* LandTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
    UTexture2D* WaterTexture;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
    UTexture2D* TownTexture;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
    UTexture2D* PlayerTexture;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
    UTexture2D* PortalTexture;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
    UTexture2D* BossTexture;

private:
    UPROPERTY(Meta = (BindWidget))
    UCanvasPanel* RootPanel;

    UPROPERTY(Meta = (BindWidget))
    UGridPanel* GridPanel;

	UFUNCTION()
	void OnVillageButtonClicked();
	
};
