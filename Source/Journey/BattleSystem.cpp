// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSystem.h"

// Sets default values
ABattleSystem::ABattleSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    isBattleStart = false;

    forestVector = FVector(14800.000000, 50630, 88.000000);
    snowVector = FVector(7600, 50630, 88.000000);
    desertVector = FVector(890, 50630, 88.000000);
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

    // enemyPower�� ���� �����Ǵ� �� �� ����
    
    int spawnNum = enemyPower / 100;

    // �ִ� ���� ���� 5����
    if (spawnNum > 3)
        spawnNum = 3;

    if (World)
    {

        FVector loc;
        // ��
        if(battleType < 3)
        {
            loc = forestVector;
        }
        // ����
        if (battleType >=3 && battleType < 6)
        {
            loc = snowVector;
        }
        // �縷
        if (battleType >= 6 && battleType < 9)
        {
            loc = desertVector;
        }
        // ���� ���
        if (battleType == 9)
        {
            loc = forestVector;
        }
        // ���� ��
        if (battleType == 10)
        {
            loc = snowVector;
        }
        // ���� ��ũ
        if (battleType == 11)
        {
            loc = desertVector;
        }

        FVector spawnVec = loc;

        // ���
        if(battleType % 3 == 0 && battleType <9)
        {
            for (int i = 0; i < spawnNum; i++)
            {
                spawnVec = loc;
               spawnVec.X += FMath::RandRange(-200, 450);
               spawnVec.Y += FMath::RandRange(-50, 150);
               spawnVec.Z += 100;

               AActor* SpawnedMonster = World->SpawnActor<AActor>(BassGoblin, spawnVec, SpawnRotation);
               Monsters.Add(SpawnedMonster);
                
            }
        }
        // ��ũ
        if (battleType % 3 == 1 && battleType < 9)
        {
            for (int i = 0; i < spawnNum; i++)
            {
                spawnVec = loc;
               spawnVec.X += FMath::RandRange(-200, 450);
               spawnVec.Y += FMath::RandRange(-50, 150);
               spawnVec.Z += 100;

               AActor* SpawnedMonster = World->SpawnActor<AActor>(BaseOrc, spawnVec, SpawnRotation);
               Monsters.Add(SpawnedMonster);
                
            }
        }
        // ��
        if (battleType % 3 == 2 && battleType < 9)
        {
            for (int i = 0; i < spawnNum; i++)
            {
                spawnVec = loc;
               spawnVec.X += FMath::RandRange(-200, 450);
               spawnVec.Y += FMath::RandRange(-50, 150);
               spawnVec.Z += 100;

               AActor* SpawnedMonster = World->SpawnActor<AActor>(BaseGolem, spawnVec, SpawnRotation);
               Monsters.Add(SpawnedMonster);
                
            }
        }

        // ���� ���
        if (battleType == 9)
        {
            spawnVec = loc;
            spawnVec.X += FMath::RandRange(-200, 450);
            spawnVec.Y += FMath::RandRange(-50, 150);
            spawnVec.Z += 100;

            AActor* SpawnedMonster = World->SpawnActor<AActor>(BossGoblin, spawnVec, SpawnRotation);
            Monsters.Add(SpawnedMonster);
        }
        // ���� ���
        if (battleType == 10)
        {
            spawnVec = loc;
            spawnVec.X += FMath::RandRange(-200, 450);
            spawnVec.Y += FMath::RandRange(-50, 150);
            spawnVec.Z += 100;

            AActor* SpawnedMonster = World->SpawnActor<AActor>(BossGolem, spawnVec, SpawnRotation);
            Monsters.Add(SpawnedMonster);
        }
        // ���� ���
        if (battleType == 11)
        {
            spawnVec = loc;
            spawnVec.X += FMath::RandRange(-200, 450);
            spawnVec.Y += FMath::RandRange(-50, 150);
            spawnVec.Z += 100;

            AActor* SpawnedMonster = World->SpawnActor<AActor>(BossOrc, spawnVec, SpawnRotation);
            Monsters.Add(SpawnedMonster);
        }


       //for (int i = 0; i < spawnNum; i++)
       // {
       //     if (Monster)
       //     {
       //         SpawnLocation.X += FMath::RandRange(-200, 450);
       //         SpawnLocation.Y += FMath::RandRange(-50, 150);
       //         SpawnLocation.Z += 100;

       //         AActor* SpawnedMonster = World->SpawnActor<AActor>(BossGoblin, SpawnLocation, SpawnRotation);
       //         Monsters.Add(SpawnedMonster);
       //     }
       // }

   
    }
}

void ABattleSystem::resetBattleField(int monsterPower, int nowBattleType)
{
    battleType = nowBattleType;
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

