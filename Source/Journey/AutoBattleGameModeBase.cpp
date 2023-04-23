// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoBattleGameModeBase.h"
#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"


void AAutoBattleGameModeBase::StartBattle()
{
    for (TActorIterator<AMonsterCharacter> It(GetWorld()); It; ++It)
    {
        AMonsterCharacter* Unit = *It;
        AMonsterAIController* AIController = Cast<AMonsterAIController>(Unit->GetController());

        if (AIController)
        {
            AIController->Activate();
        }
    }
}

void AAutoBattleGameModeBase::SpawnUnits()
{
    for (AActor* SpawnPoint : SpawnPoints)
    {
        FVector Location = SpawnPoint->GetActorLocation();
        FRotator Rotation = SpawnPoint->GetActorRotation();

        AMonsterCharacter* Monster = GetWorld()->SpawnActor<AMonsterCharacter>(MonsterClass, Location, Rotation);
    }
}

