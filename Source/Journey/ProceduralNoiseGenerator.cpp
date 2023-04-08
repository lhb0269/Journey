
// Fill out your copyright notice in the Description page of Project Settings.



#include "ProceduralNoiseGenerator.h"
#include "ProceduralMeshComponent.h"
#include "HeroCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProceduralNoiseGenerator::AProceduralNoiseGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	ProceduralMesh->SetupAttachment(GetRootComponent());
	IsMotel = false;
	IsShop = false;
}

// Called when the game starts or when spawned
void AProceduralNoiseGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	CreateVertices();
	CreateTriangles();

	//UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);
	if (XSize > 0 && YSize > 0)
		CellularAutomata();

	// ���� �Ϸ� �� �÷��̾� ��ġ ����
	AHeroCharacter* PlayerCharacter = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->ChangeCamera(false);
}

// Called every frame
void AProceduralNoiseGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProceduralNoiseGenerator::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	for (auto It = AAray.CreateIterator(); It; It++)
	{
		(*It)->Destroy();
	}
	AAray.Empty();
	RegisterAllComponents();

	Vertices.Reset();
	Triangles.Reset();
	UV0.Reset();

	//CreateVertices();
	//CreateTriangles();

	////UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

	//ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	//ProceduralMesh->SetMaterial(0, Material);

	//if (XSize > 0 && YSize > 0)
	//	CellularAutomata();
}
void AProceduralNoiseGenerator::CreateVertices()
{
	for (int x = 0; x <= XSize; ++x) {
		for (int y = 0; y <= YSize; ++y) {
			float z = FMath::PerlinNoise2D(FVector2D(x * NoiseScale + 0.1, y * NoiseScale + 0.1)) * ZMultiplier;
			Vertices.Add(FVector(x * Scale, y * Scale, z));
			UV0.Add(FVector2D(x * UVScale, y * UVScale));
			if (x < XSize && y < YSize)
				Zvalue.Add(z);
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


void AProceduralNoiseGenerator::CellularAutomata()
{
	UWorld* world = GetWorld();
	bool Original = false;
	width.clear();
	height.clear();
	float wall = 0;
	int gap = 225;
	for (int i = 0; i < XSize; ++i) {
		for (int j = 0; j < YSize; ++j) {
			width.push_back(FMath::RandRange(0, 1));
		}
		height.push_back(width);
		width.clear();
	}
	//Check Forest
	int32 tilecount = 0;
	for (int num = 0; num < Tilemax; ++num) {
		for (int i = 0; i < XSize; ++i) {
			for (int j = 0; j < YSize; ++j) {
				int32 count = 0;
				if (height[i][j] == 1) count += 1;
				if (i + 1 < XSize && i - 1 >= 0 && j + 1 < YSize && j - 1 >= 0) {
					if (height[i - 1][j - 1] == 1)  count += 1;
					if (height[i - 1][j] == 1)  count += 1;
					if (height[i - 1][j + 1] == 1)  count += 1;
					if (height[i][j - 1] == 1)  count += 1;
					if (height[i][j + 1] == 1)  count += 1;
					if (height[i + 1][j - 1] == 1)  count += 1;
					if (height[i + 1][j] == 1)  count += 1;
					if (height[i + 1][j + 1] == 1)  count += 1;
				}
				else {
					count = 6;
				}
				if (count > 5) {
					height[i][j] = 1;

				}
				//else if (count == 3)height[i][j] = 2;
				else if (count < 5) {
					height[i][j] = 0;
				}
			}
		}
	}
	//Check Village
	for (int i = 0; i < XSize; ++i) {
		for (int j = 0; j < YSize; ++j) {
			int32 count = 0;
			if (height[i][j] == 0) count += 1;
			for (int k = 1; k <= 4; ++k) {
				if (i + k < XSize && i - k >= 0 && j + k < YSize && j - k >= 0) {
					if (height[i - k][j - k] == 0)  count += 1;
					if (height[i - k][j] == 0)  count += 1;
					if (height[i - k][j + k] == 0)  count += 1;
					if (height[i][j - k] == 0)  count += 1;
					if (height[i][j + k] == 0)  count += 1;
					if (height[i + k][j - k] == 0)  count += 1;
					if (height[i + k][j] == 0)  count += 1;
					if (height[i + k][j + k] == 0)  count += 1;
				}
			}
			if (count >= 33) {
				for (int k = 1; k <= 4; ++k) {
					height[i - k][j - k] = 4;
					height[i - k][j] = 4;
					height[i - k][j + k] = 4;
					height[i][j - k] = 4;
					height[i][j + k] = 4;
					height[i + k][j - k] = 4;
					height[i + k][j] = 4;
					height[i + k][j + k] = 4;
				}
				height[i][j] = 3;
			}
		}
	}
	while(!IsMotel)
	{
		int32 x = FMath::RandRange(12,37);
		int32 y = FMath::RandRange(12,37);
		if(height[x][y] == 3)
		{
			height[x][y] = 5;
			IsMotel = true;
			UE_LOG(LogTemp,Warning,TEXT("%d %d"),x,y);
		}
	}
	while(!IsShop)
	{
		int32 x = FMath::RandRange(12,37);
		int32 y = FMath::RandRange(12,37);
		if(height[x][y] == 3)
		{
			height[x][y] = 6;
			IsShop = true;
			UE_LOG(LogTemp,Warning,TEXT("%d %d"),x,y);
		}
	}
	//
	if (Tree != nullptr && House != nullptr && motel != nullptr && Shop != nullptr) {
		for (int i = XSize - 1; i >= 0; --i) {
			for (int j = YSize - 1; j >= 0; --j) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector SpawnLocation;
				SpawnLocation.X = i * 100 + GetActorLocation().X;
				SpawnLocation.Y = j * 100 + GetActorLocation().Y;
				SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z - 10;
				rotator.Roll = 0;
				if (height[i][j] == 1) {
					rotator.Yaw = FMath::FRandRange(-90.0f, 90.0f);
					AActor* Tile1 = world->SpawnActor<AActor>(Tree, SpawnLocation, rotator, SpawnParams);
					Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					AAray.Add(Tile1);
				}
				else if (height[i][j] == 3) {
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					AActor* HouseTile = world->SpawnActor<AActor>(House, SpawnLocation, rotator, SpawnParams);
					//HouseTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					AAray.Add(HouseTile);
				}
				else if (height[i][j] == 5) { //여관생성
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					//SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z;
					AActor* MotelTile = world->SpawnActor<AActor>(motel, SpawnLocation, rotator, SpawnParams);
					AAray.Add(MotelTile);
				}
				else if (height[i][j] == 6) { //상점생성
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					AActor* Shoptile = world->SpawnActor<AActor>(Shop, SpawnLocation, rotator, SpawnParams);
					AAray.Add(Shoptile);
				}
			}
		}
	}
}

