// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSystem.h"

// Sets default values
ABattleSystem::ABattleSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    isBattleStart = false;
}


void ABattleSystem::SpawnHeroInWorld(UWorld* World,  FVector SpawnLocation,  FRotator SpawnRotation)
{
    if (World)
    {
        AActor* SpawnedHero = nullptr;

        if (Player)
        {
            SpawnLocation.X += 200;
            SpawnLocation.Y -= 750;
            SpawnLocation.Z += 200;

            SpawnedHero = World->SpawnActor<AActor>(Player, SpawnLocation, SpawnRotation);
            Heroes.Add(SpawnedHero);
        }

    }
}

void ABattleSystem::SpawnMonsterInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation)
{

    // enemyPower�� ���� �����Ǵ� �� �� ����
    
    int spawnNum = enemyPower / 100;

    // �ִ� ���� ���� 5����
    if (spawnNum > 5)
        spawnNum = 5;

    if (World)
    {
        for (int i = 0; i < spawnNum; i++)
        {
            if (Monster)
            {
                SpawnLocation.X += FMath::RandRange(-200, 450);
                SpawnLocation.Y += FMath::RandRange(-50, 150);
                SpawnLocation.Z += 100;

                AActor* SpawnedMonster = World->SpawnActor<AActor>(Monster, SpawnLocation, SpawnRotation);
                Monsters.Add(SpawnedMonster);
            }
        }

   
    }
}

void ABattleSystem::resetBattleField(int monsterPower)
{

    isBattleStart = true;
    // �迭 �ʱ�ȭ
    enemyPower = monsterPower;
    RewardGold = monsterPower;

    for (AActor* Actor : Heroes)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }

    for (AActor* Actor : Monsters)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }

    Heroes.Empty();
    Monsters.Empty();

    // ����
    UWorld* World = GetWorld();
    FVector centerPos = GetActorLocation();

    SpawnHeroInWorld(World, centerPos, FRotator(0, 90, 0));
    SpawnMonsterInWorld(World, centerPos, FRotator(0, -90, 0));
}

void ABattleSystem::ShowBattleEndWidget()
{
    if (BattleEndWidgetClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            APlayerController* PlayerController = World->GetFirstPlayerController();
            if (PlayerController)
            {
                UUserWidget* BattleEndWidget = CreateWidget<UUserWidget>(PlayerController, BattleEndWidgetClass);
                if (BattleEndWidget)
                {
                    BattleEndWidget->AddToViewport();
                }
            }
        }
    }

}

// Called when the game starts or when spawned
void ABattleSystem::BeginPlay()
{
	Super::BeginPlay();
    isBattleStart = false;
}

// Called every frame
void ABattleSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

