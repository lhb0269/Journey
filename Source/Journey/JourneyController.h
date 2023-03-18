// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JourneyController.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AJourneyController : public APlayerController
{
	GENERATED_BODY()

	AJourneyController();
public:
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeletaTime) override;

	void SetNewDestination(const FVector Dest);

	bool bClickRightMouse;

	void InputRightMouseButtonPressed();
	void InputRightMouseButtonReleased();
	void MoveToMouseCursur();
};
