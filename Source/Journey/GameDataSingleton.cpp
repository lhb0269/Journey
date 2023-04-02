// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataSingleton.h"

UGameDataSingleton* UGameDataSingleton::Instance = nullptr;

UGameDataSingleton::UGameDataSingleton()
{
    SavedPos = FVector(0, 0, 0);
    TownSpawnPos = FVector(-2000, -25000, 500);
}

UGameDataSingleton* UGameDataSingleton::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = NewObject<UGameDataSingleton>();
    }

    return Instance;
}
