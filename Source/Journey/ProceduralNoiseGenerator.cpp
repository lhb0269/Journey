
// Fill out your copyright notice in the Description page of Project Settings.



#include "ProceduralNoiseGenerator.h"
#include "ProceduralMeshComponent.h"
#include "HeroCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProceduralNoiseGenerator::AProceduralNoiseGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->SetupAttachment(GetRootComponent());

	MinimapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MinimapArm"));
	MinimapArm->SetupAttachment(ProceduralMesh);

	// Minimap = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Minimap"));
	// Minimap->SetupAttachment(MinimapArm);
	// Minimap->SetActive(false);
	IsMotel = false;
	IsShop = false;

	castlx = FMath::RandRange(1,4);
	castly = FMath::RandRange(1,4);
	
}

// Called when the game starts or when spawned
void AProceduralNoiseGenerator::BeginPlay()
{
	Super::BeginPlay();
	switch(Objective)
	{
	case 1:
		XSize = FMath::RandRange(25,50);
		YSize = FMath::RandRange(25,50);
		break;
	case 2:
		XSize = FMath::RandRange(75,100);
		YSize = FMath::RandRange(75,100);
		break;
	case 3:
		XSize = FMath::RandRange(100,125);
		YSize = FMath::RandRange(100,125);
		break;
	}
	CreateVertices();
	CreateTriangles();

	TreeTime = 0.0f;
	TownTime = 0.0f;

	MinimapArm->SetRelativeLocation(FVector(XSize/2 * 100, YSize/2 * 100,500));
	UE_LOG(LogTemp,Warning,TEXT("%d %d"),XSize/2*100,YSize/2*100);
	//UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);
	if (XSize > 0 && YSize > 0)
		CellularAutomata();

	// ���� �Ϸ� �� �÷��̾� ��ġ ����
	AHeroCharacter* PlayerCharacter = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->ChangeCamera(false);

	switch (Objective)
	{
	case 1:
		NPCCount = 2;
		break;
	case 2:
		NPCCount = 5;
		break;
	case 3:
		NPCCount = 10;
		break;
	}
}

// Called every frame
void AProceduralNoiseGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProceduralNoiseGenerator::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

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
				Zvalue_width.push_back(z);
		}
		Zvalue.push_back(Zvalue_width);
		Zvalue_width.clear();
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
	if(Objective>=1)//중간맵 이상일때
	{
		//Check Forest 1st
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
					else if(i>=XSize/2&&j>=YSize/2)
					{
						height[i][j] = 0;
					}
					if(i>=(int)(XSize/5*(castlx-1)) && i<=(int)(XSize/5*(castlx+1)) && j>=(int)(XSize/5*(castly-1)) && j<=(int)(XSize/5*(castly+1)))
					{
						height[i][j] = 4;
					}
				}
			}
		}
	}
	if (Objective == 1) //작은맵
	{
		int max_cnt = 5;
		int cnt = 0;
		int32 rad = 8;
		int32 num = FMath::RandRange(0,1);
		if(num==0)
		{
			if(height[XSize/2][YSize/2 + rad] == 0)
				height[XSize/2][YSize/2 + rad] = 9;
		}
		else
		{
			if(height[XSize/2][YSize/2 + rad] == 0)
				height[XSize/2][YSize/2 + rad] = 10;
		}
		if(height[XSize/2 + rad][YSize/2 + rad] == 0)
			height[XSize/2 + rad][YSize/2 + rad] = 3;
		if(height[XSize/2+rad][YSize/2] == 0)
			height[XSize/2+rad][YSize/2] = 3;
		if(height[XSize/2+rad][YSize/2 - rad] == 0)
			height[XSize/2+rad][YSize/2 - rad] = 3;
		if(height[XSize/2][YSize/2 - rad] == 0)
			height[XSize/2][YSize/2 - rad] = 3;
		if(height[XSize/2 - rad][YSize/2 - rad] == 0)
			height[XSize/2 - rad][YSize/2 - rad] = 3;
		if(height[XSize/2-rad][YSize/2] == 0)
			height[XSize/2-rad][YSize/2] = 3;
		if(height[XSize/2-rad][YSize/2 + rad] == 0)
			height[XSize/2-rad][YSize/2 + rad] = 3;
		
	}
	else if (Objective == 2)//중간
	{
		height[XSize/5 * castlx][YSize/5 * castly] = 8;
		int32 rand = FMath::RandRange(0,1);
		switch(rand)
		{
		case 0:
			IsShop=true;
			break;
		case 1:
			IsMotel=true;
			break;
		}
		//Check Village 2nd
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
					if(i<XSize/2 && j<YSize/2)//더미 상점
						{
						if(!IsShop)
						{
							height[i][j] = 9;
							IsShop = true;
						}
						else if(IsShop)
							height[i][j] = 6;
						for (int k = 1; k <= 8; ++k)
						{
							if(i-k >0 && j-k >0 && i+k <XSize && j+k < YSize){
								height[i - k][j - k] = 4;
								height[i - k][j] = 4;
								height[i - k][j + k] = 4;
								height[i][j - k] = 4;
								height[i][j + k] = 4;
								height[i + k][j - k] = 4;
								height[i + k][j] = 4;
								height[i + k][j + k] = 4;
							}
						}
						}
					else if(i>=XSize/2 && j<YSize/2)//더미여관
						{
						if(!IsMotel)
						{
							height[i][j]=10;
							IsMotel = true;
						}
						else if(IsMotel)
							height[i][j] = 5;
						for (int k = 1; k <= 8; ++k)
						{
							if(i-k >0 && j-k >0 && i+k <XSize && j+k < YSize){
								height[i - k][j - k] = 4;
								height[i - k][j] = 4;
								height[i - k][j + k] = 4;
								height[i][j - k] = 4;
								height[i][j + k] = 4;
								height[i + k][j - k] = 4;
								height[i + k][j] = 4;
								height[i + k][j + k] = 4;
							}
						}
						}
					else if(i<XSize/2 && j>=YSize/2)
					{
						height[i][j] = 3;
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
					}
					else if(i>=XSize/2 && j>=YSize/2)
					{
						height[i][j] = 3;
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
					}
				}
			}
		}
	}
	else if(Objective == 3)//제일 큰
	{
		
		//성 생성
		
		height[XSize/5 * castlx][YSize/5 * castly] = 8;
		//Check Village 2nd
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
					if(i<XSize/2 && j<YSize/2)//더미 상점
						{
						if(!IsShop)
						{
							height[i][j] = 9;
							IsShop = true;
						}
						else if(IsShop)
							height[i][j] = 6;
						for (int k = 1; k <= 8; ++k)
						{
							if(i-k >0 && j-k >0 && i+k <XSize && j+k < YSize){
								height[i - k][j - k] = 4;
								height[i - k][j] = 4;
								height[i - k][j + k] = 4;
								height[i][j - k] = 4;
								height[i][j + k] = 4;
								height[i + k][j - k] = 4;
								height[i + k][j] = 4;
								height[i + k][j + k] = 4;
							}
						}
						}
					else if(i>=XSize/2 && j<YSize/2)//더미여관
						{
						if(!IsMotel)
						{
							height[i][j]=10;
							IsMotel = true;
						}
						else if(IsMotel)
							height[i][j] = 5;
						for (int k = 1; k <= 8; ++k)
						{
							if(i-k >0 && j-k >0 && i+k <XSize && j+k < YSize){
								height[i - k][j - k] = 4;
								height[i - k][j] = 4;
								height[i - k][j + k] = 4;
								height[i][j - k] = 4;
								height[i][j + k] = 4;
								height[i + k][j - k] = 4;
								height[i + k][j] = 4;
								height[i + k][j + k] = 4;
							}
						}
						}
					else if(i<XSize/2 && j>=YSize/2)
					{
						if(!IsSmith)
						{
							height[i][j] = 13;
							IsSmith = true;
						}
						else
						{
							height[i][j] = 3;
						}
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
					}
					else if(i>=XSize/2 && j>=YSize/2)
					{
						height[i][j] = 3;
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
					}
					if(i>=(int)(XSize/5*(castlx-1)) && i<=(int)(XSize/5*(castlx+1)) && j>=(int)(XSize/5*(castly-1)) && j<=(int)(XSize/5*(castly+1)))
					{
						height[i][j] = 4;
					}
				}
			}
		}
	}
	height[XSize/2][YSize/2] = 12; //포탈
}

void AProceduralNoiseGenerator::CreateHouses()
{
	TownTime = 0;
	UWorld* world = GetWorld();
	if (Tree != nullptr && House != nullptr && motel != nullptr && Shop != nullptr && Tower != nullptr) {
		int32 cnt = 0;
		for (int i = XSize - 1; i >= 0; --i) {
			for (int j = YSize - 1; j >= 0; --j) {
				TownTime += 0.0005f;
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector SpawnLocation;
				SpawnLocation.X = i * 100 + GetActorLocation().X;
				SpawnLocation.Y = j * 100 + GetActorLocation().Y;
				//SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z - 10;
				//SpawnLocation.Z = GetActorLocation().Z - 10;
				SpawnLocation.Z = Zvalue[i][j];
				if(Objective == 1)
				{
					if (height[i][j] == 3)
					{
						rotator.Pitch=0;
						rotator.Roll = 0;
						rotator.Yaw = 90 * FMath::RandRange(0, 3);
						FTimerDelegate TimerDelegate;
						AActor* HouseTile;
						TimerDelegate.BindLambda([=, &HouseTile]() {
							HouseTile = GetWorld()->SpawnActor<AActor>(House, SpawnLocation, rotator, SpawnParams);
						AAray.Add(HouseTile);
							});
						FTimerHandle TimerHandle;
						GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);
					}
				}
				if(Objective >=2)
				{
					rotator.Pitch=0;
					rotator.Roll = 0;
					if (height[i][j] == 3) {
						rotator.Yaw = 90 * FMath::RandRange(0, 3);
						int32 num = FMath::RandRange(0, 1);
						switch (num)
						{
						case 0:
							{
								FTimerDelegate TimerDelegate;
								AActor* HouseTile;
								TimerDelegate.BindLambda([=, &HouseTile]() {
									HouseTile = GetWorld()->SpawnActor<AActor>(House, SpawnLocation, rotator, SpawnParams);
								AAray.Add(HouseTile);
									});
								FTimerHandle TimerHandle;
								GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);

								break;
							}
						case 1:
							{
								if (cnt <= 4)
								{
									if (cnt == 3)
									{
										FTimerDelegate TimerDelegate;
										AActor* FountainTile;
										TimerDelegate.BindLambda([=, &FountainTile]() {
											FountainTile = GetWorld()->SpawnActor<AActor>(Fontain, SpawnLocation, rotator, SpawnParams); 
											AAray.Add(FountainTile);
											});
										FTimerHandle TimerHandle;
										GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);

								
										cnt++;
										break;
									}
									else
									{
										FTimerDelegate TimerDelegate;
										AActor* TowerTile;
										TimerDelegate.BindLambda([=, &TowerTile]() {
											TowerTile = GetWorld()->SpawnActor<AActor>(Tower, SpawnLocation, rotator, SpawnParams);
										AAray.Add(TowerTile);
											});
										FTimerHandle TimerHandle;
										GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);

										cnt++;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void AProceduralNoiseGenerator::CreateTrees()
{
	
	UWorld* world = GetWorld();
	if (Tree != nullptr && House != nullptr && motel != nullptr && Shop != nullptr && Tower != nullptr)
	{
		int32 cnt = 0;
		if(Objective >= 2){
			for (int i = XSize - 3; i >= 3; --i) {
				for (int j = YSize - 3; j >= 3; --j) {
					TreeTime += 0.0005f;
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					FRotator rotator;
					FVector SpawnLocation;
					SpawnLocation.X = i * 100 + GetActorLocation().X;
					SpawnLocation.Y = j * 100 + GetActorLocation().Y;
					//SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z - 10;
					//SpawnLocation.Z = GetActorLocation().Z - 10;
					SpawnLocation.Z = Zvalue[i][j];
					rotator.Roll = 0;
					rotator.Pitch = 0;
					if (height[i][j] == 1) {
						rotator.Yaw = FMath::FRandRange(-90.0f, 90.0f);

						FTimerDelegate TimerDelegate;
						AActor* Tile1 ;
						TimerDelegate.BindLambda([=, &Tile1]() {
							Tile1 = GetWorld()->SpawnActor<AActor>(Tree, SpawnLocation, rotator, SpawnParams);
							float randscale = FMath::FRandRange(0.15,0.5);
							if(Theme == 3)
								randscale = 0.1f;
							Tile1->SetActorRelativeScale3D(FVector(randscale,randscale,randscale));
							//Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
							AAray.Add(Tile1);
						});
						FTimerHandle TimerHandle;
						GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TreeTime, false);

					}
				}
			}
		}
		if(Objective == 1){
			for (int i = XSize - 1; i >= 0; --i) {
				for (int j = YSize - 1; j >= 0; --j) {
					TreeTime += 0.0005f;
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					FRotator rotator;
					FVector SpawnLocation;
					SpawnLocation.X = i * 100 + GetActorLocation().X;
					SpawnLocation.Y = j * 100 + GetActorLocation().Y;
					//SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z - 10;
					//SpawnLocation.Z = GetActorLocation().Z - 10;
					SpawnLocation.Z = Zvalue[i][j];
					rotator.Roll = 0;
					rotator.Pitch = 0;
					if (height[i][j] == 1) {
						rotator.Yaw = FMath::FRandRange(-90.0f, 90.0f);

						FTimerDelegate TimerDelegate;
						AActor* Tile1 ;
						TimerDelegate.BindLambda([=, &Tile1]() {
							Tile1 = GetWorld()->SpawnActor<AActor>(Tree, SpawnLocation, rotator, SpawnParams);
							float randscale = FMath::FRandRange(0.15,0.5);
							if(Theme == 3)
								randscale = 0.1f;
							Tile1->SetActorRelativeScale3D(FVector(randscale,randscale,randscale));
							//Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
							AAray.Add(Tile1);
						});
						FTimerHandle TimerHandle;
						GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TreeTime, false);

					}
				}
			}
		}
	}
}

void AProceduralNoiseGenerator::CreateSpecial()
{
	SpecialTime = 0.0f;
	UWorld* world = GetWorld();
	if (Tree != nullptr && House != nullptr && motel != nullptr && Shop != nullptr && Tower != nullptr) {
		int32 cnt = 0;
		for (int i = XSize - 1; i >= 0; --i) {
			for (int j = YSize - 1; j >= 0; --j) {
				SpecialTime += 0.0005f;
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector SpawnLocation;
				SpawnLocation.X = i * 100 + GetActorLocation().X;
				SpawnLocation.Y = j * 100 + GetActorLocation().Y;
				//SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z - 10;
				//SpawnLocation.Z =  GetActorLocation().Z - 10;
				SpawnLocation.Z = Zvalue[i][j];
				rotator.Roll = 0;
				if (height[i][j] == 5) { //더미여관생성
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					rotator.Pitch = 0;
					//SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z;
					FTimerDelegate TimerDelegate;
					AActor* MotelTile;
					TimerDelegate.BindLambda([=, &MotelTile]() {
						MotelTile = GetWorld()->SpawnActor<AActor>(Dummymotel, SpawnLocation, rotator, SpawnParams);					
					AAray.Add(MotelTile);
						});
					FTimerHandle TimerHandle;
					GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, SpecialTime, false);

				}
				else if (height[i][j] == 6) { //더미상점생성
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					rotator.Pitch = 0;
					FTimerDelegate TimerDelegate;
					AActor* Shoptile;
					TimerDelegate.BindLambda([=, &Shoptile]() {
						Shoptile = GetWorld()->SpawnActor<AActor>(DummyShop, SpawnLocation, rotator, SpawnParams);
					AAray.Add(Shoptile);
						});
					FTimerHandle TimerHandle;
					GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, SpecialTime, false);
				}
				else if (height[i][j] == 9) { //상점생성
					if(Objective == 1)
						rotator.Yaw = -90;
					else
						rotator.Yaw = 90 * FMath::RandRange(0, 3);
					rotator.Pitch = 0;
					//SpawnLocation.Z = GetActorLocation().Z + 20;
					FTimerDelegate TimerDelegate;
					AActor* Shoptile;
					TimerDelegate.BindLambda([=, &Shoptile]() {
						Shoptile = GetWorld()->SpawnActor<AActor>(Shop, SpawnLocation, rotator, SpawnParams);
					AAray.Add(Shoptile);
						});
					FTimerHandle TimerHandle;
					GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, SpecialTime, false);
				}
				else if (height[i][j] == 10) { //여관생성
					if(Objective == 1)
						rotator.Yaw = -90;
					else
						rotator.Yaw = 90 * FMath::RandRange(0, 3);
					rotator.Pitch = 0;
					//SpawnLocation.Z = GetActorLocation().Z + 20;
					FTimerDelegate TimerDelegate;
					AActor* moteltile;
					TimerDelegate.BindLambda([=, &moteltile]() {
						moteltile = GetWorld()->SpawnActor<AActor>(motel, SpawnLocation, rotator, SpawnParams);
					AAray.Add(moteltile);
						});
					FTimerHandle TimerHandle;
					GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, SpecialTime, false);
				}
				else if (height[i][j] == 12) { //포탈생성
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					rotator.Pitch = 0;
					SpawnLocation.Z = GetActorLocation().Z + 100;
					FTimerDelegate TimerDelegate;
					AActor* Portal;
					TimerDelegate.BindLambda([=, &Portal]() {
						Portal = GetWorld()->SpawnActor<AActor>(PortalObject, SpawnLocation, rotator, SpawnParams);
					AAray.Add(Portal);
						});
					FTimerHandle TimerHandle;
					GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, SpecialTime, false);
				}
				else if (height[i][j] == 13) { //대장간
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					rotator.Pitch = 0;
					SpawnLocation.Z += 20;
					FTimerDelegate TimerDelegate;
					AActor* SmithTile;
					TimerDelegate.BindLambda([=, &SmithTile]() {
						SmithTile = GetWorld()->SpawnActor<AActor>(Smith, SpawnLocation, rotator, SpawnParams);
					AAray.Add(SmithTile);
						});
					FTimerHandle TimerHandle;
					GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, SpecialTime, false);
				}
			}
		}
	}
	int Scroll_Cnt=0;
	while(Scroll_Cnt < Objective)
	{
		int x = FMath::RandRange(3,XSize-3);
		int y = FMath::RandRange(3,YSize-3);
		if(height[x][y]==0)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator rotator;
			FVector SpawnLocation;
			SpawnLocation.X = x * 100 + GetActorLocation().X;
			SpawnLocation.Y = y * 100 + GetActorLocation().Y;
			SpawnLocation.Z = Zvalue[x][y] + 100;
			AActor* BP_scroll = world->SpawnActor<AActor>(Scroll, SpawnLocation, FRotator(0,0,0), SpawnParams);
			AAray.Add(BP_scroll);
			Scroll_Cnt++;
			UE_LOG(LogTemp,Warning,TEXT("SCroll"));
		}
	}
	
	int npc_cnt = 0;
	while(npc_cnt < NPCCount)
	{
		int x = FMath::RandRange(3,XSize-3);
		int y = FMath::RandRange(3,YSize-3);
		if(height[x][y]==0)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator rotator = {0,0,0};
			FVector SpawnLocation;
			SpawnLocation.X = x * 100 + GetActorLocation().X;
			SpawnLocation.Y = y * 100 + GetActorLocation().Y;
			SpawnLocation.Z = Zvalue[x][y]  + 50;
			AActor* npc = world->SpawnActor<AActor>(NPC_Child, SpawnLocation, rotator, SpawnParams);
			AAray.Add(npc);
			npc_cnt++;
		}
	}
}

void AProceduralNoiseGenerator::CreateCastle()
{
	UWorld* world = GetWorld();
	if (castle != nullptr && NPC_Child != nullptr) {
		int32 cnt = 0;
		for (int i = XSize - 1; i >= 0; --i) {
			for (int j = YSize - 1; j >= 0; --j) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector SpawnLocation;
				SpawnLocation.X = i * 100 + GetActorLocation().X;
				SpawnLocation.Y = j * 100 + GetActorLocation().Y;
				//SpawnLocation.Z =  GetActorLocation().Z - 10;
				SpawnLocation.Z = Zvalue[i][j];
				//SpawnLocation.Z = Zvalue.Pop() + GetActorLocation().Z - 10;
				rotator.Roll = 0;
			
				if (height[i][j] == 8) { //성생성
					rotator.Yaw = 90 * FMath::RandRange(0, 3);
					AActor* castletile = world->SpawnActor<AActor>(castle, SpawnLocation, rotator, SpawnParams);
					AAray.Add(castletile);
				}
			}
		}
	}
}

