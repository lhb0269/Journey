// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteJsonFile.generated.h"

class FJsonObject;

/**
 * 
 */
UCLASS()
class UReadWriteJsonFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
};
