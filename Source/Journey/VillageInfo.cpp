// Fill out your copyright notice in the Description page of Project Settings.


#include "VillageInfo.h"

#include "HeroCharacter.h"

void UVillageInfo::NativeConstruct()
{
	Super::NativeConstruct();
	UseButton->OnClicked.AddDynamic(this,&UVillageInfo::OnClicked);
}

void UVillageInfo::SetUpText(const FString& VillageName,const FVector& pos,const FVector& savedpos)
{
	FText village = FText::FromString(VillageName);
	name = VillageName;
	Location = pos;
	SavedLocation = savedpos;
	VillageNameBlock->SetText(village);
}

void UVillageInfo::OnClicked()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	Pawn->SetActorLocation(Location);
}
