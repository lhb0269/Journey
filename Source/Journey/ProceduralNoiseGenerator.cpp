// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralNoiseGenerator.h"
#include "ProceduralMeshComponent.h"
// Sets default values
AProceduralNoiseGenerator::AProceduralNoiseGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	ProceduralMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AProceduralNoiseGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProceduralNoiseGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProceduralNoiseGenerator::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	Vertices.Reset();
	Triangles.Reset();
	UV0.Reset();

	CreateVertices();
	CreateTriangles();

	//UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);
}
void AProceduralNoiseGenerator::CreateVertices()
{
	for (int x = 0; x <= XSize; ++x) {
		for (int y = 0; y <= YSize; ++y) {
			float z = FMath::PerlinNoise2D(FVector2D(x * NoiseScale + 0.1, y * NoiseScale + 0.1)) * ZMultiplier;
			Vertices.Add(FVector(x * Scale, y * Scale, z));
			UV0.Add(FVector2D(x * UVScale, y * UVScale));
		}
	}
}

void AProceduralNoiseGenerator::CreateTriangles()
{
	int Vertex = 0;
	for (int x = 0; x < XSize; ++x) {
		for (int y = 0; y < YSize; ++y) {
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);
			++Vertex;
		}
		++Vertex;
	}
}


