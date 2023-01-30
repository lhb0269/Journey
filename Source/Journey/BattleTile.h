// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleTile.generated.h"

UCLASS()
class JOURNEY_API ABattleTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform)override;

	UPROPERTY(EditAnywhere)
	int32 heightNum = 0;

	UPROPERTY(EditAnywhere)
	int32 widthNum = 0;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Tile;



};
