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
    bossVector = FVector(-12730.000000,  1560.000000, 403.299049);

    heroVector = FVector(-14020.000000, 1560.000000,  403.299049);

    bossCount = 0;
}


void ABattleSystem::SpawnHeroInWorld(UWorld* World,  FVector SpawnLocation,  FRotator SpawnRotation)
{
    if (World)
    {
        AActor* SpawnedHero = nullptr;
        AActor* SpawnedMage = nullptr;
        AActor* SpawnedArcher = nullptr;


        FVector loc;
        // 숲
        if (battleType < 3)
        {
            loc = forestVector;
        }
        // 설원
        if (battleType >= 3 && battleType < 6)
        {
            loc = snowVector;
        }
        // 사막
        if (battleType >= 6 && battleType < 9)
        {
            loc = desertVector;
        }
        // 보스 고블린
        if (battleType == 9)
        {
            loc = forestVector;
        }
        // 보스 골렘
        if (battleType == 10)
        {
            loc = snowVector;
        }
        // 보스 오크
        if (battleType == 11)
        {
            loc = desertVector;
        }

        FVector spawnVec = loc;
        if (Hero)
        {

            SpawnedHero = World->SpawnActor<AActor>(Hero, FVector(loc.X + 100, loc.Y - 750, loc.Z + 200), SpawnRotation);
            Heroes.Add(SpawnedHero);
        }

        if (Mage)
        {

            SpawnedMage = World->SpawnActor<AActor>(Mage, FVector(loc.X + 200, loc.Y - 750, loc.Z + 200), SpawnRotation);
            Heroes.Add(SpawnedMage);
        }

        if (Archer)
        {
            SpawnedArcher = World->SpawnActor<AActor>(Archer, FVector(loc.X + 300, loc.Y - 750, loc.Z + 200), SpawnRotation);
            Heroes.Add(SpawnedArcher);
        }

    }
}

void ABattleSystem::SpawnHeroInBoss(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation)
{

    AActor* SpawnedHero = nullptr;
    AActor* SpawnedMage = nullptr;
    AActor* SpawnedArcher = nullptr;

    FVector loc = heroVector;

    FRotator R = FRotator(0, 0, 0);

    if (Hero)
    {

        SpawnedHero = World->SpawnActor<AActor>(Hero, FVector(loc.X - 200 , loc.Y , loc.Z ), R);
        Heroes.Add(SpawnedHero);
    }

    if (Mage)
    {

        SpawnedMage = World->SpawnActor<AActor>(Mage, FVector(loc.X , loc.Y - 300, loc.Z ), R);
        Heroes.Add(SpawnedMage);
    }

    if (Archer)
    {
        SpawnedArcher = World->SpawnActor<AActor>(Archer, FVector(loc.X , loc.Y + 300, loc.Z ), R);
        Heroes.Add(SpawnedArcher);
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

        FVector loc;
        // 숲
        if(battleType < 3)
        {
            loc = forestVector;
        }
        // 설원
        if (battleType >=3 && battleType < 6)
        {
            loc = snowVector;
        }
        // 사막
        if (battleType >= 6 && battleType < 9)
        {
            loc = desertVector;
        }
        // 보스 고블린
        if (battleType == 9)
        {
            loc = forestVector;
        }
        // 보스 골렘
        if (battleType == 10)
        {
            loc = snowVector;
        }
        // 보스 오크
        if (battleType == 11)
        {
            loc = desertVector;
        }

        FVector spawnVec = loc;

        // 고블린
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
        // 오크
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
        // 골렘
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

        // 보스 고블린
        if (battleType == 9)
        {
            spawnVec = loc;
            spawnVec.X += FMath::RandRange(-200, 450);
            spawnVec.Y += FMath::RandRange(-50, 150);
            spawnVec.Z += 100;

            AActor* SpawnedMonster = World->SpawnActor<AActor>(BossGoblin, spawnVec, SpawnRotation);
            Monsters.Add(SpawnedMonster);
        }
        // 보스 골렘
        if (battleType == 10)
        {
            spawnVec = loc;
            spawnVec.X += FMath::RandRange(-200, 450);
            spawnVec.Y += FMath::RandRange(-50, 150);
            spawnVec.Z += 100;

            AActor* SpawnedMonster = World->SpawnActor<AActor>(BossGolem, spawnVec, SpawnRotation);
            Monsters.Add(SpawnedMonster);
        }
        // 보스 오크
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

void ABattleSystem::SpawnBossInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation)
{
    FVector spawnVec = bossVector;
   //spawnVec.X += FMath::RandRange(-200, 450);
   //spawnVec.Y += FMath::RandRange(-50, 150);
   //spawnVec.Z += 100;
    FRotator R = FRotator(0, 0, 0);

   AActor* SpawnedMonster = World->SpawnActor<AActor>(FinalBoss, spawnVec, R);
   Monsters.Add(SpawnedMonster);
    


}

void ABattleSystem::settingBossField()
{
    isBattleStart = true;
    // 배열 초기화

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

    SpawnHeroInBoss(World, centerPos, FRotator(0, 90, 0));
    SpawnBossInWorld(World, centerPos, FRotator(0, -90, 0));
}

void ABattleSystem::resetBattleField(int monsterPower, int nowBattleType)
{
    battleType = nowBattleType;
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

        // 보스 고블린
        if (battleType == 9)
        {
            bossCount += 1;
        }
        // 보스 골렘
        if (battleType == 10)
        {
            bossCount += 1;
        }
        // 보스 오크
        if (battleType == 11)
        {
            bossCount += 1;
        }
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

