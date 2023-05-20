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
	UPROPERTY(EditAnywhere)
	AHeroCharacter* heroCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void createTown();
	void createWorldMap();
	void createPlayer();
};
