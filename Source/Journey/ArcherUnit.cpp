// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherUnit.h"

AArcherUnit::AArcherUnit()
{
    if (HPMPWidgetComponent)
    {

            HPMPWidgetComponent->Initialize(this);
        
    }
}

void AArcherUnit::Attack()
{
}

void AArcherUnit::MoveTo(FVector Location)
{
}

void AArcherUnit::Idle()
{
}

void AArcherUnit::UseSkill()
{
}

void AArcherUnit::Die()
{
}
