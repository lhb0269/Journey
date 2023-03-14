// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldCubeBase.h"

// Sets default values
AWorldCubeBase::AWorldCubeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldCubeBase::BeginPlay()
{
	Super::BeginPlay();

	isVisited = false;
	
}

// Called every frame
void AWorldCubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldCubeBase::initWorldCubeBase(bool visited, int32 num)
{
	isVisited = visited;
	cubeNumber = num;
}

