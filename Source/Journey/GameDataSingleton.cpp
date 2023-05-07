// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataSingleton.h"

UGameDataSingleton* UGameDataSingleton::Instance = nullptr;

UGameDataSingleton::UGameDataSingleton()
{
    SavedPos = FVector(0, 0, 0);

    BattleSpawnPos = FVector(14949, 49000, 94);
    TownSpawnPos = FVector(-2000, -28940, 500);

    NowKeyNum = 0;
    TotalKeyNum = 0;

    isBossWorld = false;

    BossBattleSpawnPos = FVector(-43980, 49000, 94);
    BossWorldSpawnPos = FVector(-15300, 780, 20);
}

UGameDataSingleton* UGameDataSingleton::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = NewObject<UGameDataSingleton>();
    }

    return Instance;
}

UGameDataSingleton* UGameDataSingleton::ResetInstance()
{
    Instance = NewObject<UGameDataSingleton>();

    return Instance;
}
