// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileInfo.h"
#include "Blueprint/UserWidget.h"
#include "BattleSystem.generated.h"

UCLASS()
class JOURNEY_API ABattleSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleSystem();

	int bossCount;

	// �� = ���, �縷 = ��ũ , ���� = ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
		TSubclassOf<class AActor> FinalBoss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> BossGoblin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> BossOrc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> BossGolem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
		TSubclassOf<class AActor> BassGoblin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
		TSubclassOf<class AActor> BaseOrc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
		TSubclassOf<class AActor> BaseGolem;


	// MONSTER, PLAYER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> Hero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> Archer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class AActor> Mage;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	//TSubclassOf<class AActor> Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	TSubclassOf<class ATileInfo> TileInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> BattleEndWidgetClass;

	UPROPERTY()
	TArray<AActor*> Heroes;

	UPROPERTY()
	TArray<AActor*> Monsters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	bool isBossSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	int RewardGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	int enemyPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	bool isBattleStart;

	FVector forestVector;
	FVector snowVector;
	FVector desertVector;
	FVector bossVector;
	FVector heroVector;

	// 0 �� ���, 1 �� ��ũ, 2 �� ��
	// 3 ���� ���, 4 ���� ��ũ, 5 ���� ��
	// 6 �縷 ���, 7 �縷 ��ũ, 8 �縷 ��
	// 9 �� ���� ���, 10 ���� ���� ��, 11 �縷 ���� ��ũ 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BattleSystem")
	int battleType;

	void SpawnHeroInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation);
	void SpawnHeroInBoss(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation);
	void SpawnMonsterInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation);
	void SpawnBossInWorld(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation);

	void settingBossField();
	void resetBattleField(int monsterPower,int nowBattleType);

	void ShowBattleEndWidget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
