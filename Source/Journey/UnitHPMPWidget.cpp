// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitHPMPWidget.h"
#include "BaseUnit.h"

void UUnitHPMPWidget::UpdateHP(float NewHP)
{
    if (HPBar != nullptr)
    {
        HPBar->SetPercent(NewHP);
    }
}

void UUnitHPMPWidget::UpdateMP(float NewMP)
{
    if (MPBar != nullptr)
    {
        MPBar->SetPercent(NewMP);
    }
}

void UUnitHPMPWidget::Initialize(ABaseUnit* NewUnit)
{
    Unit = NewUnit;

    if (HPBar)
    {
        HPBar->SetPercent(Unit->GetHealthPercent());
    }

    if (MPBar)
    {
        MPBar->SetPercent(Unit->GetManaPercent());
    }
}
