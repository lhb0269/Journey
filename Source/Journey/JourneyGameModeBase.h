// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "JourneyGameModeBase.generated.h"


/**
 * 
 */
//struct FChracterInfo :public FTableRowBase
//{
//	GENERATED_BODY()
//public:
//	FChracterInfo()
//	{
//	}
//};


UCLASS()
class JOURNEY_API AJourneyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	UUserWidget* CurrentWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> HUDWidget;
	
};
