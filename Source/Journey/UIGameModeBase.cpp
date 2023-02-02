// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AUIGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();


}
