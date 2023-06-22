// Fill out your copyright notice in the Description page of Project Settings.


#include"Scroll.h"

#include "Blueprint/UserWidget.h"
#include "Journey/HeroCharacter.h"

// Sets default values
AScroll::AScroll()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScrollMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	
}

// Called when the game starts or when spawned
void AScroll::BeginPlay()
{
	Super::BeginPlay();
	ScrollMesh->OnComponentBeginOverlap.AddDynamic(this,&AScroll::OnOverlapBegin);
}

// Called every frame
void AScroll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScroll::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

