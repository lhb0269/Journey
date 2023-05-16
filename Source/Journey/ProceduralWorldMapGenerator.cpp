// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralWorldMapGenerator.h"
#include "GameDataSingleton.h"
#include "GameFramework/PlayerController.h"


AProceduralWorldMapGenerator::AProceduralWorldMapGenerator()
{
 	PrimaryActorTick.bCanEverTick = true;
    isPlayerMove = false;

    MapPos.Add(FVector(-67120.000000, -29210.000000, 540.000000));
    MapPos.Add(FVector(-67120.000000, -62930.000000, 540.000000));
    MapPos.Add(FVector(-67120.000000, -94320.000000, 540.000000));
    MapPos.Add(FVector(-67120.000000, -136950.000000, 540.000000));
    MapPos.Add(FVector(-1410.000000, -30100.000000, 540.000000));
    MapPos.Add(FVector(-1410.000000, -61840.000000, 540.000000));
    MapPos.Add(FVector(-560.000000, -93480.000000, 540.000000));
    MapPos.Add(FVector(-250.000000, -137220.000000, 540.000000));
    MapPos.Add(FVector(35280.000000, -30100.000000, 540.000000));
    MapPos.Add(FVector(35280.000000, -62120.000000, 540.000000));
    MapPos.Add(FVector(36250.000000, -93420.000000, 540.000000));
    MapPos.Add(FVector(35830.000000, -137090.000000, 540.000000));
}


void AProceduralWorldMapGenerator::BeginPlay()
{
	Super::BeginPlay();

    Seed = FDateTime::Now().GetTicks();

    GenerateTerrain();
    GenerateTowns();
    GenerateMonsters();
	

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

    // Generate the terrain
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
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
                    GetWorld()->SpawnActor<AActor>(GrassLand, location, FRotator::ZeroRotator);

                }
                if (heightMap[i][j].tileType == 1)
                {
                    GetWorld()->SpawnActor<AActor>(DesertLand, location, FRotator::ZeroRotator);
                }
                if (heightMap[i][j].tileType == 2)
                {
                    GetWorld()->SpawnActor<AActor>(SnowLand, location, FRotator::ZeroRotator);
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

    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
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

                        // ´« ÃÊ¿ø »ç¸·
                        if (heightMap[i][j].tileType == 0 && GrassCount < 4)
                        {
                            AWorldCubeBase* wc = GetWorld()->SpawnActor<AWorldCubeBase>(GrassTown, location, FRotator::ZeroRotator);
                            wc->Location = MapPos[3 + GrassCount];
                            wc->isVisited = false;
                            wc->isTown = true;
                            GrassCount += 1;

                        }
                        if (heightMap[i][j].tileType == 1 && DesertCount < 4)
                        {
                            AWorldCubeBase* wc = GetWorld()->SpawnActor<AWorldCubeBase>(DesertTown, location, FRotator::ZeroRotator);
                            wc->Location = MapPos[7 + GrassCount];
                            wc->isVisited = false;
                            wc->isTown = true;
                            DesertCount += 1;

                            if (!isPlayerMove)
                            {
                                playerSpawnPos = FVector(location.X, location.Y, location.Z );
                                isPlayerMove = true;
                            }
                        }
                        if (heightMap[i][j].tileType == 2 && SnowCount < 4)
                        {
                            AWorldCubeBase* wc = GetWorld()->SpawnActor<AWorldCubeBase>(SnowTown, location, FRotator::ZeroRotator);
                            wc->Location = MapPos[GrassCount];
                            wc->isVisited = false;
                            wc->isTown = true;
                            SnowCount += 1;
                        }

                    

                }
                
            }
        }
    }
    
}

void AProceduralWorldMapGenerator::GenerateMonsters()
{
    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
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
                    AWorldCubeBase *wc = GetWorld()->SpawnActor<AWorldCubeBase>(GolemBase, location, FRotator::ZeroRotator);
                    wc->monsterLevel = 1;
                    wc->monsterType = 1;
                    wc->monsterPower = 1000;
                    wc->isKey = false;
                    wc->isTown = false;
                    wc->isVisited = false;
                }

            }
        }
    }
}

