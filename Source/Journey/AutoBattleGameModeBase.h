// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/GameModeBase.h"
#include "MonsterCharacter.h"
#include "AutoBattleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_API AAutoBattleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	TSubclassOf<AMonsterCharacter> MonsterClass;

	UPROPERTY(EditAnywhere, Category = "Monster")
	TArray<AActor*> SpawnPoints;
public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StartBattle();

	void SpawnUnits();
};
