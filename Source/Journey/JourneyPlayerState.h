// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JourneyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AJourneyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AJourneyPlayerState();

	int32 GetGameHighScore() const;
	FString SaveSlotName;

	void InitPlayerData();
	void SavePlayerData();
	void AddExp();
	void AddGameScore();

protected:
	UPROPERTY(Transient)
	int32 GameHighScore;
	int32 Exp;
	int32 CharacterLevel;
	int32 GameScore;
};
