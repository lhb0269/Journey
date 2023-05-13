// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldCubeBase.h"
#include "GameFramework/Actor.h"
#include "ProceduralWorldMapGenerator.generated.h"

UCLASS()
class JOURNEY_API AProceduralWorldMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	

	AProceduralWorldMapGenerator();

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> Land;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> Sea;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> Town;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AWorldCubeBase> GolemBase;

    UPROPERTY(EditAnywhere)
    int width = 50;
    UPROPERTY(EditAnywhere)
    int height = 50;
    UPROPERTY(EditAnywhere)
    float seaLevel = 0.02f;
    UPROPERTY(EditAnywhere)
    float townFrequency = 0.01f;
    UPROPERTY(EditAnywhere)
    float monsterFrequency = 0.01f;
    UPROPERTY(EditAnywhere)
    float heightVolume = 100;


    int64 Seed;
    TArray<TArray<float>> heightMap;
public:

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    float Noise(int x, int y);
    float SmoothNoise(int x, int y);
    float InterpolatedNoise(float x, float y);
    float Interpolate(float a, float b, float x);

    void GenerateTerrain();
    void GenerateTowns();
    void GenerateMonsters();
};
