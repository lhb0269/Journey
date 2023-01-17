// Fill out your copyright notice in the Description page of Project Settings.


#include "CellularAutomata.h"
#include<vector>
#include "Components/ChildActorComponent.h"
using namespace std;
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
	
}

// Called every frame
void ACellularAutomata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACellularAutomata::OnConstruction(const FTransform& Transform)
{
	vector<int32>width;
	vector<vector<int32>>height;
	UWorld* world = GetWorld();
	bool Original = false;
	width.clear();
	height.clear();
	float wall = 0;
	for (int i = 0; i < Tilemax; ++i) {
		for (int j = 0; j < Tilemax; ++j) {
			width.push_back(FMath::RandRange(0, 1));
			UE_LOG(LogTemp, Warning, TEXT("[%d][%d]'s num is %d"), i, j, width[j]);
			if (width[j] == 1)
				wall++;
		}
		height.push_back(width);
		width.clear();
	}
	Original = true;
	if ((Tilemax * Tilemax) * (45.0f / 100.0f) <= wall) {
		UE_LOG(LogTemp, Warning, TEXT("Complete"));
		Original = true;
	}
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
				count = 5;
			}
			if (count >= 5)height[i][j] = 1;
			else if (count == 3)height[i][j] = 2;
			else height[i][j] = 0;
			UE_LOG(LogTemp, Warning, TEXT("Celluar [%d][%d]'s num is %d"), i, j, width[j]);
		}
	}
	if (Tile != nullptr && Tile2 != nullptr && River != nullptr) {
		for (int time = 0; time < Time; ++time) {
			for (int i = 0; i < Tilemax; ++i) {
				for (int j = 0; j < Tilemax; ++j) {
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					FRotator rotator;
					FVector SpawnLocation;
					SpawnLocation.Y = i * 100 + GetActorLocation().Y;
					SpawnLocation.X = j * 100 + GetActorLocation().X;
					SpawnLocation.Z = GetActorLocation().Z;
					if (height[i][j] == 0) {
						AActor* Tile1 = world->SpawnActor<AActor>(Tile, SpawnLocation, rotator, SpawnParams);
						Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					}
					else if (height[i][j] == 1) {
						AActor* Mountain = world->SpawnActor<AActor>(Tile2, SpawnLocation, rotator, SpawnParams);
						Mountain->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
						FVector Scale;
						Scale.X = 1.0f; Scale.Y = 1.0f; Scale.Z = FMath::FRandRange(1.0f, 50.0f);
						Mountain->SetActorScale3D(Scale);
					}
					else if (height[i][j] == 2) {
						AActor* RiverTile = world->SpawnActor<AActor>(River, SpawnLocation, rotator, SpawnParams);
						RiverTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					}
				}
			}
		}
	}
}

