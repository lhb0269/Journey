// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileInfo.h"
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	bool isBossSystem;


	
	void resetBattleField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};