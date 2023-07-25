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
    
    //AHeroUnit hero;
    //UnitList.Add(hero);

    for(int i=0;i<4;++i)
    {
        HeroItem.Add(nullptr);
        ArcherItem.Add(nullptr);
        MageItem.Add(nullptr);
    }
    Hero_Upgrade = 0;
    archer_Upgrade = 0;
    Mage_Upgrade = 0;

    UIUnitNum = 0;
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
    //IsPartner.Pop();
    UE_LOG(LogTemp,Warning,TEXT("Remove Partner"));
}

void UGameDataSingleton::FightUpgrade()
{
    Hero->power += 5;
    UE_LOG(LogTemp,Warning,TEXT("Hero Upgrade : %d"),Hero->power);
}

void UGameDataSingleton::ShotUpgrade()
{
    archer->power += 5;
    UE_LOG(LogTemp,Warning,TEXT("Archer Upgrade : %d"),archer->power);
}

void UGameDataSingleton::MagicUpgrade()
{
    Mage_Upgrade += 5;
    Mage->power+=5;
    UE_LOG(LogTemp,Warning,TEXT("Mage Upgrade : %d"),Mage->power);
}

int32 UGameDataSingleton::GetUIUnitNum()
{
    return UIUnitNum;
}

void UGameDataSingleton::AddUIUnitNum()
{
    if(UIUnitNum<2)
    {
        UIUnitNum++;
    }
}

void UGameDataSingleton::MinusUIUnitNum()
{
    if(UIUnitNum>0)
    {
        UIUnitNum--;
    }
}

void UGameDataSingleton::UseEquip(UEquipItem * item)
{
    if(item)
    {
        if (item->OwingInventory != nullptr && item->OwningShop == nullptr)
        {
            switch (UIUnitNum) //장비 장착
            {
            case 0:
                if(item->E_Case == 0)
                    HeroItem[0] = item;
                if(item->E_Case == 1)
                    HeroItem[1] = item;
                if(item->E_Case == 2)
                    HeroItem[2] = item;
                if(item->E_Case == 3)
                    HeroItem[3] = item;
                break;
            case 1:
                if(item->E_Case == 0)
                    ArcherItem[0] = item;
                if(item->E_Case == 1)
                    ArcherItem[1] = item;
                if(item->E_Case == 2)
                    ArcherItem[2] = item;
                if(item->E_Case == 3)
                    ArcherItem[3] = item;
                break;
            case 2:
                if(item->E_Case == 0)
                    MageItem[0] = item;
                if(item->E_Case == 1)
                    MageItem[1] = item;
                if(item->E_Case == 2)
                    MageItem[2] = item;
                if(item->E_Case == 3)
                    MageItem[3] = item;
                break;
            }
        }
    }
}
