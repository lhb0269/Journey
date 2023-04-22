// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController()
    :bIsActivated(false)
{
	BehaviorTreeAsset = nullptr;
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

}

void AMonsterAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AMonsterAIController::Activate()
{
    if (!bIsActivated)
    {
        bIsActivated = true;

        if (BehaviorTreeAsset)
        {
            UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComponent);
            RunBehaviorTree(BehaviorTreeAsset);
        }
    }
}

