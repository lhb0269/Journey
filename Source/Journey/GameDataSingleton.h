// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "ArcherUnit.h"
#include "HeroUnit.h"
#include "MageUnit.h"
#include "UObject/NoExportTypes.h"
#include "CellularAutomata.h"
#include "GameDataSingleton.generated.h"

/**
 * 
 *  값들을 Public 으로 돌려 놓았음
 */
UCLASS()
class JOURNEY_API UGameDataSingleton : public UObject
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "UGameDataSingleton")
        static UGameDataSingleton* GetInstance();

    UFUNCTION(BlueprintCallable, Category = "UGameDataSingleton")
     static UGameDataSingleton* ResetInstance();

	UFUNCTION(BlueprintCallable,Category="Partner")
	void AddPartner();

	UFUNCTION(BlueprintCallable,Category="Partner")
	void RemovePartner();

	UFUNCTION(BlueprintCallable,Category="Upgrade")
	void FightUpgrade();

	UFUNCTION(BlueprintCallable,Category="Upgrade")
	void ShotUpgrade();

	UFUNCTION(BlueprintCallable,Category="Upgrade")
	void MagicUpgrade();
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int TotalKeyNum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int NowKeyNum;

    bool isBossWorld;

    // tile TArray
    TArray<FCAStruct> TileInfos;
    FVector SavedPos;

    FVector TownSpawnPos;
    FVector BattleSpawnPos;

    FVector BossBattleSpawnPos;
    FVector BossWorldSpawnPos;

    FVector playerSpawnPos;

	TArray<bool> IsPartner;

	TArray<ABaseUnit*> Lineup;
	class AArcherUnit* archer;
	class AHeroUnit* Hero;
	class AMageUnit* Mage;

	int32 Hero_Upgrade;
	int32 archer_Upgrade;
	int32 Mage_Upgrade;
private:
    UGameDataSingleton();

    static UGameDataSingleton* Instance;


};
