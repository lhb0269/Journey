// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldCubeBase.h"
#include<random>
#include<algorithm>
#include<vector>
#include "ProceduralWorldMapGenerator.generated.h"


USTRUCT()
// CellularAutomata�� ������ Ÿ�� ������ �����մϴ�.
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

    UPROPERTY()
        bool isPossible = true;

    UPROPERTY()
        bool isTown = false;

    UPROPERTY()
        bool isWater = false;
    UPROPERTY()
        bool isPortal;
    UPROPERTY()
        FVector location;

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
    TArray<TSubclassOf<class AActor>> GrassDeco;
    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<class AActor>> DesertDeco;
    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<class AActor>> SnowDeco;
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
    TSubclassOf<class AActor> SnowObj;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> DesertObj;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> GrassObj;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> Portal;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AWorldCubeBase> GrassGolemBase;
    UPROPERTY(EditAnywhere)
        TSubclassOf<class AWorldCubeBase> DesertGolemBase;
    UPROPERTY(EditAnywhere)
        TSubclassOf<class AWorldCubeBase> SnowGolemBase;
    UPROPERTY(EditAnywhere)
       TSubclassOf<class AWorldCubeBase> MidBossBase;

    TArray<FVector>MapPos;
    std::vector<FString>townname;
    int32 townnamecnt;
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
    float objectFrequency = 0.1f;
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
    UFUNCTION(BlueprintCallable, Category = "Create")
    void GenerateDeco();
    int InterpolateTileType(int tileType1, int tileType2, int tileType3, float t, float u);
    int LinearInterpolation(int value1, int value2, float t);
    void SetSurroundingTilesAsMountain(int i, int j);

    float terrainTime;
    float TownTime;
    float MonsterTime;
    float DecoTime;
    
    void createBossPortal();

    bool isPortal;
};
