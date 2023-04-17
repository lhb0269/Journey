// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldCubeBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWorldCubeBase::AWorldCubeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	isVisited = false;
	isTown = false;
	isKey = false;
	monsterPower=10;
	monsterLevel=5;
	monsterType=1;
}

// Called when the game starts or when spawned
void AWorldCubeBase::BeginPlay()
{
	Super::BeginPlay();





	
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

void AWorldCubeBase::resetCubeState()
{


	//if (isTown)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("isTown: %d"), cubeNumber);
	//	Town->SetVisibility(true);
	//	Battle->SetVisibility(false);
	//}

	//if (isVisited)
	//{
	//	Battle->SetVisibility(false);
	//	Key->SetVisibility(false);
	//}
	//else if(!isVisited)
	//{	
	//	if (isKey)
	//	{
	//		Key->SetVisibility(true);
	//		UE_LOG(LogTemp, Warning, TEXT("isKey: %d"), cubeNumber);
	//	}
	//		
	//}



}

