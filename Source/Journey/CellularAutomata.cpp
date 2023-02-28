// Fill out your copyright notice in the Description page of Project Settings.


#include "CellularAutomata.h"

#include "Components/ChildActorComponent.h"

// Sets default values
ACellularAutomata::ACellularAutomata()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellularAutomata::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	bool Original = false;
	width.clear();
	height.clear();
	float wall = 0;
	//int gap = 225;
	int gap = 200;
	for (int i = 0; i < Tilemax; ++i) {
		for (int j = 0; j < Tilemax; ++j) {
			width.push_back(FMath::RandRange(0, 1));
			if (width[j] == 1)
				wall++;
		}
		height.push_back(width);
		width.clear();
	}
	if (Tilemax >= 8) {
		for (int i = 0; i < Tilemax; ++i) {
			for (int j = 0; j < Tilemax; ++j) {
				int32 count = 0;
				if (height[i][j] == 1) count += 1;
				if (i + 1 < Tilemax && i - 1 >= 0 && j + 1 < Tilemax && j - 1 >= 0) {
					if (height[i - 1][j - 1] == 1)  count += 1;
					if (height[i - 1][j] == 1)  count += 1;
					if (height[i - 1][j + 1] == 1)  count += 1;
					if (height[i][j - 1] == 1)  count += 1;
					if (height[i][j + 1] == 1)  count += 1;
					if (height[i + 1][j - 1] == 1)  count += 1;
					if (height[i + 1][j] == 1)  count += 1;
					if (height[i + 1][j + 1] == 1)  count += 1;
				}
				else {
					count = 6;
				}
				if (count >= 6)height[i][j] = 1;
				else if (count == 3)height[i][j] = 2;
				else height[i][j] = 0;
			}
		}
	}
	else
	{
		for (int i = 0; i < Tilemax; ++i) {
			for (int j = 0; j < Tilemax; ++j) {
				int32 count = 0;
				if (height[i][j] == 0) count += 1;
				if (i + 1 < Tilemax && i - 1 >= 0 && j + 1 < Tilemax && j - 1 >= 0) {
					if (height[i - 1][j - 1] == 0)  count += 1;
					if (height[i - 1][j] == 0)  count += 1;
					if (height[i - 1][j + 1] == 0)  count += 1;
					if (height[i][j - 1] == 0)  count += 1;
					if (height[i][j + 1] == 0)  count += 1;
					if (height[i + 1][j - 1] == 0)  count += 1;
					if (height[i + 1][j] == 0)  count += 1;
					if (height[i + 1][j + 1] == 0)  count += 1;
				}
				else {
					count = 6;
				}
				if (count >= 6)height[i][j] = 0;
				else if (count == 3)height[i][j] = 2;
				else height[i][j] = 1;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), height.size());
	if (Tile != nullptr && Mountain != nullptr && River != nullptr) {
		for (int i = 0; i < Tilemax; ++i) {
			for (int j = 0; j < Tilemax; ++j) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector SpawnLocation;
				SpawnLocation.Y = i * 450 + GetActorLocation().Y;
				if (i % 2 == 0)
					SpawnLocation.X = j * 450 + GetActorLocation().X;
				else
					SpawnLocation.X = j * 450 + GetActorLocation().X + gap;
				SpawnLocation.Z = GetActorLocation().Z;
				if (height[i][j] == 0) {
					AActor* Tile1 = world->SpawnActor<AActor>(Tile, SpawnLocation, rotator, SpawnParams);
					Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					AArray.Add(Tile1);
				}
				else if (height[i][j] == 1) {//Mountain
					AActor* MountainTile = world->SpawnActor<AActor>(Mountain, SpawnLocation, rotator, SpawnParams);
					MountainTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					//FVector Scale;
					//Scale.X = 1.0f; Scale.Y = 1.0f; Scale.Z = FMath::FRandRange(1.0f, 50.0f);
					//MountainTile->SetActorScale3D(Scale);
					AArray.Add(MountainTile);
				}
				else if (height[i][j] == 2) {//River
					AActor* RiverTile = world->SpawnActor<AActor>(River, SpawnLocation, rotator, SpawnParams);
					RiverTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					AArray.Add(RiverTile);
				}
			}
		}
	}
}

// Called every frame
void ACellularAutomata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACellularAutomata::OnConstruction(const FTransform& Transform)
{
	for (auto It = AArray.CreateIterator(); It; It++)
	{
		(*It)->Destroy();
	}
	AArray.Empty();
	RegisterAllComponents();

}

