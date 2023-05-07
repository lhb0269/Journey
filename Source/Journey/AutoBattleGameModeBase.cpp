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
 
}

