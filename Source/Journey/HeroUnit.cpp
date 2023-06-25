// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroUnit.h"

AHeroUnit::AHeroUnit()
{
    if (HPMPWidgetComponent)
    {

            HPMPWidgetComponent->Initialize(this);
        
    }
}

void AHeroUnit::Attack()
{
}

void AHeroUnit::MoveTo(FVector Location)
{
}

void AHeroUnit::Idle()
{
}

void AHeroUnit::UseSkill()
{
}

void AHeroUnit::Die()
{
}
