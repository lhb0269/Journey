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
        AActor* SpawnedMage = nullptr;
        AActor* SpawnedArcher = nullptr;

        FVector loc;
        if (Hero)
        {
            loc = FVector(SpawnLocation.X + 100, SpawnLocation.Y - 750, SpawnLocation.Z + 200);

            SpawnedHero = World->SpawnActor<AActor>(Hero, loc, SpawnRotation);
            Heroes.Add(SpawnedHero);
        }

        if (Mage)
        {
            loc = FVector(SpawnLocation.X + 200, SpawnLocation.Y - 750, SpawnLocation.Z + 200);
     

            SpawnedMage = World->SpawnActor<AActor>(Mage, loc, SpawnRotation);
            Heroes.Add(SpawnedMage);
        }

        if (Archer)
        {
            loc = FVector(SpawnLocation.X + 300, SpawnLocation.Y - 750, SpawnLocation.Z + 200);

            SpawnedArcher = World->SpawnActor<AActor>(Archer, loc, SpawnRotation);
            Heroes.Add(SpawnedArcher);
        }

    }
}

void ABattleSystem::SpawnMonsterInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation)
{

    // enemyPower에 따라 생성되는 골렘 수 변경
    
    int spawnNum = enemyPower / 100;

    // 최대 생성 적은 5마리
    if (spawnNum > 3)
        spawnNum = 3;

    if (World)
    {
       // for (int i = 0; i < spawnNum; i++)
        {
            if (Monster)
            {
                SpawnLocation.X += FMath::RandRange(-200, 450);
                SpawnLocation.Y += FMath::RandRange(-50, 150);
                SpawnLocation.Z += 100;

                AActor* SpawnedMonster = World->SpawnActor<AActor>(BossGoblin, SpawnLocation, SpawnRotation);
                Monsters.Add(SpawnedMonster);
            }
        }

   
    }
}

void ABattleSystem::resetBattleField(int monsterPower, int battleType)
{

    isBattleStart = true;
    // 배열 초기화
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

    // 생성
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
            PlayerController->SetInputMode(FInputModeUIOnly());
            PlayerController->bShowMouseCursor = true;
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

