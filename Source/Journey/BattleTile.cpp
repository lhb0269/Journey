// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTile.h"
#include <vector>

// Sets default values
ABattleTile::ABattleTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleTile::OnConstruction(const FTransform& Transform)
{
	int32 w = widthNum;
	int32 h = heightNum;
	UWorld* world = GetWorld();

	TArray<TArray<int32>> tileArray;


	FVector SpawnLocation;
	FRotator rotator;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnLocation.Z = GetActorLocation().Z;
	if (Tile != nullptr)
	{
		for (int i = 0; i < heightNum; i++)
		{
			for (int j = 0; j < widthNum; j++)
			{
				SpawnLocation.X = j * 1000 + GetActorLocation().X;
				SpawnLocation.Y = i * 1000 + GetActorLocation().X;

				AActor* Tile1 = world->SpawnActor<AActor>(Tile, SpawnLocation, rotator, SpawnParams);
				Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}


}

