// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralWorldMapGenerator.h"

// Sets default values
AProceduralWorldMapGenerator::AProceduralWorldMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void AProceduralWorldMapGenerator::BeginPlay()
{
	Super::BeginPlay();

    Seed = FDateTime::Now().GetTicks();

    GenerateTerrain();
    GenerateTowns();
	
}

// Called every frame
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
    float scale = 0.7f; // Noise scale

    heightMap.SetNum(width);
    for (int i = 0; i < width; i++)
    {
        heightMap[i].SetNum(height);
        for (int j = 0; j < height; j++)
        {
            heightMap[i][j] = InterpolatedNoise(i * scale, j * scale);
        }
    }

    // Generate the terrain
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            float heightValue = heightMap[i][j];
            // You can map the height value to a suitable range for your game
            FVector location(i * 100, j * 100, heightValue * heightVolume);

            // If heightValue is less than sea level, it's sea
            if (heightValue < seaLevel)
            {
                GetWorld()->SpawnActor<AActor>(Sea, location, FRotator::ZeroRotator);
            }
            else // Otherwise, it's land
            {
                GetWorld()->SpawnActor<AActor>(Land, location, FRotator::ZeroRotator);
            }
        }
    }
}

void AProceduralWorldMapGenerator::GenerateTowns()
{
    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
            float heightValue = heightMap[i][j];
            if (heightValue >= seaLevel)
            {
                if (FMath::FRand() < townFrequency)
                {
                    FVector location(i * 100, j * 100, heightValue * heightVolume);
                    GetWorld()->SpawnActor<AActor>(Town, location, FRotator::ZeroRotator);
                }
                
            }
        }
    }
  
}

