// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellularAutomata.generated.h"

UCLASS()
class JOURNEY_API ACellularAutomata : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellularAutomata();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform)override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Tilemax = 5;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> Tile;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> Tile2;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> River;
	UPROPERTY(EditAnywhere)
		int32 Time = 2;
};
