// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "InventoryComponent.h"
#include "ShopComponent.h"
#include "Engine/DataTable.h"
#include "JourneySaveGame.h"
#include "CellularAutomata.h"
#include "HeroAIController.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "ProceduralNoiseGenerator.h"
#include "HeroCharacter.generated.h"


UCLASS()
class JOURNEY_API AHeroCharacter : public ABasicCharacter
{
	GENERATED_BODY()
public:
	AHeroCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UInventoryComponent* Inventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UShopComponent* shop;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 hp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 mp;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 Armour;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	int32 gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	int nowKeyNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	int maxKeyNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	int SpecialBuilingcode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fatigue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIBattle")
	bool isAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIBattle")
	bool isDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIBattle")
	bool isInBattle;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	bool isTown;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	bool isShop;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Hero")
	bool isMotel;
	
	UFUNCTION(BlueprintCallable,Category="Items")
	void UseItem(class UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveToLocation(const FVector& DestLocation);

	// CONTROLLER 
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	AHeroAIController* AIController;
	// Battle 관련 정보

	FVector SavedPos;

	// CAMERA
	// worldmap camera 와 battlemap camera
	// + player가 가지고 있는 카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	ACameraActor* BattleCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	ACameraActor* BossBattleCamera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	ACameraActor* WorldMapCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	ACameraActor* BossMapCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	ACameraActor* PlayerCamera;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FVector LandOceanPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool landClick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool oceanClick;

	float DefaultFOV;


	// Camera 전환 함수
	void ChangeToWorldMapCamera();
	void ChangeToBossWorldMapCamera();
	void ChangeToBattleCamera();
	void ChangeToBossBattleCamera();
	void ChangeToTownCamera();

	// 마우스 휠 클릭 이벤트 처리를 위한 함수
	void OnMouseWheelClicked();
	void OnMouseWheelReleased();
	// 카메라 이동을 처리하는 함수
	void MoveCamera(float DeltaTime);

	// 마우스 휠 클릭 상태를 저장하는 변수
	bool bIsMouseWheelClicked;


	void ChangeController(bool isAI);


	

    int32 mapcode =0;//0 world 1 town 2 battle
	float TurnRate =50.f;
	//UJourneySaveGame* MySaveGame;
	// 월드맵 정보
	ACellularAutomata* CellularActor;
	AProceduralNoiseGenerator* ProceduralActor;

	void LoadGame();
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void GoToWorldMap();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void GoToWorld();


	

	void ChangeCamera(bool isWorld);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ChangeGameMode();


	// 월드맵 충돌 체크
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	//UFUNCTION(BlueprintCallable,Category="Items")
	//void BuyItem(UItem* Item,UInventoryComponent* UserInventory);
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void MoveForward(float value);
	void MoveRight(float value);
	void Turn_Right(float value);
	void Pitch_Up(float value);
	void OnLeftClick();
	void OnRightClick();
	void OnZoomIn();
	void OnZoomOut();
	void OnMouseWheelButtonDown();
	
	void createPortal();

	void SwitchToFollowCamera();
	void SwitchToWorldFollowCamera();

};
