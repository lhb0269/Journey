// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Alixer.h"

#include "Journey/HeroCharacter.h"

AAlixer::AAlixer()
{
	Value=10.0f;
}

void AAlixer::Use(AHeroCharacter* Character)
{
	if(Character)
	{
		Character->AddHealth(Value);
	}
}

