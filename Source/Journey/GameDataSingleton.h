// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CellularAutomata.h"
#include "GameDataSingleton.generated.h"

/**
 * 
 *  ������ Public ���� ���� ������
 */
UCLASS()
class JOURNEY_API UGameDataSingleton : public UObject
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "UGameDataSingleton")
        static UGameDataSingleton* GetInstance();

    // tile TArray
    TArray<FCAStruct> TileInfos;
    FVector SavedPos;

    FVector TownSpawnPos;
private:
    UGameDataSingleton();

    static UGameDataSingleton* Instance;


};
