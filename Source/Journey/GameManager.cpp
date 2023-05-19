// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	worldMap = Cast<AProceduralWorldMapGenerator>(UGameplayStatics::GetActorOfClass(GetWorld(), AProceduralWorldMapGenerator::StaticClass()));

	FMovieSceneSequencePlaybackSettings Settings;
	ALevelSequenceActor* OutActor;
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), IntroSequence, Settings, OutActor);

	SequencePlayer->Play();



	createWorldMap();
	createTown();
	createPlayer();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::createTown()
{

}

void AGameManager::createWorldMap()
{
	
	FTimerHandle TerrainTimerHandle;
	FTimerHandle TownsTimerHandle;
	FTimerHandle MonstersTimerHandle;


	GetWorldTimerManager().SetTimer(TerrainTimerHandle, worldMap, &AProceduralWorldMapGenerator::GenerateTerrain, 1.0f, false);


	GetWorldTimerManager().SetTimer(TownsTimerHandle, worldMap, &AProceduralWorldMapGenerator::GenerateTowns, 2.0f, false);


	GetWorldTimerManager().SetTimer(MonstersTimerHandle, worldMap, &AProceduralWorldMapGenerator::GenerateMonsters, 3.0f, false);

	/*worldMap->GenerateTerrain();
	worldMap->GenerateTowns();
	worldMap->GenerateMonsters();*/
}

void AGameManager::createPlayer()
{

}
