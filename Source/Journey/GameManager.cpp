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

void AGameManager::addUnit()
{
}

void AGameManager::createTown()
{

	FTimerHandle TreesTimerHandle[9];
	FTimerHandle HousesTimerHandle[9];
	FTimerHandle SpecialTimerHandle[9];
	FTimerHandle CastleTimerHandle[9];
	float count = 0.f;
	for (int i = 0; i < 9; i++)
	{
		float time;
		time = 6.5f + (count / 3.f);
		GetWorldTimerManager().SetTimer(TreesTimerHandle[i], townMap[i], &AProceduralNoiseGenerator::CreateTrees, time, false);

		time = 7.5f + (count / 3.f);
		GetWorldTimerManager().SetTimer(HousesTimerHandle[i], townMap[i], &AProceduralNoiseGenerator::CreateHouses, time, false);
		
		time = 8.5f + (count / 3.f);
		GetWorldTimerManager().SetTimer(SpecialTimerHandle[i], townMap[i], &AProceduralNoiseGenerator::CreateSpecial, time, false);

		time = 9.5f + (count / 3.f);
		GetWorldTimerManager().SetTimer(CastleTimerHandle[i], townMap[i], &AProceduralNoiseGenerator::CreateCastle, time, false);
		count += 3.f;
	}
}

void AGameManager::createWorldMap()
{
	
	FTimerHandle TerrainTimerHandle;
	FTimerHandle TownsTimerHandle;
	FTimerHandle MonstersTimerHandle;
	FTimerHandle DecoTimerHandle;

	GetWorldTimerManager().SetTimer(TerrainTimerHandle, worldMap, &AProceduralWorldMapGenerator::GenerateTerrain, 1.0f, false);


	GetWorldTimerManager().SetTimer(TownsTimerHandle, worldMap, &AProceduralWorldMapGenerator::GenerateTowns, 2.0f, false);


	GetWorldTimerManager().SetTimer(MonstersTimerHandle, worldMap, &AProceduralWorldMapGenerator::GenerateMonsters, 3.0f, false);

	GetWorldTimerManager().SetTimer(DecoTimerHandle, worldMap, &AProceduralWorldMapGenerator::GenerateDeco, 4.0f, false);
	/*worldMap->GenerateTerrain();
	worldMap->GenerateTowns();
	worldMap->GenerateMonsters();*/
}

void AGameManager::createPlayer()
{

}

void AGameManager::createPortal()
{
	FMovieSceneSequencePlaybackSettings Settings;
	ALevelSequenceActor* OutActor;
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), BossSequence, Settings, OutActor);

	SequencePlayer->Play();
}

void AGameManager::createBossWorld()
{
}

void AGameManager::endingScene()
{
	FMovieSceneSequencePlaybackSettings Settings;
	ALevelSequenceActor* OutActor;
	ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), EndingSequence, Settings, OutActor);

	SequencePlayer->Play();
}

float AGameManager::getHeroPower()
{
	return realHero->power;
}

float AGameManager::getHeroArmor()
{
	return realHero->Armour;
}

float AGameManager::getTankerPower()
{
	return hero->power;
}

float AGameManager::getTankerArmor()
{
	return hero->Armour;
}

float AGameManager::getArcherPower()
{
	return archer->power;
}

float AGameManager::getArcherArmor()
{
	return archer->Armour;
}

float AGameManager::getMagePower()
{
	return maze->power;
}

float AGameManager::getMageArmor()
{
	return maze->Armour;
}
