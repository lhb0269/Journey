// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralWorldMapGenerator.h"
#include "GameDataSingleton.h"
#include<random>
#include<algorithm>
#include<vector>
#include "GameFramework/PlayerController.h"


AProceduralWorldMapGenerator::AProceduralWorldMapGenerator()
{
    isDesertBoss = false;
    isForestBoss = false;
    isSnowBoss = false;

    isPortal = false;

 	PrimaryActorTick.bCanEverTick = true;
    isPlayerMove = false;
    townnamecnt=0;
    townname.push_back("moriocho");
    townname.push_back("Cape Canaveral");
    townname.push_back("Neapolis");
    townname.push_back("Eldoria");
    townname.push_back("Misthaven");
    townname.push_back("Emberwood");
    townname.push_back("Silvercrest");
    townname.push_back("Stormreach");
    townname.push_back("Havenbrook");
    townname.push_back("Dragon's Hollow");
    townname.push_back("Oakshade");
    townname.push_back("Serenity Falls");
    townname.push_back("Ironhold");
    townname.push_back("Whisperwind");
    townname.push_back("Frostholm");
    townname.push_back("Willowbrook");
    townname.push_back("Shadowfen");
    townname.push_back("Goldenleaf");
    townname.push_back("Brightwater");
    townname.push_back("Starhaven");
    townname.push_back("Thornkeep");
    townname.push_back("Moonshadow");
    townname.push_back("Sunridge");
    townname.push_back("DIO's World");
    townname.push_back("Windmere");
    townname.push_back("Twilight Glade");
    townname.push_back("Maplehurst");
    townname.push_back("Stormgaard");
    townname.push_back("Frostfall");
    townname.push_back("Duskwood");
    townname.push_back("Stonemeadow");
    townname.push_back("Evergreen");
    townname.push_back("Ironforge");
    townname.push_back("Silvermoon");
    townname.push_back("Ravenstone");
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(townname.begin(),townname.end(),g);
    
    MapPos.Add(FVector(-58689.839353, -46396.097618, 200.000000));
    MapPos.Add(FVector(-60434.839353, -79441.097618, 200.000000));
    MapPos.Add(FVector(-59944.839353, -111341.097618, 200.000000));
    MapPos.Add(FVector(8620.160647, -111201.097618, 200.000000));
    MapPos.Add(FVector(5360.160647, -79486.097618, 200.000000));
    MapPos.Add(FVector(5360.160647, -47226.097618, 200.000000));
    MapPos.Add(FVector(42035.160647, -46301.097618, 200.000000));
    MapPos.Add(FVector(42035.160647, -79436.097618, 200.000000));
    MapPos.Add(FVector(43475.160647, -110881.097618, 200.000000));
}


void AProceduralWorldMapGenerator::BeginPlay()
{
	Super::BeginPlay();

    Seed = FDateTime::Now().GetTicks();

    terrainTime = 0.0f;
    TownTime = 0.0f;
    MonsterTime = 0.0f;
    DecoTime = 0.0f;

  /*  GenerateTerrain();
    GenerateTowns();
    GenerateMonsters();*/
	

}

void AProceduralWorldMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AProceduralWorldMapGenerator::Noise(int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n ^ Seed;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);


}

float AProceduralWorldMapGenerator::SmoothNoise(int x, int y)
{
    float corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
    float sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
    float center = Noise(x, y) / 4;

    return corners + sides + center;
}

float AProceduralWorldMapGenerator::InterpolatedNoise(float x, float y)
{
    int intX = int(x);
    float fracX = x - intX;

    int intY = int(y);
    float fracY = y - intY;

    float v1 = SmoothNoise(intX, intY);
    float v2 = SmoothNoise(intX + 1, intY);
    float v3 = SmoothNoise(intX, intY + 1);
    float v4 = SmoothNoise(intX + 1, intY + 1);

    float i1 = Interpolate(v1, v2, fracX);
    float i2 = Interpolate(v3, v4, fracX);

    return Interpolate(i1, i2, fracY);
}

float AProceduralWorldMapGenerator::Interpolate(float a, float b, float x)
{
    float ft = x * 3.1415927;
    float f = (1 - cos(ft)) * 0.5;

    return a * (1 - f) + b * f;
}

void AProceduralWorldMapGenerator::GenerateTerrain()
{
    float scale = 0.5f; 

    int tileVal = FMath::RandRange(0, 2);


    heightMap.SetNum(width);
    for (int i = 0; i < width; i++)
    {
        heightMap[i].SetNum(height);
        for (int j = 0; j < height; j++)
        {
            heightMap[i][j].heightVal = InterpolatedNoise(i * scale, j * scale);

            // 보간할 가중치 계산
            float t = static_cast<float>(i) / (width - 1);
            float u = static_cast<float>(j) / (height - 1);

            // 인접한 타일 유형 보간
            int tileType1, tileType2, tileType3;
            if (i < width / 2 && j < height / 2)
            {
                tileType1 = tileVal % 3;
                tileType2 = (tileVal + 1) % 3;
                tileType3 = tileVal % 3;
            }
            else if (i >= width / 2 && j < height / 2)
            {
                tileType1 = (tileVal + 1) % 3;
                tileType2 = (tileVal + 2) % 3;
                tileType3 = (tileVal + 1) % 3;
            }
            else if (j >= height / 2)
            {
                tileType1 = tileVal % 3;
                tileType2 = (tileVal + 2) % 3;
                tileType3 = (tileVal + 2) % 3;
            }

            // 보간된 타일 유형 결정
            heightMap[i][j].tileType = InterpolateTileType(tileType1, tileType2, tileType3, t, u);

      
        }
    }


    for (int k = 0; k < 10; k++)
    {
        // 산 타일의 위치를 랜덤으로 지정
        int mountainX = FMath::RandRange(0, width - 1);
        int mountainY = FMath::RandRange(0, height - 1);

        // 산 타일로 설정
        heightMap[mountainX][mountainY].tileType = 3;
    }

    terrainTime = 0.0f;
    // Generate the terrain
    for (int i = 0; i < width; i++)
    {

        for (int j = 0; j < height; j++)
        {
            if (heightMap[i][j].tileType == 3) // 산 타일인 경우
            {
                // 주변 타일들도 산 타일로 설정
                SetSurroundingTilesAsMountain(i, j);
            }
        }
    }

    for (int i = 0; i < width; i++)
    {

        for (int j = 0; j < height; j++)
        {
            terrainTime += 0.001f;
            float heightValue = heightMap[i][j].heightVal;
            FVector location;
            if (j % 2 == 0)
               location = FVector(i * 180 , j * 150, heightValue * heightVolume);
            else
               location = FVector(i * 180 +90 , j * 150, heightValue * heightVolume);


            if (heightValue < seaLevel)
            {
               // GetWorld()->SpawnActor<AActor>(Sea, location, FRotator::ZeroRotator);
                heightMap[i][j].isWater = true;
            }
            else 
            {
                if (heightMap[i][j].tileType == 0)
                {
                    if(heightMap[i][j].isPossible)
                    {
                        FTimerDelegate TimerDelegate;
                        TimerDelegate.BindLambda([=]() {
                            GetWorld()->SpawnActor<AActor>(GrassLand, location, FRotator::ZeroRotator);
                            });
                        FTimerHandle TimerHandle;
                        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, terrainTime, false);
                    }
                }
                if (heightMap[i][j].tileType == 1)
                {
                    if(heightMap[i][j].isPossible)
                    {
                        FTimerDelegate TimerDelegate;
                        TimerDelegate.BindLambda([=]() {
                            GetWorld()->SpawnActor<AActor>(DesertLand, location, FRotator::ZeroRotator);
                            });
                        FTimerHandle TimerHandle;
                        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, terrainTime, false);
                    }
                }
                if (heightMap[i][j].tileType == 2)
                {
                    if(heightMap[i][j].isPossible)
                    {
                        FTimerDelegate TimerDelegate;
                        TimerDelegate.BindLambda([=]() {
                            GetWorld()->SpawnActor<AActor>(SnowLand, location, FRotator::ZeroRotator);
                            });
                        FTimerHandle TimerHandle;
                        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, terrainTime, false);
                    }
                }
                if (heightMap[i][j].tileType == 3)
                {
                    location.Z += 150;
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(MountainLand, location, FRotator::ZeroRotator);
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, terrainTime, false);
                }
                if (heightMap[i][j].tileType == 4)
                {
                    location.Z += 100;
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(MountainLand, location, FRotator::ZeroRotator);
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, terrainTime, false);
                }
              
            }
        }
    }
}

void AProceduralWorldMapGenerator::GenerateTowns()
{
    int GrassCount = 0;
    int DesertCount = 0;
    int SnowCount = 0;

    TownTime = terrainTime;

    int townDistance = 10; 
    int lastTownPositionI = -townDistance; 
    int lastTownPositionJ = -townDistance; 


    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
            TownTime += 0.001f;

            float heightValue = heightMap[i][j].heightVal;
            if (heightValue >= seaLevel)
            {
                if (FMath::FRand() < townFrequency)
                {
\
                        FVector location;
                        if (j % 2 == 0)
                            location = FVector(i * 180, j * 150, heightValue * heightVolume + 200);
                        else
                            location = FVector(i * 180 + 90, j * 150, heightValue * heightVolume + 200);

                    

                        // �� �ʿ� �縷
                        if (heightMap[i][j].tileType == 0 && GrassCount < 3 && heightMap[i][j].isPossible)
                        {
                            AWorldCubeBase* wc ;                         
                         
                            FTimerDelegate TimerDelegate;
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(GrassTown, location, FRotator::ZeroRotator);
                                wc->Location = MapPos[3 + GrassCount];
                                wc->isVisited = false;
                                wc->isTown = true;
								wc->townname = townname[townnamecnt];
                                townnamecnt++;
                                });
                            FTimerHandle TimerHandle;
                            GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);
                            GrassCount += 1;
                            heightMap[i][j].isPossible = false;
                            heightMap[i][j].isTown = true;
                            heightMap[i][j].location = location;
                        }
                        if (heightMap[i][j].tileType == 1 && DesertCount < 3 && heightMap[i][j].isPossible)
                        {
                            AWorldCubeBase* wc;
                        
                            FTimerDelegate TimerDelegate;
                            TimerDelegate.BindLambda([=, &wc]()
                                {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(DesertTown, location, FRotator::ZeroRotator);
                            wc->Location = MapPos[6 + DesertCount];
                            wc->isVisited = false;
                            wc->isTown = true;

                            wc->townname = townname[townnamecnt];
                                townnamecnt++;

                                });
                            FTimerHandle TimerHandle;
                            GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);

                            if (!isPlayerMove)
                            {
                                playerSpawnPos = FVector(location.X, location.Y, location.Z );
                                isPlayerMove = true;
                            }
                            DesertCount += 1;
                            heightMap[i][j].isPossible = false;
                            heightMap[i][j].isTown = true;
                            heightMap[i][j].location = location;

                        }
                        if (heightMap[i][j].tileType == 2 && SnowCount < 3 && heightMap[i][j].isPossible)
                        {
                            heightMap[i][j].isPossible = false;
                            AWorldCubeBase* wc;                         
                            FTimerDelegate TimerDelegate;
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(SnowTown, location, FRotator::ZeroRotator);; 
                            wc->Location = MapPos[SnowCount];
                            wc->isVisited = false;
                            wc->isTown = true;
							wc->townname = townname[townnamecnt];
                                townnamecnt++;
                                });
                            FTimerHandle TimerHandle;
                            GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);

                            SnowCount += 1;
                            heightMap[i][j].isPossible = false;
                            heightMap[i][j].isTown = true;
                            heightMap[i][j].location = location;
                        }
                }

                if (FMath::FRand() < objectFrequency)
                {
                    FVector location;
                    if (j % 2 == 0)
                        location = FVector(i * 180, j * 150, heightValue * heightVolume + 200);
                    else
                        location = FVector(i * 180 + 90, j * 150, heightValue * heightVolume + 200);


                    if (heightMap[i][j].tileType == 0 && heightMap[i][j].isPossible)
                    {
                        heightMap[i][j].isPossible = false;
                        AActor* wc;
                        FTimerDelegate TimerDelegate;
                        TimerDelegate.BindLambda([=, &wc]() {
                            wc = GetWorld()->SpawnActor<AActor>(GrassObj, location, FRotator::ZeroRotator);
                            });
                        FTimerHandle TimerHandle;
                        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);
                    }
                    if (heightMap[i][j].tileType == 1 && heightMap[i][j].isPossible)
                    {
                        AActor* wc;
                        heightMap[i][j].isPossible = false;
                        FTimerDelegate TimerDelegate;
                        TimerDelegate.BindLambda([=, &wc]() {
                            wc = GetWorld()->SpawnActor<AActor>(DesertObj, location, FRotator::ZeroRotator);
                            });
                        FTimerHandle TimerHandle;
                        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);
                    }
                    if (heightMap[i][j].tileType == 2 && heightMap[i][j].isPossible)
                    {
                        AActor* wc;
                        heightMap[i][j].isPossible = false;
                        FTimerDelegate TimerDelegate;
                        TimerDelegate.BindLambda([=, &wc]() {
                            wc = GetWorld()->SpawnActor<AActor>(SnowObj, location, FRotator::ZeroRotator);
                            });
                        FTimerHandle TimerHandle;
                        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);
                    }
                }
                
            }
        }
    }
    
}

void AProceduralWorldMapGenerator::GenerateMonsters()
{

    MonsterTime = terrainTime;
    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
            MonsterTime += 0.001f;
            float heightValue = heightMap[i][j].heightVal;
            if (heightValue >= seaLevel)
            {
                if (FMath::FRand() < monsterFrequency && heightMap[i][j].isPossible)
                {
                    FVector location;
                    if (j % 2 == 0)
                        location = FVector(i * 180, j * 150, heightValue * heightVolume + 200);
                    else
                        location = FVector(i * 180 + 90, j * 150, heightValue * heightVolume + 200);
                 
                    heightMap[i][j].location = location;
                    int val = FMath::RandRange(1, 10);
                    heightMap[i][j].isPossible = false;
                    AWorldCubeBase* wc;
                    FTimerDelegate TimerDelegate;

                    //  생성 난수 
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_real_distribution<> dis(0.0, 1.0);
                    double randomValue = dis(gen);

  

                    if (heightMap[i][j].tileType == 0)
                    {
                        // 순서는 고블린, 골렘, 오크
                        if (randomValue < 1.0 / 3.0)
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(ForestGoblinBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 0;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });
                        }
                        else if (randomValue < 2.0 / 3.0)
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(ForestGolemBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 2;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });
                        }
                        else
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(ForestOrcBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 1;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });
         
                        }
        
                    }
                    if (heightMap[i][j].tileType == 1)
                    {
                        // 순서는 고블린, 골렘, 오크
                        if (randomValue < 1.0 / 3.0)
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(DesertGoblinBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 6;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });
                        }
                        else if (randomValue < 2.0 / 3.0)
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(DesertGolemBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 8;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });
                        }
                        else
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(DesertOrcBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 7;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });

                        }
                    }
                    if (heightMap[i][j].tileType == 2)
                    {
                        if (randomValue < 1.0 / 3.0)
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(SnowGoblinBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 3;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });
                        }
                        else if (randomValue < 2.0 / 3.0)
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(SnowGolemBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 4;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });
                        }
                        else
                        {
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(SnowOrcBase, location, FRotator::ZeroRotator);
                            wc->monsterLevel = 1;
                            wc->tileType = 5;
                            wc->monsterType = 1;
                            wc->monsterPower = 1000;
                            wc->isKey = false;
                            wc->isTown = false;
                            wc->isVisited = false;
                            if (val == 1)
                                wc->isKey = true;
                                });

                        }
                    }
                   
                
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, MonsterTime, false);

           
                }
                if ( heightMap[i][j].isPossible && heightMap[i][j].tileType == 0 && !isForestBoss)
                {
                    isForestBoss = true;
                    FVector location;
                    if (j % 2 == 0)
                        location = FVector(i * 180, j * 150, heightValue * heightVolume + 200);
                    else
                        location = FVector(i * 180 + 90, j * 150, heightValue * heightVolume + 200);


                    int val = FMath::RandRange(1, 10);
                    heightMap[i][j].isPossible = false;
                    AWorldCubeBase* wc;
                    FTimerDelegate TimerDelegate;

                    TimerDelegate.BindLambda([=, &wc]() {
                        wc = GetWorld()->SpawnActor<AWorldCubeBase>(GoblinBossBase, location, FRotator::ZeroRotator);
                    wc->monsterLevel = 1;
                    wc->tileType = 9;
                    wc->monsterType = 1;
                    wc->monsterPower = 1000;
                    wc->isKey = false;
                    wc->isTown = false;
                    wc->isVisited = false;
                    if (val == 1)
                        wc->isKey = true;
                        });
                    

                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, MonsterTime, false);
                }
                if ( heightMap[i][j].isPossible && heightMap[i][j].tileType == 1 && !isDesertBoss)
                {
                    isDesertBoss = true;

                    FVector location;
                    if (j % 2 == 0)
                        location = FVector(i * 180, j * 150, heightValue * heightVolume + 200);
                    else
                        location = FVector(i * 180 + 90, j * 150, heightValue * heightVolume + 200);


                    int val = FMath::RandRange(1, 10);
                    heightMap[i][j].isPossible = false;
                    AWorldCubeBase* wc;
                    FTimerDelegate TimerDelegate;

                    TimerDelegate.BindLambda([=, &wc]() {
                        wc = GetWorld()->SpawnActor<AWorldCubeBase>(OrcBossBase, location, FRotator::ZeroRotator);
                    wc->monsterLevel = 1;
                    wc->tileType = 11;
                    wc->monsterType = 1;
                    wc->monsterPower = 1000;
                    wc->isKey = false;
                    wc->isTown = false;
                    wc->isVisited = false;
                    if (val == 1)
                        wc->isKey = true;
                        });


                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, MonsterTime, false);
                }
                if (heightMap[i][j].isPossible && heightMap[i][j].tileType == 2 && !isSnowBoss)
                {
                    isSnowBoss = true;
                    FVector location;
                    if (j % 2 == 0)
                        location = FVector(i * 180, j * 150, heightValue * heightVolume + 200);
                    else
                        location = FVector(i * 180 + 90, j * 150, heightValue * heightVolume + 200);


                    int val = FMath::RandRange(1, 10);
                    heightMap[i][j].isPossible = false;
                    AWorldCubeBase* wc;
                    FTimerDelegate TimerDelegate;

                    TimerDelegate.BindLambda([=, &wc]() {
                        wc = GetWorld()->SpawnActor<AWorldCubeBase>(GolemBossBase, location, FRotator::ZeroRotator);
                    wc->monsterLevel = 1;
                    wc->tileType = 10;
                    wc->monsterType = 1;
                    wc->monsterPower = 1000;
                    wc->isKey = false;
                    wc->isTown = false;
                    wc->isVisited = false;
                    if (val == 1)
                        wc->isKey = true;
                        });


                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, MonsterTime, false);
                }

            }
            else
            {
                heightMap[i][j].isWater = true;
            }
        }
    }
}

void AProceduralWorldMapGenerator::GenerateDeco()
{
    DecoTime = terrainTime;
    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
            DecoTime += 0.001f;
            float heightValue = heightMap[i][j].heightVal;
            FVector location;
            if (j % 2 == 0)
                location = FVector(i * 180 , j * 150, heightValue * heightVolume);
            else
                location = FVector(i * 180 +90 , j * 150, heightValue * heightVolume);
            if (heightMap[i][j].tileType == 0)
            {
                if(heightMap[i][j].isPossible && !heightMap[i][j].isWater)
                {
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(GrassDeco[FMath::RandRange(0,GrassDeco.Num()-1)], location, FRotator::ZeroRotator);
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DecoTime, false);
                }
            }
            if (heightMap[i][j].tileType == 1)
            {
                if(heightMap[i][j].isPossible && !heightMap[i][j].isWater)
                {
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(DesertDeco[FMath::RandRange(0,DesertDeco.Num()-1)], location, FRotator::ZeroRotator);
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DecoTime, false);
                }
            }
            if (heightMap[i][j].tileType == 2)
            {
                if(heightMap[i][j].isPossible && !heightMap[i][j].isWater)
                {
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(SnowDeco[FMath::RandRange(0,SnowDeco.Num()-1)], location, FRotator::ZeroRotator);
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DecoTime, false);
                }
            }
            
        }
    }
}

int AProceduralWorldMapGenerator::InterpolateTileType(int tileType1, int tileType2, int tileType3, float t, float u)
{
    float oneMinusT = 1.0f - t;
    float oneMinusU = 1.0f - u;

    float weight1 = oneMinusT * oneMinusU;
    float weight2 = t * oneMinusU;
    float weight3 = oneMinusT * u;

    float interpolatedTileTypeFloat = weight1 * tileType1 + weight2 * tileType2 + weight3 * tileType3;

    // 반올림하여 정수 타입으로 변환
    int interpolatedTileType = static_cast<int>(interpolatedTileTypeFloat + 0.5f);

    return interpolatedTileType;
}

int AProceduralWorldMapGenerator::LinearInterpolation(int value1, int value2, float t)
{
    return static_cast<int>(value1 * (1 - t) + value2 * t);
}

void AProceduralWorldMapGenerator::SetSurroundingTilesAsMountain(int i, int j)
{
    if (heightMap[i][j].tileType == 3)
    {
        // 주변 타일 인덱스 계산
        int startI = FMath::Max(0, i - 1);
        int endI = FMath::Min(width - 1, i + 1);
        int startJ = FMath::Max(0, j - 1);
        int endJ = FMath::Min(height - 1, j + 1);

        // 주변 타일들을 산 타일로 설정
        for (int x = startI; x <= endI; x++)
        {
            for (int y = startJ; y <= endJ; y++)
            {
                if (x != i || y != j) // 현재 타일은 제외하고 주변 타일 변경
                {
                    if (x >= 0 && x < width && y >= 0 && y < height) // 인덱스의 유효성 검사
                    {
                        heightMap[x][y].tileType = 4; // 산 타일로 설정
                    }
                }
            }
        }
    }
}

void AProceduralWorldMapGenerator::createBossPortal()
{

    int X = FMath::RandRange(0, width);
    int Y = FMath::RandRange(0, height);

    if (!isPortal)
    {
        for (int i = 1; i < width - 1; i++)
        {
            for (int j = 1; j < height - 1; j++)
            {
                if (heightMap[i][j].heightVal < seaLevel)
                    continue;
                if (heightMap[i][j].tileType == 3)
                    continue;
                if (heightMap[i][j].tileType == 4)
                    continue;
                if (heightMap[i][j].isTown)
                    continue;
                if (!heightMap[i][j].isPossible)
                    continue;

                FVector location;
                if (j % 2 == 0)
                    location = FVector(i * 180, j * 150, heightMap[i][j].heightVal);
                else
                    location = FVector(i * 180 + 90, j * 150, heightMap[i][j].heightVal);
 
                GetWorld()->SpawnActor<AActor>(Portal, location, FRotator::ZeroRotator);
                isPortal = true;
                heightMap[i][j].isPortal = true;
                return;
  
            }
        }
    }
   

}


