// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldCubeBase.generated.h"

UCLASS()
class JOURNEY_API AWorldCubeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldCubeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void initWorldCubeBase(bool visited, int32 num);

	void resetCubeState();

	// 0 ½£ °íºí¸°, 1 ½£ ¿ÀÅ©, 2 ½£ °ñ·½
	// 3 ¼³¿ø °íºí¸°, 4 ¼³¿ø ¿ÀÅ©, 4 ¼³¿ø °ñ·½
	// 5 »ç¸· °íºí¸°, 6 »ç¸· ¿ÀÅ©, 7 »ç¸· °ñ·½
	// 8 ½£ º¸½º °íºí¸°, 9 ¼³¿ø º¸½º °ñ·½, 10 »ç¸· º¸½º ¿ÀÅ© 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int tileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isVisited;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isTown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 cubeNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ThemeCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int monsterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int monsterPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int monsterLevel;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isPortal;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString townname;
};
