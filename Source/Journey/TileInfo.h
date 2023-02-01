// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "TileInfo.generated.h"

UCLASS()
class JOURNEY_API ATileInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileInfo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "TileMesh")
	int32 heightNum;

	UPROPERTY(EditAnywhere, Category = "TileMesh")
		UStaticMesh* TileMesh;
	UPROPERTY(EditAnywhere, Category = "TileMesh")
		UStaticMesh* AreaMesh;

};
