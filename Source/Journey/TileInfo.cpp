// Fill out your copyright notice in the Description page of Project Settings.


#include "TileInfo.h"

// Sets default values
ATileInfo::ATileInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UWorld* world = GetWorld();

	//FRotator rotator;
	//FActorSpawnParameters SpawnParams;
	//SpawnParams.Owner = this;

	//UStaticMeshComponent* Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor_Mesh"));
	//TileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	//TileMesh->SetStaticMesh(TileMesh);
	//TileMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//TileMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.5f));

	//UStaticMeshComponent* Area = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor_Mesh"));
	//Area->AttachToComponent(Tile, FAttachmentTransformRules::KeepWorldTransform);
	//Area->SetStaticMesh(AreaMesh);
	//Area->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//Area->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));

}

// Called when the game starts or when spawned
void ATileInfo::BeginPlay()
{
	Super::BeginPlay();
	
	
	//AreaMesh->AttachToActor(TileMesh, FAttachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void ATileInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

