// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldCubeBase.h"
#include "ProceduralWorldMapGenerator.generated.h"


USTRUCT()
// CellularAutomata로 생성한 타일 정보를 저장합니다.
struct FWTile
{
    GENERATED_BODY()
public:
    UPROPERTY()
        float heightVal = -1;


    // tileType
    // 0 = grass , 1 = desrt, 2 = snow, 3 = mountain
    UPROPERTY()
        int32 tileType = -1;
};

UCLASS()
class JOURNEY_API AProceduralWorldMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	

	AProceduralWorldMapGenerator();

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> GrassLand;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> DesertLand;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> MountainLand;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> SnowLand;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> Sea;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AWorldCubeBase> SnowTown;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AWorldCubeBase> DesertTown;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AWorldCubeBase> GrassTown;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class AWorldCubeBase> GolemBase;

    TArray<FVector>MapPos;

    FTimerHandle SpawnTimerHandle;



    UPROPERTY(EditAnywhere)
    int width = 50;
    UPROPERTY(EditAnywhere)
    int height = 50;
    UPROPERTY(EditAnywhere)
    float seaLevel = 0.02f;
    UPROPERTY(EditAnywhere)
    float townFrequency = 0.01f;
    UPROPERTY(EditAnywhere)
    float monsterFrequency = 0.1f;
    UPROPERTY(EditAnywhere)
    float heightVolume = 100;

    bool isPlayerMove;
    FVector playerSpawnPos;

    int64 Seed;
    TArray<TArray<FWTile>> heightMap;
public:

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    float Noise(int x, int y);
    float SmoothNoise(int x, int y);
    float InterpolatedNoise(float x, float y);
    float Interpolate(float a, float b, float x);

    UFUNCTION(BlueprintCallable, Category = "Create")
    void GenerateTerrain();
    UFUNCTION(BlueprintCallable, Category = "Create")
    void GenerateTowns();
    UFUNCTION(BlueprintCallable, Category = "Create")
    void GenerateMonsters();

    float terrainTime;
    float TownTime;
    float MonsterTime;
};
