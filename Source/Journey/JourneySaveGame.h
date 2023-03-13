// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellularAutomata.h"
#include "GameFramework/SaveGame.h"
#include "JourneySaveGame.generated.h"


using namespace std;

/**
 * 
 */
UCLASS()
class JOURNEY_API UJourneySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UJourneySaveGame();

public:
	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;

	UPROPERTY(VisibleAnywhere, Category = "Saved Location")
	FVector SavedPos;

	UPROPERTY()
	int32 tileMax;

	// CellularAutomata ������ �� ����
	TArray<TArray<FCAStruct>> CADatas;
	
};
