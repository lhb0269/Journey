// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroesBattleUI.h"



void UHeroesBattleUI::NativeConstruct()
{
	

    HPBar1->PercentDelegate.BindUFunction(this, FName("GetHPBar1Percent_Implementation"));
    MPBar1->PercentDelegate.BindUFunction(this, FName("GetMPBar1Percent_Implementation"));

    HPBar2->PercentDelegate.BindUFunction(this, FName("GetHPBar2Percent_Implementation"));
    MPBar2->PercentDelegate.BindUFunction(this, FName("GetMPBar2Percent_Implementation"));

    HPBar3->PercentDelegate.BindUFunction(this, FName("GetHPBar3Percent_Implementation"));
    MPBar3->PercentDelegate.BindUFunction(this, FName("GetMPBar3Percent_Implementation"));

    HPBar4->PercentDelegate.BindUFunction(this, FName("GetHPBar4Percent_Implementation"));
    MPBar4->PercentDelegate.BindUFunction(this, FName("GetMPBar4Percent_Implementation"));

    
    if (UGameDataSingleton::GetInstance()->UnitList[0].unitType == -1)
    {
        HPBar1->SetVisibility(ESlateVisibility::Collapsed);
        MPBar1->SetVisibility(ESlateVisibility::Collapsed);

        Image1->SetVisibility(ESlateVisibility::Collapsed);

        item1_1->SetVisibility(ESlateVisibility::Collapsed);
        item1_2->SetVisibility(ESlateVisibility::Collapsed);
        item1_3->SetVisibility(ESlateVisibility::Collapsed);
        item1_4->SetVisibility(ESlateVisibility::Collapsed);
    }
    if (UGameDataSingleton::GetInstance()->UnitList[1].unitType == -1)
    {
        HPBar2->SetVisibility(ESlateVisibility::Collapsed);
        MPBar2->SetVisibility(ESlateVisibility::Collapsed);

        Image2->SetVisibility(ESlateVisibility::Collapsed);

        item2_1->SetVisibility(ESlateVisibility::Collapsed);
        item2_2->SetVisibility(ESlateVisibility::Collapsed);
        item2_3->SetVisibility(ESlateVisibility::Collapsed);
        item2_4->SetVisibility(ESlateVisibility::Collapsed);
    }
    if (UGameDataSingleton::GetInstance()->UnitList[2].unitType == -1)
    {
        HPBar3->SetVisibility(ESlateVisibility::Collapsed);
        MPBar3->SetVisibility(ESlateVisibility::Collapsed);

        Image3->SetVisibility(ESlateVisibility::Collapsed);

        item3_1->SetVisibility(ESlateVisibility::Collapsed);
        item3_2->SetVisibility(ESlateVisibility::Collapsed);
        item3_3->SetVisibility(ESlateVisibility::Collapsed);
        item3_4->SetVisibility(ESlateVisibility::Collapsed);
    }
    if (UGameDataSingleton::GetInstance()->UnitList[3].unitType == - 1)
    {
        HPBar4->SetVisibility(ESlateVisibility::Collapsed);
        MPBar4->SetVisibility(ESlateVisibility::Collapsed);

        Image4->SetVisibility(ESlateVisibility::Collapsed);

       item4_1->SetVisibility(ESlateVisibility::Collapsed);
       item4_2->SetVisibility(ESlateVisibility::Collapsed);
       item4_3->SetVisibility(ESlateVisibility::Collapsed);
       item4_4->SetVisibility(ESlateVisibility::Collapsed);
    }
}

float UHeroesBattleUI::GetHPBar1Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[0].maxHP / UGameDataSingleton::GetInstance()->UnitList[0].nowHP;
}

float UHeroesBattleUI::GetMPBar1Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[0].maxMP / UGameDataSingleton::GetInstance()->UnitList[0].nowMP;
}

float UHeroesBattleUI::GetHPBar2Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[1].maxHP / UGameDataSingleton::GetInstance()->UnitList[1].nowHP;
}

float UHeroesBattleUI::GetMPBar2Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[1].maxMP / UGameDataSingleton::GetInstance()->UnitList[1].nowMP;
}

float UHeroesBattleUI::GetHPBar3Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[2].maxHP / UGameDataSingleton::GetInstance()->UnitList[2].nowHP;
}

float UHeroesBattleUI::GetMPBar3Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[2].maxMP / UGameDataSingleton::GetInstance()->UnitList[2].nowMP;
}

float UHeroesBattleUI::GetHPBar4Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[3].maxHP / UGameDataSingleton::GetInstance()->UnitList[3].nowHP;
}

float UHeroesBattleUI::GetMPBar4Percent_Implementation() const
{
    return UGameDataSingleton::GetInstance()->UnitList[3].maxMP / UGameDataSingleton::GetInstance()->UnitList[3].nowMP;
}

