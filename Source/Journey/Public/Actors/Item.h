// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Journey/Public/Structs.h"
#include "Journey/Public/InteractableInterface.h"
#include "Item.generated.h"
UCLASS()
class JOURNEY_API AItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		class UStaticMeshComponent* ItemMesh;
	// Called when the game starts or when spawned
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FPosion PosionData;
	virtual void BeginPlay() override;

public:
	virtual void Interact(class AHeroCharacter* Character) override;
	FPosion GetItemData() const {return PosionData;}
};
