// Copyright Epic Games, Inc. All Rights Reserved.


#include "JourneyGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AJourneyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();
}
