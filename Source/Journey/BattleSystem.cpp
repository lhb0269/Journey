// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSystem.h"

// Sets default values
ABattleSystem::ABattleSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABattleSystem::resetBattleField()
{
}

// Called when the game starts or when spawned
void ABattleSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

