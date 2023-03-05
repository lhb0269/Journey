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
		int32 XSize = 100;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int32 YSize = 100;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float ZMultiplier = 100.0f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float NoiseScale = 0.1f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float Scale = 100;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Tilemax = 5;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> Tree;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor>House;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor>Plaza;
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

	bool CreateShop = false;
	bool CreateHPHouse = false;

	void CreateVertices();
	void CreateTriangles();
	void CellularAutomata();
};
