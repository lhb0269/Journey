// Fill out your copyright notice in the Description page of Project Settings.

#include "CellularAutomata.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "JourneySaveGame.h"
#include "AI/NavigationSystemBase.h" 
#include "NavigationSystem.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "Components/ChildActorComponent.h"
#include "Math/UnrealMath.h"
#include "GameDataSingleton.h"
#include <array>
#include "HeroCharacter.h"

// Sets default values
ACellularAutomata::ACellularAutomata()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellularAutomata::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	bool Original = false;
	float wall = 0;
	//int gap = 225;
	int gap = 200;


	Tilemax = 6;

	// 12x12 �ʻ���
	GenMapData();
	
	//width.clear();
	//height.clear();
	//for (int i = 0; i < Tilemax; ++i) {
	//	for (int j = 0; j < Tilemax; ++j) {
	//		width.push_back(CATileInfos[j + i * Tilemax].tileType);
	//	}
	//	height.push_back(width);
	//	width.clear();
	//}
	//
	//width.clear();
	//height.clear();
	//for (int i = 0; i < Tilemax; ++i) {
	//	for (int j = 0; j < Tilemax; ++j) {
	//		width.push_back(FMath::RandRange(0, 1));
	//		if (width[j] == 1)
	//			wall++;
	//	}
	//	height.push_back(width);
	//	width.clear();
	//}
	//if (Tilemax >= 8) {
	//	for (int i = 0; i < Tilemax; ++i) {
	//		for (int j = 0; j < Tilemax; ++j) {
	//			int32 count = 0;
	//			if (height[i][j] == 1) count += 1;
	//			if (i + 1 < Tilemax && i - 1 >= 0 && j + 1 < Tilemax && j - 1 >= 0) {
	//				if (height[i - 1][j - 1] == 1)  count += 1;
	//				if (height[i - 1][j] == 1)  count += 1;
	//				if (height[i - 1][j + 1] == 1)  count += 1;
	//				if (height[i][j - 1] == 1)  count += 1;
	//				if (height[i][j + 1] == 1)  count += 1;
	//				if (height[i + 1][j - 1] == 1)  count += 1;
	//				if (height[i + 1][j] == 1)  count += 1;
	//				if (height[i + 1][j + 1] == 1)  count += 1;
	//			}
	//			else {
	//				count = 6;
	//			}
	//			if (count >= 6)height[i][j] = 1;
	//			else if (count == 3)height[i][j] = 2;
	//			else height[i][j] = 0;
	//		}
	//	}
	//}
	//else
	//{
	//	for (int i = 0; i < Tilemax; ++i) {
	//		for (int j = 0; j < Tilemax; ++j) {
	//			int32 count = 0;
	//			if (height[i][j] == 0) count += 1;
	//			if (i + 1 < Tilemax && i - 1 >= 0 && j + 1 < Tilemax && j - 1 >= 0) {
	//				if (height[i - 1][j - 1] == 0)  count += 1;
	//				if (height[i - 1][j] == 0)  count += 1;
	//				if (height[i - 1][j + 1] == 0)  count += 1;
	//				if (height[i][j - 1] == 0)  count += 1;
	//				if (height[i][j + 1] == 0)  count += 1;
	//				if (height[i + 1][j - 1] == 0)  count += 1;
	//				if (height[i + 1][j] == 0)  count += 1;
	//				if (height[i + 1][j + 1] == 0)  count += 1;
	//			}
	//			else {
	//				count = 6;
	//			}
	//			if (count >= 6)height[i][j] = 0;
	//			else if (count == 3)height[i][j] = 2;
	//			else height[i][j] = 1;
	//		}
	//	}
	//}
	//


	//UE_LOG(LogTemp, Warning, TEXT("%d"), height.size());
	//if (Tile != nullptr && Mountain != nullptr && River != nullptr) {
	//	for (int i = 0; i < Tilemax; ++i) {
	//		for (int j = 0; j < Tilemax; ++j) {
	//			FActorSpawnParameters SpawnParams;
	//			SpawnParams.Owner = this;
	//			FRotator rotator;
	//			FVector SpawnLocation;
	//			SpawnLocation.Y = i * 360 + GetActorLocation().Y;
	//			if (i % 2 == 0)
	//				SpawnLocation.X = j * 390 + GetActorLocation().X;
	//			else
	//				SpawnLocation.X = j * 390 + GetActorLocation().X + gap;
	//			SpawnLocation.Z = GetActorLocation().Z;



	//			if (height[i][j] == 0) {
	//				AWorldCubeBase* Tile1 = world->SpawnActor<AWorldCubeBase>(Tile, SpawnLocation, rotator, SpawnParams);
	//				Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	//				Tile1->cubeNumber = j + i * Tilemax;
	//				Tile1->isVisited = CATileInfos[j + i * Tilemax].isVisited;
	//				Tile1->isTown = CATileInfos[j + i * Tilemax].isTown;
	//				Tile1->isKey = CATileInfos[j + i * Tilemax].isKey;
	//				Tile1->resetCubeState();
	//				AArray.Add(Tile1);


	//			}
	//			else if (height[i][j] == 1) {//Mountain
	//				AWorldCubeBase* MountainTile = world->SpawnActor<AWorldCubeBase>(Mountain, SpawnLocation, rotator, SpawnParams);
	//				MountainTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	//				MountainTile->cubeNumber = j + i * Tilemax;
	//				MountainTile->isVisited = CATileInfos[j + i * Tilemax].isVisited;
	//				MountainTile->isTown = CATileInfos[j + i * Tilemax].isTown;
	//				MountainTile->isKey = CATileInfos[j + i * Tilemax].isKey;
	//				MountainTile->resetCubeState();
	//				//FVector Scale;
	//				//Scale.X = 1.0f; Scale.Y = 1.0f; Scale.Z = FMath::FRandRange(1.0f, 50.0f);
	//				//MountainTile->SetActorScale3D(Scale);
	//				AArray.Add(MountainTile);

	//			}
	//			else if (height[i][j] == 2) {//River
	//				AWorldCubeBase* RiverTile = world->SpawnActor<AWorldCubeBase>(River, SpawnLocation, rotator, SpawnParams);
	//				RiverTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	//				RiverTile->cubeNumber = j + i * Tilemax;
	//				RiverTile->isVisited = CATileInfos[j + i * Tilemax].isVisited;
	//				RiverTile->isTown = CATileInfos[j + i * Tilemax].isTown;
	//				RiverTile->isKey = CATileInfos[j + i * Tilemax].isKey;
	//				RiverTile->resetCubeState();
	//				AArray.Add(RiverTile);

	//			}
	//		}
	//	}
	//}


	// ���� �Ϸ� �� ����, Ű �����ϱ�
	// ���� �����ϱ� 
	//GenRandomkeyTown();


	
	// ?�???�료 ?� ?�?�?��??�치 조정
	// 0403 ?��??�방?� 변경으�? �??�동?�?� ?��? 지?�
	/*AHeroCharacter* PlayerCharacter = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (chcekSaveFile())
	{
		PlayerCharacter->SetActorLocation(MySaveGame->SavedPos);
		PlayerCharacter->ChangeCamera(true);
	}*/

	// ?�???�료 ?� ?��?게?�션 ?�시 빌?�
	RebuildNavigationMesh();


	// ���� �Ϸ� �� UGameDataSingleton �� �߰�
	if(UGameDataSingleton::GetInstance()->TileInfos.IsEmpty())
		UGameDataSingleton::GetInstance()->TileInfos = MoveTemp(CATileInfos);

}

// Called every frame
void ACellularAutomata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACellularAutomata::OnConstruction(const FTransform& Transform)
{
	for (auto It = AArray.CreateIterator(); It; It++)
	{
		(*It)->Destroy();
	}
	AArray.Empty();
	RegisterAllComponents();

}

bool ACellularAutomata::chcekSaveFile()
{

	if (MySaveGame == nullptr)
	{
		return false;
	}


	return true;
	
}

void ACellularAutomata::RebuildNavigationMesh()
{
	UWorld* World = GetWorld();
	if (World)
	{
		
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World);
		if (NavSystem)
		{
			
			NavSystem->CancelBuild();
			NavSystem->Build();
		}
	}
}

void ACellularAutomata::GenRandomkeyTown()
{
	// create town number
	std::array<int32, 3> RandomNumbers;
	for (int32 i = 0; i < RandomNumbers.size(); i++)
	{
		bool IsDuplicate = true;

		while (IsDuplicate)
		{
			int32 NewRandomNumber = FMath::RandRange(1, (Tilemax*Tilemax - 1));

			// Check if the new number is already in the array
			IsDuplicate = false;
			for (int32 j = 0; j < i; j++)
			{
				if (RandomNumbers[j] == NewRandomNumber)
				{
					IsDuplicate = true;
					break;
				}
	
			}
			if (CATileInfos[NewRandomNumber].tileType != 0)			
				IsDuplicate = true;
	

			// If the new number is not a duplicate, add it to the array
			if (!IsDuplicate)
			{
				RandomNumbers[i] = NewRandomNumber;
				CATileInfos[NewRandomNumber].isTown = true;
				AArray[NewRandomNumber]->isTown = true;
				AArray[NewRandomNumber]->resetCubeState();
				UE_LOG(LogTemp, Warning, TEXT("town: %d"), NewRandomNumber);
			}
		}
	}
	
	// create key 
	for (int32 i = 0; i < RandomNumbers.size(); i++)
	{
		bool IsDuplicate = true;

		while (IsDuplicate)
		{
			int32 NewRandomNumber = FMath::RandRange(1, (Tilemax * Tilemax - 1));

			// Check if the new number is already in the array
			IsDuplicate = false;
			for (int32 j = 0; j < i; j++)
			{
				if (RandomNumbers[j] == NewRandomNumber)
				{
					IsDuplicate = true;
					break;
				}

	
			}

			if (CATileInfos[NewRandomNumber].tileType != 0)
				IsDuplicate = true;
	

			if (CATileInfos[NewRandomNumber].isTown)
				IsDuplicate = true;

			if (!IsDuplicate)
			{
				RandomNumbers[i] = NewRandomNumber;
				CATileInfos[NewRandomNumber].isKey = true;
				AArray[NewRandomNumber]->isKey = true;
				AArray[NewRandomNumber]->resetCubeState();
				UE_LOG(LogTemp, Warning, TEXT("Key: %d"), NewRandomNumber);
			}
		}
	}
	
	//TArray<AActor*> FoundActors;
	//TSubclassOf<AWorldCubeBase> ClassToFind = AWorldCubeBase::StaticClass();

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

	//for (AActor* Actor : FoundActors)
	//{
	//	Cast< AWorldCubeBase>(Actor)->Key->SetVisibility(true);
	//}
	
}

void ACellularAutomata::GenMapData()
{
	// 1. �ϴ� �÷��̾� ��ġ�� �������� ���� (1~4)
	int startNum = FMath::RandRange(1, 4);

	// 2. 4���� Ÿ�� �迭�� ������ ���踦 �Ѹ���. (�÷��̾� ��ġ�� Ÿ�� �迭�� ���踦 �����Ѵ�.)
	std::vector<TArray<FCAStruct>> CATileVector;
	TArray<FCAStruct> TileInfos;
	float wall = 0;
	UWorld* world = GetWorld();
	bool Original = false;
	int gap = 200;

	for (int tileCount = 0; tileCount < 4; tileCount++)
	{
		TileInfos.Init(FCAStruct(), Tilemax * Tilemax);
		width.clear();
		height.clear();
		for (int i = 0; i < Tilemax; ++i) {
			for (int j = 0; j < Tilemax; ++j) {
				width.push_back(FMath::RandRange(0, 1));
				if (width[j] == 1)
					wall++;
			}
			height.push_back(width);
			width.clear();
		}
		if (Tilemax >= 8) {
			for (int i = 0; i < Tilemax; ++i) {
				for (int j = 0; j < Tilemax; ++j) {
					int32 count = 0;
					if (height[i][j] == 1) count += 1;
					if (i + 1 < Tilemax && i - 1 >= 0 && j + 1 < Tilemax && j - 1 >= 0) {
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
					if (count >= 6)height[i][j] = 1;
					else if (count == 3)height[i][j] = 2;
					else height[i][j] = 0;
				}
			}
		}
		else
		{
			for (int i = 0; i < Tilemax; ++i) {
				for (int j = 0; j < Tilemax; ++j) {
					int32 count = 0;
					if (height[i][j] == 0) count += 1;
					if (i + 1 < Tilemax && i - 1 >= 0 && j + 1 < Tilemax && j - 1 >= 0) {
						if (height[i - 1][j - 1] == 0)  count += 1;
						if (height[i - 1][j] == 0)  count += 1;
						if (height[i - 1][j + 1] == 0)  count += 1;
						if (height[i][j - 1] == 0)  count += 1;
						if (height[i][j + 1] == 0)  count += 1;
						if (height[i + 1][j - 1] == 0)  count += 1;
						if (height[i + 1][j] == 0)  count += 1;
						if (height[i + 1][j + 1] == 0)  count += 1;
					}
					else {
						count = 6;
					}
					if (count >= 6)height[i][j] = 0;
					else if (count == 3)height[i][j] = 2;
					else height[i][j] = 1;
				}
			}
		}

		if (Tile != nullptr && Mountain != nullptr && River != nullptr) {
			for (int i = 0; i < Tilemax; ++i) 
			{
				for (int j = 0; j < Tilemax; ++j) 
				{
					// FCAStruct �� �߰�

					TileInfos[j + i * Tilemax].isVisited = false;
					TileInfos[j + i * Tilemax].isTown = false;
					TileInfos[j + i * Tilemax].isKey = false;
					TileInfos[j + i * Tilemax].tileType = height[i][j];
					//SpawnLocation �߰��������
					//CATileInfos[j + i * Tilemax].tilePos = SpawnLocation;

				}
			}
			// ����, ���踦 �����Ѵ�. 
			// create town number
			//std::array<int32, 3> RandomNumbers;
			//for (int32 i = 0; i < RandomNumbers.size(); i++)
			//{
			//	bool IsDuplicate = true;

			//	while (IsDuplicate)
			//	{
			//		int32 NewRandomNumber = FMath::RandRange(1, (Tilemax * Tilemax - 1));

			//		// Check if the new number is already in the array
			//		IsDuplicate = false;
			//		for (int32 j = 0; j < i; j++)
			//		{
			//			if (RandomNumbers[j] == NewRandomNumber)
			//			{
			//				IsDuplicate = true;
			//				break;
			//			}

			//		}
			//		if (TileInfos[NewRandomNumber].tileType != 0)
			//			IsDuplicate = true;


			//		// If the new number is not a duplicate, add it to the array
			//		if (!IsDuplicate)
			//		{
			//			RandomNumbers[i] = NewRandomNumber;
			//			TileInfos[NewRandomNumber].isTown = true;
			//			AArray[NewRandomNumber]->isTown = true;
			//			AArray[NewRandomNumber]->resetCubeState();
			//			UE_LOG(LogTemp, Warning, TEXT("town: %d"), NewRandomNumber);
			//		}
			//	}
			//}

			//// create key 
			//// ���� ��ġ�� �ƴϾ������ �۵���
			//if (startNum != tileCount)
			//{
			//	for (int32 i = 0; i < RandomNumbers.size(); i++)
			//	{
			//		bool IsDuplicate = true;

			//		while (IsDuplicate)
			//		{
			//			int32 NewRandomNumber = FMath::RandRange(1, (Tilemax * Tilemax - 1));

			//			// Check if the new number is already in the array
			//			IsDuplicate = false;
			//			for (int32 j = 0; j < i; j++)
			//			{
			//				if (RandomNumbers[j] == NewRandomNumber)
			//				{
			//					IsDuplicate = true;
			//					break;
			//				}
			//			}
			//			if (TileInfos[NewRandomNumber].tileType != 0)
			//				IsDuplicate = true;

			//			if (TileInfos[NewRandomNumber].isTown)
			//				IsDuplicate = true;

			//			if (!IsDuplicate)
			//			{
			//				RandomNumbers[i] = NewRandomNumber;
			//				TileInfos[NewRandomNumber].isKey = true;
			//				AArray[NewRandomNumber]->isKey = true;
			//				AArray[NewRandomNumber]->resetCubeState();
			//			}
			//		}
			//	}
			//}
			// ���� �� vector�� �߰��Ѵ�.
			CATileVector.push_back(TileInfos);
		}
	}
	

	// 3. �ϳ��� ��ģ��.
	for (int tileCount = 0; tileCount < 4; tileCount++)
	{
		for (int x = 0; x < Tilemax ; x++)
		{
			for (int y = 0; y < Tilemax ; y++)
			{
				MainTileInfos.Add(CATileVector[tileCount][y + x * Tilemax]);
			}
		}
	}

	// 4. Spawn Vector ����ش�.
	if (Tile != nullptr && Mountain != nullptr && River != nullptr) {
		for (int i = 0; i < Tilemax * 2; ++i) {
			for (int j = 0; j < Tilemax * 2; ++j) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector SpawnLocation;
				SpawnLocation.Y = i * 360 + GetActorLocation().Y;
				if (i % 2 == 0)
					SpawnLocation.X = j * 390 + GetActorLocation().X;
				else
					SpawnLocation.X = j * 390 + GetActorLocation().X + gap;
				SpawnLocation.Z = GetActorLocation().Z;

				MainTileInfos[j + i * Tilemax].tilePos = SpawnLocation;

				
				if (MainTileInfos[j + i * Tilemax].tileType == 0) {
					AWorldCubeBase* Tile1 = world->SpawnActor<AWorldCubeBase>(Tile, SpawnLocation, rotator, SpawnParams);
					Tile1->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					Tile1->cubeNumber = j + i * Tilemax;
					Tile1->isVisited = MainTileInfos[j + i * Tilemax].isVisited;
					Tile1->isTown = MainTileInfos[j + i * Tilemax].isTown;
					Tile1->isKey = MainTileInfos[j + i * Tilemax].isKey;
					AArray.Add(Tile1);


				}
				else if (MainTileInfos[j + i * Tilemax].tileType == 1) {//Mountain
					AWorldCubeBase* MountainTile = world->SpawnActor<AWorldCubeBase>(Mountain, SpawnLocation, rotator, SpawnParams);
					MountainTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					MountainTile->cubeNumber = j + i * Tilemax;
					MountainTile->isVisited = MainTileInfos[j + i * Tilemax].isVisited;
					MountainTile->isTown = MainTileInfos[j + i * Tilemax].isTown;
					MountainTile->isKey = MainTileInfos[j + i * Tilemax].isKey;

					//FVector Scale;
					//Scale.X = 1.0f; Scale.Y = 1.0f; Scale.Z = FMath::FRandRange(1.0f, 50.0f);
					//MountainTile->SetActorScale3D(Scale);
					AArray.Add(MountainTile);

				}
				else if (MainTileInfos[j + i * Tilemax].tileType == 2) {//River
					AWorldCubeBase* RiverTile = world->SpawnActor<AWorldCubeBase>(River, SpawnLocation, rotator, SpawnParams);
					RiverTile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
					RiverTile->cubeNumber = j + i * Tilemax;
					RiverTile->isVisited = MainTileInfos[j + i * Tilemax].isVisited;
					RiverTile->isTown = MainTileInfos[j + i * Tilemax].isTown;
					RiverTile->isKey = MainTileInfos[j + i * Tilemax].isKey;
					AArray.Add(RiverTile);

				}
			}
		}
	}
}

