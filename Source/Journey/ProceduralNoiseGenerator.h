// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralNoiseGenerator.generated.h"

using namespace std;
class UProceduralMeshComponent;
class UMaterialInterface;
UCLASS()
class JOURNEY_API AProceduralNoiseGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralNoiseGenerator();
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int32 XSize = 0;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int32 YSize = 0;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float ZMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float NoiseScale = 1.0f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float Scale = 0;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Tilemax = 5;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> Tree;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor>House;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor>Shop;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor>motel;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor>Tower;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor>Fontain;

	UPROPERTY(EditAnywhere)
    	
	TSubclassOf<class AActor>NPC_Child;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor>NPC_Guard;
	TArray<AActor*>AAray;
	vector<int32>width;
	vector<vector<int32>>height;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& transform)override;
	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UProceduralMeshComponent* ProceduralMesh;
	TArray<FVector>Vertices;
	TArray<int>Triangles;
	TArray<float>Zvalue;
	TArray<FVector2D>UV0;
	
	bool IsShop;
	bool IsMotel;
	
	void CreateVertices();
	void CreateTriangles();
	void CellularAutomata();
};
