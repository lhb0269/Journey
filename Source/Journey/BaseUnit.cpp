// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUnit.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	maxHP = nowHP = 10;
	maxMP = 10;
	nowMP = 10;
	isDeath = false;
	isSkill1 = false;
	
	distance = 1000000.0;
}

void ABaseUnit::Attack()
{
}

void ABaseUnit::MoveTo(FVector Location)
{
}

void ABaseUnit::Idle()
{
}

void ABaseUnit::UseSkill()
{
}

void ABaseUnit::Die()
{
}

float ABaseUnit::GetHealthPercent()
{
	return nowHP / maxHP;
}

float ABaseUnit::GetManaPercent()
{
	return nowMP / maxMP;
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
