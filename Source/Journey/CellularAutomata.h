// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldCubeBase.h"
#include "Camera/CameraComponent.h"
#include "CellularAutomata.generated.h"
using namespace std;

class UJourneySaveGame;

// 
USTRUCT()
// CellularAutomata로 생성한 타일 정보를 저장합니다.
struct FCAStruct
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FVector tilePos = FVector(-1, -1, -1);
	UPROPERTY()
	int32 tileType = -1;
	UPROPERTY()
	bool isVisited = false;
	UPROPERTY()
	bool isTown = false;
	UPROPERTY()
	bool isKey= false;

	UPROPERTY()
	int monsterType = -1;

	UPROPERTY()
	int monsterPower = -1;

	UPROPERTY()
	int monsterLevel = -1;

};



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

	bool chcekSaveFile();

	void RebuildNavigationMesh();

	void GenRandomkeyTown();

	void GenMapData();
	



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Tilemax = 5;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWorldCubeBase> Tile;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWorldCubeBase> Mountain;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWorldCubeBase> River;
	UPROPERTY(EditAnywhere)
		int32 Time = 2;
	UPROPERTY(EditAnywhere)
		bool isPortalExist;

	
	TArray<AWorldCubeBase*>AArray;
	vector<int32>width;

	TArray<FVector>MapPos;

	vector<vector<int32>>height;

	// tile 정보를 저장할 vector
	TArray<FCAStruct> CATileInfos;
	TArray<FCAStruct> MainTileInfos;
	// 저장 파일
	UJourneySaveGame* MySaveGame;

	
};
