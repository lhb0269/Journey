// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralWorldMapGenerator.h"
#include "ProceduralNoiseGenerator.h"
#include "GameFramework/Actor.h"
#include "MovieSceneSequenceID.h"
#include "HeroCharacter.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "BaseUnit.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"


UCLASS()
class JOURNEY_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();


	UPROPERTY(EditAnywhere)
	AProceduralWorldMapGenerator* worldMap;


	UPROPERTY(EditAnywhere)
	AProceduralNoiseGenerator* townMap[9];

	UPROPERTY(EditAnywhere, Category = "Cutscenes")
	ULevelSequence* IntroSequence;
	UPROPERTY(EditAnywhere, Category = "Cutscenes")
	ULevelSequence* BossSequence;
	UPROPERTY(EditAnywhere)
	AHeroCharacter* heroCharacter;

	UPROPERTY(EditAnywhere, Category = "Hero")
		ABaseUnit* archer;

	UPROPERTY(EditAnywhere, Category = "Hero")
		ABaseUnit* hero;

	UPROPERTY(EditAnywhere, Category = "Hero")
		ABaseUnit* maze;

	UPROPERTY(EditAnywhere, Category = "Hero")
		ABaseUnit* realHero;

	UPROPERTY(EditAnywhere, Category = "BOSS")
	AActor* protal;
	UPROPERTY(EditAnywhere, Category = "BOSS")
	AProceduralWorldMapGenerator* bossWorld;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void addUnit();

	void createTown();
	void createWorldMap();
	void createPlayer();

	void createPortal();
	void createBossWorld();

	
};
