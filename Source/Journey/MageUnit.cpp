// Fill out your copyright notice in the Description page of Project Settings.


#include "MageUnit.h"

AMageUnit::AMageUnit()
{
    if (HPMPWidgetComponent)
    {
          HPMPWidgetComponent->Initialize(this);     
    }
}

void AMageUnit::Attack()
{
}

void AMageUnit::MoveTo(FVector Location)
{
}

void AMageUnit::Idle()
{
}

void AMageUnit::UseSkill()
{
}

void AMageUnit::Die()
{
}
