// Fill out your copyright notice in the Description page of Project Settings.


#include "TankerUnit.h"

ATankerUnit::ATankerUnit()
{
    if (HPMPWidgetComponent)
    {

        HPMPWidgetComponent->Initialize(this);
        
    }
}

void ATankerUnit::Attack()
{
}

void ATankerUnit::MoveTo(FVector Location)
{
}

void ATankerUnit::Idle()
{
}

void ATankerUnit::UseSkill()
{
}

void ATankerUnit::Die()
{
}
