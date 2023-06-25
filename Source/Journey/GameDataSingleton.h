// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
    UGameDataSingleton();

    static UGameDataSingleton* Instance;


};
