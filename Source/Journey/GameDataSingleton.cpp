// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataSingleton.h"


UGameDataSingleton* UGameDataSingleton::Instance = nullptr;

UGameDataSingleton::UGameDataSingleton()
{
    UE_LOG(LogTemp,Warning,TEXT("SingleTonTest"));
    SavedPos = FVector(0, 0, 0);

    BattleSpawnPos = FVector(14949, 49000, 94);
    TownSpawnPos = FVector(-2000, -28940, 500);

    NowKeyNum = 0;
    TotalKeyNum = 0;

    isBossWorld = false;

    BossBattleSpawnPos = FVector(-43980, 49000, 94);
    BossWorldSpawnPos = FVector(-15300, 780, 20);

    Lineup.Add(Hero);
    Lineup.Add(archer);
    Lineup.Add(Mage);
    
    Hero_Upgrade = 0;
    archer_Upgrade = 0;
    Mage_Upgrade = 0;
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

void UGameDataSingleton::AddPartner()
{
   // IsPartner.Add(true);
    UE_LOG(LogTemp,Warning,TEXT("Add Partner"));
}

void UGameDataSingleton::RemovePartner()
{
    IsPartner.Pop();
    UE_LOG(LogTemp,Warning,TEXT("Remove Partner"));
}

void UGameDataSingleton::FightUpgrade()
{
    Hero_Upgrade += 5;
    UE_LOG(LogTemp,Warning,TEXT("Hero Upgrade : %d"),Hero_Upgrade);
}

void UGameDataSingleton::ShotUpgrade()
{
    archer_Upgrade += 5;
    UE_LOG(LogTemp,Warning,TEXT("Archer Upgrade : %d"),archer_Upgrade);
}

void UGameDataSingleton::MagicUpgrade()
{
    Mage_Upgrade += 5;
    UE_LOG(LogTemp,Warning,TEXT("Mage Upgrade : %d"),Mage_Upgrade);
}
