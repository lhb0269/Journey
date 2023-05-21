// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralWorldMapGenerator.h"
#include "GameDataSingleton.h"
#include<random>
#include<algorithm>
#include<vector>
#include "GameFramework/PlayerController.h"


AProceduralWorldMapGenerator::AProceduralWorldMapGenerator()
{
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
    
    MapPos.Add(FVector(-60200.0, -46870.0, 540.000000));
    MapPos.Add(FVector(-60200.0, -79570.0, 540.000000));
    MapPos.Add(FVector(-60200.0, -110445.0, 540.000000));
    MapPos.Add(FVector(6205.0, -110445.0, 540.000000));
    MapPos.Add(FVector(5430.0, -79565.0, 540.000000));
    MapPos.Add(FVector(3320.0, -46950.0, 540.000000));
    MapPos.Add(FVector(40550.0, -44885.0, 540.000000));
    MapPos.Add(FVector(40550.0, -79765.0, 540.000000));
    MapPos.Add(FVector(40550.0, -110770.0, 540.000000));
    MapPos.Add(FVector(40550.0, -110770.0, 540.000000));
    MapPos.Add(FVector(40550.0, -110770.0, 540.000000));
    MapPos.Add(FVector(40550.0, -110770.0, 540.000000));
}


void AProceduralWorldMapGenerator::BeginPlay()
{
	Super::BeginPlay();

    Seed = FDateTime::Now().GetTicks();

    terrainTime = 0.0f;
    TownTime = 0.0f;
    MonsterTime = 0.0f;

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
           
            if (i < width / 2 && j < height / 2)
            {
                heightMap[i][j].tileType = tileVal%3;
            }


            if (i >= width / 2 && j < height / 2)
            {
                heightMap[i][j].tileType = (tileVal+1)%3;
            }

            if ( j >= height / 2)
            {
                heightMap[i][j].tileType = (tileVal + 2) % 3;
            }


        }

      
    }

    terrainTime = 0.0f;
    // Generate the terrain
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
            }
            else 
            {
                if (heightMap[i][j].tileType == 0)
                {
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(GrassLand, location, FRotator::ZeroRotator);
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, terrainTime, false);

                }
                if (heightMap[i][j].tileType == 1)
                {
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(DesertLand, location, FRotator::ZeroRotator);
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, terrainTime, false);
                }
                if (heightMap[i][j].tileType == 2)
                {
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=]() {
                        GetWorld()->SpawnActor<AActor>(SnowLand, location, FRotator::ZeroRotator);
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
                        if (heightMap[i][j].tileType == 0 && GrassCount < 3)
                        {
                            AWorldCubeBase* wc ;                         
                            GrassCount += 1;
                            FTimerDelegate TimerDelegate;
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(GrassTown, location, FRotator::ZeroRotator);
                                wc->Location = MapPos[3 + GrassCount];
                                wc->isVisited = false;
                                wc->isTown = true;
								wc->townname = townname[townnamecnt];
                                });
                            FTimerHandle TimerHandle;
                            GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);

                            
                            townnamecnt++;

                        }
                        if (heightMap[i][j].tileType == 1 && DesertCount < 3)
                        {
                            AWorldCubeBase* wc;
                            DesertCount += 1;
                            FTimerDelegate TimerDelegate;
                            TimerDelegate.BindLambda([=, &wc]() {
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
                        }
                        if (heightMap[i][j].tileType == 2 && SnowCount < 3)
                        {
                            AWorldCubeBase* wc;
                            SnowCount += 1;
                            FTimerDelegate TimerDelegate;
                            TimerDelegate.BindLambda([=, &wc]() {
                                wc = GetWorld()->SpawnActor<AWorldCubeBase>(SnowTown, location, FRotator::ZeroRotator);; 
                            wc->Location = MapPos[SnowCount];
                            wc->isVisited = false;
                            wc->isTown = true;
							wc->townname = townname[townnamecnt];
                                });
                            FTimerHandle TimerHandle;
                            GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TownTime, false);

                            SnowCount += 1;
                            
                            townnamecnt++;

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
                if (FMath::FRand() < monsterFrequency)
                {
                    FVector location;
                    if (j % 2 == 0)
                        location = FVector(i * 180, j * 150, heightValue * heightVolume + 200);
                    else
                        location = FVector(i * 180 + 90, j * 150, heightValue * heightVolume + 200);
                 
                    AWorldCubeBase* wc;
                    FTimerDelegate TimerDelegate;
                    TimerDelegate.BindLambda([=, &wc]() {
                        wc = GetWorld()->SpawnActor<AWorldCubeBase>(GolemBase, location, FRotator::ZeroRotator); 
                        wc->monsterLevel = 1;
                        wc->monsterType = 1;
                        wc->monsterPower = 1000;
                        wc->isKey = false;
                        wc->isTown = false;
                        wc->isVisited = false;
                        });
                    FTimerHandle TimerHandle;
                    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, MonsterTime, false);

           
                }

            }
        }
    }
}



