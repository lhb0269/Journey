// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileInfo.h"
#include "Blueprint/UserWidget.h"
#include "BattleSystem.generated.h"

UCLASS()
class JOURNEY_API ABattleSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleSystem();


	// MONSTER, PLAYER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class ATileInfo> TileInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> BattleEndWidgetClass;

	UPROPERTY()
	TArray<AActor*> Heroes;

	UPROPERTY()
	TArray<AActor*> Monsters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	bool isBossSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	int RewardGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	int enemyPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	bool isBattleStart;

	void SpawnHeroInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation);
	void SpawnMonsterInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation);

	void resetBattleField(int monsterPower);

	void ShowBattleEndWidget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
